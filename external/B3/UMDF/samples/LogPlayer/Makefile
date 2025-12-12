#
# Makefile to produce the `LogPlayer` executable
#

CXX = g++-12
CC = g++-12
CXXFLAGS = -O3 -pthread -std=c++17
CPPFLAGS = -DNDEBUG -I. -I.. -I../../include
LDFLAGS = -pthread -L../../lib -Wl,-rpath ../../lib
LDLIBS = -lonixs-b3umdfh

SOURCES = LogPlayer.cpp
OBJECTS = $(patsubst %.cpp,%.o,$(filter-out %.h,$(SOURCES)))

LogPlayer: $(OBJECTS)

clean:
	rm -f LogPlayer $(OBJECTS)

.PHONY: clean
