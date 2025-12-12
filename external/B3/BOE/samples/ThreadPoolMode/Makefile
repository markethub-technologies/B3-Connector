#
# Makefile to produce the `ThreadPoolMode` executable
#

CXX = g++-12
CC = g++-12
CXXFLAGS = -O3 -pthread -std=c++17
CPPFLAGS = -DNDEBUG -I. -I.. -I../../include
LDFLAGS = -pthread -L../../lib -Wl,-rpath ../../lib
LDLIBS = -lonixs-b3-boe

SOURCES = ThreadPoolMode.cpp \
          stdafx.cpp \
          stdafx.h \
          ../Common/Listener.h \
          ../Common/Helpers.h \
          ../Settings/Defaults.h
OBJECTS = $(patsubst %.cpp,%.o,$(filter-out %.h,$(SOURCES)))

ThreadPoolMode: $(OBJECTS)

clean:
	rm -f ThreadPoolMode $(OBJECTS)

.PHONY: clean
