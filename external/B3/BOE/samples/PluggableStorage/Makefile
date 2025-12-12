#
# Makefile to produce the `PluggableStorage` executable
#

CXX = g++-12
CC = g++-12
CXXFLAGS = -O3 -pthread -std=c++17
CPPFLAGS = -DNDEBUG -I. -I.. -I../../include
LDFLAGS = -pthread -L../../lib -Wl,-rpath ../../lib
LDLIBS = -lonixs-b3-boe

SOURCES = PluggableStorage.cpp \
          MySessionStorage.cpp \
          MySessionStorage.h \
          stdafx.cpp \
          stdafx.h \
          ../Common/Helpers.h \
          ../Settings/Defaults.h
OBJECTS = $(patsubst %.cpp,%.o,$(filter-out %.h,$(SOURCES)))

PluggableStorage: $(OBJECTS)

clean:
	rm -f PluggableStorage $(OBJECTS)

.PHONY: clean
