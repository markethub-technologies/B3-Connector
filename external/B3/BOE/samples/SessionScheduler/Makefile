#
# Makefile to produce the `SessionScheduler` executable
#

CXX = g++-12
CC = g++-12
CXXFLAGS = -O3 -pthread -std=c++17
CPPFLAGS = -DNDEBUG -I. -I.. -I../../include
LDFLAGS = -pthread -L../../lib -Wl,-rpath ../../lib
LDLIBS = -lonixs-b3-boe

SOURCES = SessionScheduler.cpp \
          stdafx.h
OBJECTS = $(patsubst %.cpp,%.o,$(filter-out %.h,$(SOURCES)))

SessionScheduler: $(OBJECTS)

clean:
	rm -f SessionScheduler $(OBJECTS)

.PHONY: clean
