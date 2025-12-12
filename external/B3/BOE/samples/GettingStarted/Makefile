#
# Makefile to produce the `GettingStarted` executable
#

CXX = g++-12
CC = g++-12
CXXFLAGS = -O3 -pthread -std=c++17
CPPFLAGS = -DNDEBUG -I. -I.. -I../../include
LDFLAGS = -pthread -L../../lib -Wl,-rpath ../../lib
LDLIBS = -lonixs-b3-boe

SOURCES = GettingStarted.cpp \
          stdafx.cpp \
          stdafx.h \
          ../Common/Listener.h \
          ../Common/Helpers.h \
          ../Settings/Defaults.h
OBJECTS = $(patsubst %.cpp,%.o,$(filter-out %.h,$(SOURCES)))

GettingStarted: $(OBJECTS)

clean:
	rm -f GettingStarted $(OBJECTS)

.PHONY: clean
