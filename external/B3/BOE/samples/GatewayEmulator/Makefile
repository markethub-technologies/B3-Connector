#
# Makefile to produce the `GatewayEmulator` executable
#

CXX = g++-12
CC = g++-12
CXXFLAGS = -O3 -pthread -std=c++17
CPPFLAGS = -DNDEBUG -I. -I.. -I../../include
LDFLAGS = -pthread -L../../lib -Wl,-rpath ../../lib
LDLIBS = -lonixs-b3-boe

SOURCES = GatewayEmulator.cpp \
          stdafx.cpp \
          stdafx.h \
          ../Common/Listener.h \
          ../Common/Helpers.h \
          ../Settings/Defaults.h
OBJECTS = $(patsubst %.cpp,%.o,$(filter-out %.h,$(SOURCES)))

GatewayEmulator: $(OBJECTS)

clean:
	rm -f GatewayEmulator $(OBJECTS)

.PHONY: clean
