#!/bin/bash

MAX_CHARS=15000
OUT_PREFIX="salida"
PART=1
CHARS=0
BASE_DIR="$(pwd)"

new_file() {
  OUT_FILE="${OUT_PREFIX}_${PART}.txt"
  : > "$OUT_FILE"
  CHARS=0
}

new_file

find "$BASE_DIR" \
  -type f \
  \( -name "*.hpp" -o -name "*.cpp" -o -name "*.h" -o -name "*.conf" \) \
  ! -path "$BASE_DIR/build/*" |
while read -r file; do

  HEADER="\n===== FILE: $file =====\n"
  HEADER_LEN=${#HEADER}

  if (( CHARS + HEADER_LEN > MAX_CHARS )); then
    ((PART++))
    new_file
  fi

  echo -ne "$HEADER" >> "$OUT_FILE"
  ((CHARS+=HEADER_LEN))

  while IFS= read -r line; do
    LINE_LEN=$((${#line} + 1))

    if (( CHARS + LINE_LEN > MAX_CHARS )); then
      ((PART++))
      new_file
      echo -ne "$HEADER" >> "$OUT_FILE"
      ((CHARS+=HEADER_LEN))
    fi

    echo "$line" >> "$OUT_FILE"
    ((CHARS+=LINE_LEN))
  done < "$file"

done
