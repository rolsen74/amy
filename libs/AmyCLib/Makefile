
###########################################################################

.PHONY: all clean revision install makedirs strip

###########################################################################

# Root Dir
ROOTDIR		:= ../..

# Object Dir
OBJDIR		:= obj

# Binary Dir
BINDIR		:= bin

# Target Name
TARGET		:= AmyCLib.library

# Compiler Flags
CFLAGS		:= -O2
CFLAGS		+= -I.
CFLAGS		+= -I $(ROOTDIR)/inc_System
CFLAGS		+= -I $(ROOTDIR)/inc_Public
CFLAGS		+= -I $(ROOTDIR)/inc_Private
CFLAGS		+= -DDEBUG
CFLAGS		+= -gstabs
CFLAGS		+= -W
CFLAGS		+= -Wall
CFLAGS		+= -MMD
CFLAGS		+= -MP
CFLAGS		+= -mcrt=clib2

# Linker Flags
LDFLAGS		:= -mcrt=clib2 
LDFLAGS		+= -nostartfiles

# Link Libraries
LIBS		:=

# Empty Source File List (Will grow)
SRCS		:=

# Host SYS we compile on
HOSTOS		:= $(shell uname)

###########################################################################
# Set Compiler

ifeq ($(HOSTOS),AmigaOS)

LS			:= list
RM			:= delete
CC			:= gcc
STRIP		:= strip
MKDIR		:= makedir FORCE
COPY		:= copy
SDK			:= sdk:clib2/

# --

else ifeq ($(HOSTOS),Linux)

LS			:= ls -lort
RM			:= rm -rf
CC			:= ppc-amigaos-gcc
STRIP		:= ppc-amigaos-strip
MKDIR		:= mkdir -p
COPY		:= cp
SDK			:= /SDK/

else

$(error Unknown Host SYS type: $(HOSTOS).)

endif

###########################################################################
# 

SRCS		+= src/Library.c

# Manager Interface
SRCS		+= src/_Manager/Close.c
SRCS		+= src/_Manager/Expunge.c
SRCS		+= src/_Manager/Obtain.c
SRCS		+= src/_Manager/Open.c
SRCS		+= src/_Manager/Release.c

# Main Interface

###########################################################################

OBJS		:= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
DEPS		:= $(patsubst %.c,$(OBJDIR)/%.d,$(SRCS))

all: $(BINDIR)/$(TARGET)

###########################################################################

$(BINDIR)/$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(BINDIR)/$(TARGET) $(OBJS) $(LIBS) -Wl,--cref,-M,-Map=AmyCLib.map

###########################################################################

# Include dependency files
-include $(DEPS)

###########################################################################

clean:
	$(RM) $(OBJS) $(DEPS) bin/$(TARGET) AmyCLib.map

###########################################################################

install:
	$(COPY) $(BINDIR)/$(TARGET) $(INSTALLDIR)

###########################################################################

strip:
	@$(LS)		$(BINDIR)/$(TARGET)
	@$(STRIP)	$(BINDIR)/$(TARGET)
	@$(LS)		$(BINDIR)/$(TARGET)

###########################################################################

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

###########################################################################
