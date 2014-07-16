# Compiler
CC = g++

# Flags:
INCLUDES = 
CFLAGS = -Wextra
LFLAGS = 
LIBS = 

# Debugging Flags
D_CFLAGS = -g3 -rdynamic
D_LFLAGS = 
D_LIBS = 

# Release Flags
R_CFLAGS = -O3
R_LFLAGS = 
R_LIBS = 

# Sources in this directory to Compile
SUBDIRS=$(shell ls -d */ | grep SCP-)
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

.PHONY : default Release Debug all $(SUBDIRS) clean

default: Release

Release: SCP-Svarog

Debug: SCP-Svarog-Dbg

all: Debug Release

$(SUBDIRS):
	for subdir in $(SUBDIRS); do \
	  $(MAKE) -C $$subdir $(MAKECMDGOALS); \
	done

$(SRCS).o:$(SRCS) $(INCLUDES)
	$(CC) $(CFLAGS) -c

SCP-Svarog: $(SRCS) $(SUBDIRS)
	$(CC) $(CFLAGS) $(R_CFLAGS) $(SRCS).o $(LFLAGS) $(R_LFLAGS) $(LIBS) $(R_LIBS) -o SCP-Svarog-Dbg

SCP-Svarog-Dbg: $(SRCS) $(SUBDIRS)
	$(CC) $(CFLAGS) $(D_CFLAGS) $(SRCS).o $(LFLAGS) $(D_LFLAGS) $(LIBS) $(D_LIBS) -o SCP-Svarog-Dbg

clean:
	for subdir in $(SUBDIRS); do \
	  $(MAKE) -C $$subdir clean; \
	done
	rm -f *.o SCP-Svarog*
