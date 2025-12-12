#
# Top level Makefile
#

SAMPLES = AllChannels Backtesting Benchmark GettingStarted LogPlayer

all: $(SAMPLES)

$(SAMPLES):
	$(MAKE) -C $@

clean:
	$(foreach dir,$(SAMPLES),$(MAKE) -C $(dir) clean;)

.PHONY: all clean $(SAMPLES)
