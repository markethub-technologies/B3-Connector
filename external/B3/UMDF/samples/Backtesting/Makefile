#
# Makefile to produce the `Backtesting` executable
#

CXX = g++-12
CC = g++-12
CXXFLAGS = -O3 -pthread -std=c++17
CPPFLAGS = -DNDEBUG -I. -I.. -I../../include
LDFLAGS = -pthread -L../../lib -Wl,-rpath ../../lib
LDLIBS = -lonixs-b3umdfh

SOURCES = Backtesting.cpp
OBJECTS = $(patsubst %.cpp,%.o,$(filter-out %.h,$(SOURCES)))

Backtesting: $(OBJECTS)

clean:
	rm -f Backtesting $(OBJECTS)

.PHONY: clean
