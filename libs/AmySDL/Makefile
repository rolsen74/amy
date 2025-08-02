
###########################################################################

.PHONY: all clean revision install makedirs

###########################################################################

# Root Dir
ROOTDIR		:= ../..

# Object Dir
OBJDIR		:= obj

# Binary Dir
BINDIR		:= bin

# Target Name
TARGET		:= AmySDL.library

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

# Linker Flags
LDFLAGS		:= -nostartfiles

# Link Libraries
LIBS		:=

# Empty Source File List (Will grow)
SRCS		:=

# Host SYS we compile on
HOSTOS		:= $(shell uname)

###########################################################################

# --

ifeq ($(HOSTOS),AmigaOS)

LS			:= list
RM			:= delete
RMDIR		:= rm -rf
MKDIR		:= makedir ALL

# --

else ifeq ($(HOSTOS),Linux)

LS			:= ls -lort
RM			:= rm
RMDIR		:= rm -rf
MKDIR		:= mkdir -p

# --

else

$(error Unknown Host SYS type: $(HOSTOS).)

endif

###########################################################################
# Set Compiler

ifeq ($(HOSTOS),AmigaOS)

LS			:= list
RM			:= delete
CC			:= gcc
STRIP		:= strip
MKDIR		:= makedir FORCE
COPY		:= copy
SDK			:= sdk:

# --

else ifeq ($(HOSTOS),Linux)

LS			:= ls -lort
RM			:= rm -rf
CC			:= ppc-amigaos-gcc
STRIP		:= ppc-amigaos-strip
MKDIR		:= mkdir -p
COPY		:= cp
SDK			:= /SDK/

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

###############################################################################

$(BINDIR)/$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(BINDIR)/$(TARGET) $(OBJS) $(LIBS) -Wl,--cref,-M,-Map=AmySDL.map

###############################################################################

# Include dependency files
-include $(DEPS)

###############################################################################

clean:
	$(RM) $(OBJS) $(DEPS) bin/$(TARGET) AmySDL.map

###############################################################################

install:
	copy $(BINDIR)/$(TARGET) $(INSTALLDIR)

###############################################################################

strip:
	@$(LS)		$(BINDIR)/$(TARGET)
	@$(STRIP)	$(BINDIR)/$(TARGET)
	@$(LS)		$(BINDIR)/$(TARGET)

###############################################################################

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

###########################################################################
