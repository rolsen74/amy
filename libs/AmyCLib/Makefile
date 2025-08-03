
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
INSTALLDIR	:= libs:

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

SRCS		+= src/Library.c

# Manager Interface
SRCS		+= src/_Manager/Close.c
SRCS		+= src/_Manager/Expunge.c
SRCS		+= src/_Manager/Obtain.c
SRCS		+= src/_Manager/Open.c
SRCS		+= src/_Manager/Release.c

# Main (Private) Interface functions
SRCS		+= src/_Main/main_Obtain.c
SRCS		+= src/_Main/main_Release.c
SRCS		+= src/_Main/main_Expunge.c
SRCS		+= src/_Main/main_Clone.c
SRCS		+= src/_Main/Startup_Init.c
SRCS		+= src/_Main/Startup_Main.c
SRCS		+= src/_Main/Startup_Free.c

# Main .. setjmp
ASMSRCS		+= src/_Main_SetJmp/longjmp.s
ASMSRCS		+= src/_Main_SetJmp/setjmp.s

# Main .. string
SRCS		+= src/_Main_String/memset.c

# Main .. strings
SRCS		+= src/_Main_Strings/bzero.c

###########################################################################

OBJS		:= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
ASMOBJS		:= $(patsubst %.s,$(OBJDIR)/%.o,$(ASMSRCS))
DEPS		:= $(patsubst %.c,$(OBJDIR)/%.d,$(SRCS))
ALL_OBJS	:= $(OBJS) $(ASMOBJS)

all: $(BINDIR)/$(TARGET) 

###########################################################################

$(BINDIR)/$(TARGET): $(ALL_OBJS)
	$(CC) $(LDFLAGS) -o $(BINDIR)/$(TARGET) $(ALL_OBJS) $(LIBS) -Wl,--cref,-M,-Map=AmyCLib.map

###########################################################################

# Include dependency files
-include $(DEPS)

###########################################################################

clean:
	$(RM) $(ALL_OBJS) $(DEPS) bin/$(TARGET) AmyCLib.map

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
