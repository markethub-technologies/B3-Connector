#
# Makefile to produce the `ExternalThreadMode` executable
#

CXX = g++-12
CC = g++-12
CXXFLAGS = -O3 -pthread -std=c++17
CPPFLAGS = -DNDEBUG -I. -I.. -I../../include
LDFLAGS = -pthread -L../../lib -Wl,-rpath ../../lib
LDLIBS = -lonixs-b3-boe

SOURCES = ExternalThreadMode.cpp \
          stdafx.cpp \
          stdafx.h \
          ../Common/Listener.h \
          ../Common/Helpers.h \
          ../Settings/Defaults.h
OBJECTS = $(patsubst %.cpp,%.o,$(filter-out %.h,$(SOURCES)))

ExternalThreadMode: $(OBJECTS)

clean:
	rm -f ExternalThreadMode $(OBJECTS)

.PHONY: clean
