
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
TARGET		:= rTestCase

# Compiler Flags
CFLAGS		:= -O2
CFLAGS		+= -I.
CFLAGS		+= -I $(ROOTDIR)/inc_System
CFLAGS		+= -I $(ROOTDIR)/inc_Public
#CFLAGS		+= -I $(ROOTDIR)/inc_Private
#CFLAGS		+= -DDEBUG
CFLAGS		+= -gstabs
CFLAGS		+= -W
CFLAGS		+= -Wall
CFLAGS		+= -MMD
CFLAGS		+= -MP
CFLAGS		+= -mcrt=clib2
#CFLAGS		+= -D__RA_CLASS__

# Linker Flags
LDFLAGS		:= -mcrt=clib2 
#LDFLAGS	+= -nostartfiles

# Link Libraries
LIBS		:= -lra

# Empty Source File List (Will grow)
ASMSRCS		:=
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
INSTALLDIR	:= c:

# --

else ifeq ($(HOSTOS),Linux)

LS			:= ls -lort
RM			:= rm -rf
CC			:= ppc-amigaos-gcc
STRIP		:= ppc-amigaos-strip
MKDIR		:= mkdir -p
COPY		:= cp
INSTALLDIR	:= 

else

$(error Unknown Host SYS type: $(HOSTOS).)

endif

###########################################################################
# 

SRCS		+= src/Main.c
SRCS		+= src/ScanDir.c
SRCS		+= src/ScanFile.c
SRCS		+= src/TestFile.c
SRCS		+= src/BuildScript.c

###########################################################################

OBJS		:= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
DEPS		:= $(patsubst %.c,$(OBJDIR)/%.d,$(SRCS))
ASMOBJS		:= $(patsubst %.s,$(OBJDIR)/%.o,$(ASMSRCS))
ALL_OBJS	:= $(OBJS) $(ASMOBJS)

all: $(BINDIR)/$(TARGET) 

###########################################################################

$(BINDIR)/$(TARGET): $(ALL_OBJS)
	$(CC) $(LDFLAGS) -o $(BINDIR)/$(TARGET) $(ALL_OBJS) $(LIBS) -Wl,--cref,-M,-Map=App.map

###########################################################################

# Include dependency files
-include $(DEPS)

###########################################################################

clean:
	$(RM) $(ALL_OBJS) $(DEPS) bin/$(TARGET) App.map

###########################################################################

install:
	$(COPY) $(BINDIR)/$(TARGET) $(INSTALLDIR)

###########################################################################

strip:
	@$(LS)		$(BINDIR)/$(TARGET)
	@$(STRIP)	$(BINDIR)/$(TARGET)
	@$(LS)		$(BINDIR)/$(TARGET)

###########################################################################

# Pattern rule for C source files
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Pattern rule for ASM (.s) source files
$(OBJDIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) -c -mregnames $< -o $@

###########################################################################
