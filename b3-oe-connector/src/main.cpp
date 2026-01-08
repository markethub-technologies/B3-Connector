#include "AppRuntime.h"

#include <csignal>
#include <atomic>
#include <thread>

static std::atomic<bool> g_stop{false};

static void onSig(int) { g_stop.store(true); }

int main() {
  std::signal(SIGINT, onSig);
  std::signal(SIGTERM, onSig);

  AppRuntime::Settings s;
  s.ordersBindEndpoint = "tcp://*:6001";
  s.eventsPubEndpoint = "tcp://*:7001";

  // TODO: cargar de config/env
  s.boeHost = "127.0.0.1";
  s.boePort = 9999;
  s.boeSessionId = 0;    // TODO real
  s.boeAccessKey = "";   // TODO real
  s.boeEnteringFirm = 0; // TODO real
  s.boeTradingSystemName = "B3-OE-Connector";

  s.boeLicenseStore = "";     // e.g. "/workspaces/.../license"
  s.boeStorageDirectory = ""; // e.g. "/workspaces/.../storage";

  AppRuntime app(s);
  app.start();

  while (!g_stop.load()) std::this_thread::sleep_for(std::chrono::milliseconds(200));

  app.stop(false);
  return 0;
}
