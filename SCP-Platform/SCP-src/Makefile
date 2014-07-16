# Compiler
CC = g++

# Compiler flags:
#  -Wall turns on most, but not all, compiler warnings
CFLAGS = -Wall

# Debugging Compiler Flags
#  -g	 adds debugging information to the executable file
DebugCFLAGS = -g

#INCLUDES = -I/Path/to/include
#LFLAGS = -L/Path/to/libs
#LIBS = -lLIBNAMES

# Sources in this directory to Compile
# SRCS = $(wildcard *.cpp)
# We just have the Main entry point here, so it's the only source,
# Everything else will be on it's respective dir
SRCS = SCP-MainEntryPoint.cpp
OBJS = $(SRCS:.cpp=.o)

SUBDIRS = SCP-ACE SCP-Definitions SCP-HE SCP-HIE SCP-HwCtrl

.PHONY : default Release Debug Subdirs all clean $(SUBDIRS)

default: all

Release: SCP-Svarog

Debug: SCP-Svarog-Dbg

Subdirs: $(SUBDIRS)

$(SUBDIRS):
	for subdir in $(SUBDIRS); do \
	  $(MAKE) -C $$subdir $(MAKECMDGOALS); \
	done

SCP-Svarog: SCP-MainEntryPoint.cpp $(SUBDIRS)
	$(CC) $(CFLAGS) -o $(Target) $(Target).c

SCP-Svarog-Dbg: SCP-MainEntryPoint.cpp $(SUBDIRS)
	$(CC) $(DebugCFLAGS) $(CFLAGS) -o $(Target) $(Target).c

all: Debug Release

clean:
	make -C SCP-HwCtrl clean
	rm -f *.o SCP-Svarog*

