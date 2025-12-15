#!/usr/bin/env bash
# -----------------------------------------------------------------------------
# Descargador de Cache de Protobuf (CodeArtifact + AWSGoogleLogin)
#
# Resumen
# - Descarga un tarball precompilado de Protobuf desde AWS CodeArtifact (paquetes
#   genéricos) y lo guarda en un directorio de cache local.
# - Evita compilar Protobuf desde código fuente en cada entorno, acelerando
#   builds locales, devcontainers y CI.
#
# Autenticación
# - El script intenta usar credenciales AWS ya configuradas (env, profiles,
#   credential_process, etc.).
# - Si no encuentra una sesión AWS válida, intenta obtener credenciales
#   temporales desde el servicio local AWSGoogleLogin.
#
# ⚠️ IMPORTANTE
# - Para que el script funcione correctamente usando AWSGoogleLogin, DEBEN
#   existir en el archivo `.devcontainer/.env` (o en el entorno) las variables:
#
#     AWS_GOOGLE_PASSWORD
#     AWS_GOOGLE_TOKEN_DURATION (opcional, default 28800)
#
# - Si estas variables no están presentes, el script NO VA A FUNCIONAR.
#
# Compatibilidad de entorno
# - El script carga automáticamente `.devcontainer/.env` si existe.
# - Resuelve automáticamente el host del servicio AWSGoogleLogin:
#     * `host.docker.internal` cuando está disponible
#     * `localhost` como fallback (común en Linux host)
#
# Requisitos
# - aws (CLI v2)
# - curl
# - jq
# -----------------------------------------------------------------------------

set -euo pipefail

# ----------------------------
# Cargar .env si existe
# ----------------------------
ENV_FILE=".devcontainer/.env"
if [ -f "$ENV_FILE" ]; then
  set -a
  # shellcheck disable=SC1090
  source "$ENV_FILE"
  set +a
fi

# ----------------------------
# Resolver AWS_GOOGLE_HOST
# ----------------------------
if [ -z "${AWS_GOOGLE_HOST:-}" ]; then
  if getent hosts host.docker.internal >/dev/null 2>&1; then
    AWS_GOOGLE_HOST="host.docker.internal"
  else
    AWS_GOOGLE_HOST="localhost"
  fi
fi
export AWS_GOOGLE_HOST

PROTOBUF_VERSION="28.3"
PROTO_CACHE_VERSION="v2"
PROTO_PKG="protobuf-${PROTOBUF_VERSION}-ubuntu2404-gcc-${PROTO_CACHE_VERSION}"
PROTO_FILE="${PROTO_PKG}.tar.gz"
PROTO_REPO="MH-cpp"
NAMESPACE="com.markethub.dependencies"
DOMAIN="markethub"
OWNER="221110370770"
REGION="us-east-1"

CACHE_DIR="$(cd "$(dirname "$0")/cache" && pwd 2>/dev/null || echo "$(dirname "$0")/cache")"
mkdir -p "${CACHE_DIR}"

echo "==> Descargador de Cache de Protobuf"
echo "    Versión: ${PROTOBUF_VERSION}"
echo "    Paquete: ${PROTO_PKG}"
echo "    Directorio de cache: ${CACHE_DIR}"
echo ""

# Si el archivo ya existe, salir
if [ -f "${CACHE_DIR}/${PROTO_FILE}" ]; then
  echo "✅ El cache de Protobuf ya existe: ${CACHE_DIR}/${PROTO_FILE}"
  echo "   Tamaño: $(du -h "${CACHE_DIR}/${PROTO_FILE}" | cut -f1)"
  echo ""
  echo "Para forzar la descarga nuevamente:"
  echo "   rm ${CACHE_DIR}/${PROTO_FILE}"
  exit 0
fi

# ----------------------------
# Autenticación AWS
# ----------------------------
aws_is_authed() {
  aws sts get-caller-identity --region "${REGION}" >/dev/null 2>&1
}

if ! aws_is_authed; then
  echo "==> AWS CLI no está autenticado. Intentando con AWSGoogleLogin..."

  : "${AWS_GOOGLE_PASSWORD:?❌ Falta la variable AWS_GOOGLE_PASSWORD (definila en .devcontainer/.env)}"

  AWS_GOOGLE_TOKEN_DURATION="${AWS_GOOGLE_TOKEN_DURATION:-28800}"

  CREDS_JSON="$(curl -sS -X POST "http://${AWS_GOOGLE_HOST}:8001/credentials" \
    -H "Content-Type: application/json" \
    -d "{\"password\":\"${AWS_GOOGLE_PASSWORD}\",\"duration\":${AWS_GOOGLE_TOKEN_DURATION}}")"

  # Extraer credenciales temporales (soporta variantes comunes de keys)
  export AWS_ACCESS_KEY_ID="$(echo "$CREDS_JSON" | jq -r '.AccessKeyId // .accessKeyId // .Credentials.AccessKeyId')"
  export AWS_SECRET_ACCESS_KEY="$(echo "$CREDS_JSON" | jq -r '.SecretAccessKey // .secretAccessKey // .Credentials.SecretAccessKey')"
  export AWS_SESSION_TOKEN="$(echo "$CREDS_JSON" | jq -r '.SessionToken // .sessionToken // .Credentials.SessionToken')"
  export AWS_DEFAULT_REGION="${AWS_DEFAULT_REGION:-${REGION}}"

  if ! aws_is_authed; then
    echo "❌ No se pudo autenticar contra AWS luego de usar AWSGoogleLogin."
    echo "   Verificá que el servicio esté accesible en:"
    echo "   http://${AWS_GOOGLE_HOST}:8001/credentials"
    exit 1
  fi
fi

echo "✅ AWS autenticado correctamente:"
aws sts get-caller-identity --region "${REGION}" | jq .
echo ""

# ----------------------------
# Verificar existencia del paquete
# ----------------------------
echo "==> Verificando existencia de Protobuf ${PROTOBUF_VERSION} en CodeArtifact..."

PROTO_EXISTS="$(aws codeartifact list-package-versions --region "${REGION}" \
  --domain "${DOMAIN}" \
  --domain-owner "${OWNER}" \
  --repository "${PROTO_REPO}" \
  --format generic \
  --namespace "${NAMESPACE}" \
  --package "${PROTO_PKG}" \
  --query "versions[?version=='${PROTOBUF_VERSION}'] | length(@)" \
  --output text 2>/dev/null | tr -dc '0-9' || echo "0")"

if [ "${PROTO_EXISTS}" -eq 0 ]; then
  echo "❌ Protobuf ${PROTOBUF_VERSION} no encontrado en CodeArtifact."
  echo "   Paquete esperado: ${PROTO_PKG}"
  echo "   Repositorio: ${PROTO_REPO}"
  exit 1
fi

echo "✅ Protobuf ${PROTOBUF_VERSION} encontrado en CodeArtifact"
echo ""
echo "==> Descargando a ${CACHE_DIR}/${PROTO_FILE}..."

# ----------------------------
# Descargar artefacto
# ----------------------------
aws codeartifact get-package-version-asset --region "${REGION}" \
  --domain "${DOMAIN}" \
  --domain-owner "${OWNER}" \
  --repository "${PROTO_REPO}" \
  --format generic \
  --namespace "${NAMESPACE}" \
  --package "${PROTO_PKG}" \
  --package-version "${PROTOBUF_VERSION}" \
  --asset "${PROTO_FILE}" \
  "${CACHE_DIR}/${PROTO_FILE}"

echo ""
echo "✅ Descarga completada correctamente"
echo "   Archivo: ${CACHE_DIR}/${PROTO_FILE}"
echo "   Tamaño: $(du -h "${CACHE_DIR}/${PROTO_FILE}" | cut -f1)"