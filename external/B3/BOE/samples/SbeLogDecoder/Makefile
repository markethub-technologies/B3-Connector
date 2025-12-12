#
# Makefile to produce the `SbeLogDecoder` executable
#

CXX = g++-12
CC = g++-12
CXXFLAGS = -O3 -pthread -std=c++17
CPPFLAGS = -DNDEBUG -I. -I.. -I../../include
LDFLAGS = -pthread -L../../lib -Wl,-rpath ../../lib
LDLIBS = -lonixs-b3-boe

SOURCES = SbeLogDecoder.cpp \
          stdafx.cpp \
          stdafx.h
OBJECTS = $(patsubst %.cpp,%.o,$(filter-out %.h,$(SOURCES)))

SbeLogDecoder: $(OBJECTS)

clean:
	rm -f SbeLogDecoder $(OBJECTS)

.PHONY: clean
