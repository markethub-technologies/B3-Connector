#
# Makefile to produce the `TradingClient` executable
#

CXX = g++-12
CC = g++-12
CXXFLAGS = -O3 -pthread -std=c++17
CPPFLAGS = -DNDEBUG -I. -I.. -I../../include
LDFLAGS = -pthread -L../../lib -Wl,-rpath ../../lib
LDLIBS = -lonixs-b3-boe

SOURCES = Main.cpp \
          TradingClient.cpp \
          TradingClient.h \
          MessageFactory.cpp \
          MessageFactory.h \
          CUI.h \
          Book.h \
          Order.cpp \
          Order.h \
          Settings.cpp \
          Settings.h \
          stdafx.cpp \
          stdafx.h \
          ../Common/Helpers.h \
          ../Settings/Defaults.h
OBJECTS = $(patsubst %.cpp,%.o,$(filter-out %.h,$(SOURCES)))

TradingClient: $(OBJECTS)

clean:
	rm -f TradingClient $(OBJECTS)

.PHONY: clean
