#pragma once
#include <string_view>

namespace markethub::messaging::models {

  /// <summary>
  /// Tipos de mensajes que soporta la librería.
  /// </summary>
  struct MessageTypes {
    static constexpr std::string_view Ping = "Ping";
    static constexpr std::string_view Pong = "Pong";

    static constexpr std::string_view SecurityDefinitionRequest = "SecurityDefinitionRequest";
    static constexpr std::string_view SecurityDefinitionResponse = "SecurityDefinitionResponse";

    static constexpr std::string_view SecurityListRequest = "SecurityListRequest";
    static constexpr std::string_view SecurityListResponse = "SecurityListResponse";

    static constexpr std::string_view MarketDataSuscriptionRequest = "MarketDataSuscriptionRequest";
    static constexpr std::string_view MarketDataSuscriptionResponse =
        "MarketDataSuscriptionResponse";

    static constexpr std::string_view PreviousClosePriceRequest = "PreviousClosePriceRequest";
    static constexpr std::string_view PreviousClosePriceResponse = "PreviousClosePriceResponse";

    static constexpr std::string_view MarketDataUpdate = "MarketData";

    static constexpr std::string_view NewOrderRequest = "NewOrderRequest";
    static constexpr std::string_view CancelOrderRequest = "CancelOrderRequest";
    static constexpr std::string_view ReplaceOrderRequest = "ReplaceOrderRequest";

    static constexpr std::string_view MassCancelRequest = "MassCancelRequest";
    static constexpr std::string_view MassCancelReport = "MassCancelReport";

    static constexpr std::string_view OrderStatusRequest = "OrderStatusRequest";
    static constexpr std::string_view TradeSessionStatusRequest = "TradeSessionStatusRequest";
    static constexpr std::string_view TradingSessionStatus = "TradingSessionStatus";

    static constexpr std::string_view MassOrderStatusRequest = "MassOrderStatusRequest";
    static constexpr std::string_view MassOrderStatusResponse = "MassOrderStatusResponse";

    static constexpr std::string_view TradeCaptureReportRequest = "TradeCaptureReportRequest";
    static constexpr std::string_view TradeCaptureReportResponse = "TradeCaptureReportResponse";
    static constexpr std::string_view TradeCaptureReport = "TradeCaptureReport";

    static constexpr std::string_view ExecutionReport = "ExecutionReport";

    static constexpr std::string_view SecurityStatusRequest = "SecurityStatusRequest";
    static constexpr std::string_view SecurityStatusResponse = "SecurityStatusResponse";

    static constexpr std::string_view AccountListRequest = "AccountListRequest";
    static constexpr std::string_view AccountListResponse = "AccountListResponse";
    static constexpr std::string_view AccountListIncremental = "AccountListIncremental";

    static constexpr std::string_view AllSymbolsRequest = "AllSymbolsRequest";
    static constexpr std::string_view AllSymbolsResponse = "AllSymbolsResponse";

    static constexpr std::string_view Stop = "Stop";

    static constexpr std::string_view AddServiceRequest = "AddServiceRequest";
    static constexpr std::string_view AddServiceResponse = "AddServiceResponse";

    static constexpr std::string_view Heartbeat = "Heartbeat";

    static constexpr std::string_view RemoveServiceRequest = "RemoveServiceRequest";
    static constexpr std::string_view NodesBroadcast = "NodesBroadcast";

    static constexpr std::string_view FindNodeRequest = "FindNodeRequest";
    static constexpr std::string_view FindNodeResponse = "FindNodeResponse";

    static constexpr std::string_view DiscoverServicesRequest = "DiscoverServicesRequest";

    static constexpr std::string_view FilterSymbolsRequest = "FilterSymbolsRequest";
    static constexpr std::string_view FilterSymbolsResponse = "FilterSymbolsResponse";

    static constexpr std::string_view AllInstrumentsRequest = "AllInstrumentsRequest";
    static constexpr std::string_view AllInstrumentsResponse = "AllInstrumentsResponse";

    static constexpr std::string_view HoldingReportRequest = "HoldingReportRequest";
    static constexpr std::string_view HoldingReportResponse = "HoldingReportResponse";

    static constexpr std::string_view PNLReportRequest = "PNLReportRequest";
    static constexpr std::string_view PNLReportResponse = "PNLReportResponse";

    static constexpr std::string_view HoldingReport = "HoldingReport";
    static constexpr std::string_view PNLReport = "PNLReport";

    static constexpr std::string_view NextBusinessDayRequest = "NextBusinessDayRequest";
    static constexpr std::string_view NextBusinessDayResponse = "NextBusinessDayResponse";

    static constexpr std::string_view ReposMappingRequest = "ReposMappingRequest";
    static constexpr std::string_view ReposMappingResponse = "ReposMappingResponse";

    static constexpr std::string_view OTCTradeReport = "OTCTradeReport";

    static constexpr std::string_view PositionUpdateNotification = "PositionUpdateNotification";
    static constexpr std::string_view PositionCorrectionNotification =
        "PositionCorrectionNotification";
  };

} // namespace markethub::messaging::models