#
# Makefile to produce the `Benchmark` executable
#

CXX = g++-12
CC = g++-12
CXXFLAGS = -O3 -pthread -std=c++17
CPPFLAGS = -DNDEBUG -I. -I.. -I../../include
LDFLAGS = -pthread -L../../lib -Wl,-rpath ../../lib
LDLIBS = -lonixs-b3-boe

SOURCES = Benchmark.cpp \
          stdafx.cpp \
          stdafx.h \
          ../Common/BenchmarkGatewayListener.h \
          ../Common/BenchmarkSessionListener.h \
          ../Common/Helpers.h \
          ../Common/PerformanceCounter.h \
          ../Common/PerformanceCounter.inc.h \
          ../Common/BenchmarkData.h \
          ../Settings/Defaults.h
OBJECTS = $(patsubst %.cpp,%.o,$(filter-out %.h,$(SOURCES)))

Benchmark: $(OBJECTS)

clean:
	rm -f Benchmark $(OBJECTS)

.PHONY: clean
