#----------------------------------------------------------------------------
#       Macros
#----------------------------------------------------------------------------
CXX           = g++
RM            = rm -rf
EXEEXT        =
CPPFLAGS      = $(PICFLAGS) $(GENFLAGS) -D_LINUX -o2
OUTPUT_OPTION = -o "$@"
COMPILE.cc    = $(CXX) $(CCFLAGS) $(CPPFLAGS) -c
BTARGETDIR    = ./
BIN           = $(BTARGETDIR)multicastTest$(EXEEXT)
OBJECT        = .o
OBJS          = MulticastTest$(OBJECT)
EXPORTFLAGS   = $(STATICFLAGS)

#----------------------------------------------------------------------------
#       Local targets
#----------------------------------------------------------------------------

all: $(BIN)

$(BTARGETDIR):
	@$(MKDIR) "$@"

$(BIN): $(BTARGETDIR) $(OBJS)
	$(LINK.cc) $(OUTPUT_OPTION) $(OBJS) $(LDLIBS)

multicastTest$(OBJECT): MulticastTest.cpp
	$(COMPILE.cc) $(EXPORTFLAGS) $(OUTPUT_OPTION) MulticastTest.cpp

clean:
	-$(RM) $(OBJS)

realclean: clean
	-$(RM) $(BIN)
