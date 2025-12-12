#
# Top level Makefile
#

SAMPLES = Benchmark ExternalThreadMode GettingStarted GatewayEmulator SbeLogDecoder SessionScheduler TCPDirectBenchmark TCPDirectGettingStarted TCPStandardBenchmark ThreadPoolMode TradingClient PluggableStorage

all: $(SAMPLES)

$(SAMPLES):
	$(MAKE) -C $@

clean:
	$(foreach dir,$(SAMPLES),$(MAKE) -C $(dir) clean;)

.PHONY: all clean $(SAMPLES)
