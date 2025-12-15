#pragma once
#include <string_view>

namespace markethub::messaging::events {

  /// <summary>
  /// Tipos de eventos
  /// </summary>
  struct EventTypes {
    /// Evento disparado cuando se genera un libro.
    static constexpr std::string_view ON_BOOK_GENERATED = "on_book_generated";

    /// Evento disparado cuando se genera un execution report.
    static constexpr std::string_view EXECUTION_REPORT = "execution_report";

    /// Evento disparado cuando se inicia la ejecución de una estrategia.
    static constexpr std::string_view STRATEGY_EXECUTION_STARTED = "strategy_execution_started";

    /// Evento disparado cuando se reciben nuevos datos.
    static constexpr std::string_view ON_DATA = "on_data";

    /// Evento disparado cuando finalizan los datos.
    static constexpr std::string_view END_ON_DATA = "end_on_data";

    /// Evento disparado cuando se recibe un execution report.
    static constexpr std::string_view ON_EXECUTION_REPORT = "on_execution_report";

    /// Evento disparado cuando se generan estadísticas.
    static constexpr std::string_view STATISTICS = "statistics";

    /// Evento disparado cuando se genera un libro para almacenar datos históricos.
    static constexpr std::string_view ON_BOOK_GENERATED_HISTORICAL = "on_book_generated_historical";

    /// Evento disparado cuando se recibe un cambio en los parámetros de la estrategia.
    static constexpr std::string_view ON_PARAMS_CHANGED = "on_params_changed";
  };

} // namespace markethub::messaging::events