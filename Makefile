# Makefile for building embedded application.
# by Brian Fraser

# Edit this file to compile extra C files into their own programs.
TARGETS = capture
SOURCES = main.c
PUBDIR = $(HOME)/cmpt433/public/project/capture
OUTDIR = $(PUBDIR)

CROSS_TOOL = arm-linux-gnueabihf-
# CROSS_TOOL = 

CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc
CC_H = gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L  
# -pg for supporting gprof profiling.
# CFLAGS += -pg

all: copy
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGETS) -lpthread

clean:
	rm -f $(OUTDIR) / $(TARGETS)

copy:
	cp $(HOME)/cmpt433/work/myApps/project/capture/bash.sh $(PUBDIR)

