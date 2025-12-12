#
# Makefile to produce the `AllChannels` executable
#

CXX = g++-12
CC = g++-12
CXXFLAGS = -O3 -pthread -std=c++17
CPPFLAGS = -DNDEBUG -I. -I.. -I../../include
LDFLAGS = -pthread -L../../lib -Wl,-rpath ../../lib
LDLIBS = -lonixs-b3umdfh

SOURCES = AllChannels.cpp \
          MyListener.cpp \
          MyListener.h
OBJECTS = $(patsubst %.cpp,%.o,$(filter-out %.h,$(SOURCES)))

AllChannels: $(OBJECTS)

clean:
	rm -f AllChannels $(OBJECTS)

.PHONY: clean
