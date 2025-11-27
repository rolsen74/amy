
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
TARGET		:= Reactive.library

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
CFLAGS		+= -mcrt=amyclib

# Linker Flags
LDFLAGS		:= -nostartfiles
LDFLAGS		+= -mcrt=amyclib

# Link Libraries
LIBS		:= -lc

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
INSTALLDIR	:= libs:

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
SRCS		+= src/_Main/Obtain.c
SRCS		+= src/_Main/Release.c
SRCS		+= src/_Main/Expunge.c
SRCS		+= src/_Main/Clone.c

# RA Root Class
SRCS		+= src/RootClass/Dispatcher.c

# RA Arguments
SRCS		+= src/Arguments/Parse.c
SRCS		+= src/Arguments/Free.c

# RA Attr
SRCS		+= src/Attr/Get.c
SRCS		+= src/Attr/GetTags.c
SRCS		+= src/Attr/GetParent.c
SRCS		+= src/Attr/GetParentTags.c
SRCS		+= src/Attr/GetSuper.c
SRCS		+= src/Attr/GetSuperTags.c
SRCS		+= src/Attr/Set.c
SRCS		+= src/Attr/SetTags.c
SRCS		+= src/Attr/SetParent.c
SRCS		+= src/Attr/SetParentTags.c
SRCS		+= src/Attr/SetSuper.c
SRCS		+= src/Attr/SetSuperTags.c

# RA Class
SRCS		+= src/Class/Add.c
SRCS		+= src/Class/Create.c
SRCS		+= src/Class/Delete.c
SRCS		+= src/Class/Find.c
SRCS		+= src/Class/Lock.c
SRCS		+= src/Class/Unlock.c

# RA Object
SRCS		+= src/Object/Create.c
SRCS		+= src/Object/Delete.c

# RA Method
SRCS		+= src/Method/DoList.c
SRCS		+= src/Method/DoTags.c
SRCS		+= src/Method/DoParentList.c
SRCS		+= src/Method/DoParentTags.c
SRCS		+= src/Method/DoSuperList.c
SRCS		+= src/Method/DoSuperTags.c
SRCS		+= src/Method/DoSuperNew.c
SRCS		+= src/Method/RunFunc.c

# RA Misc
SRCS		+= src/Misc/Get_Tag_Data.c
SRCS		+= src/Misc/Get_Tag_Value.c
SRCS		+= src/Misc/Plugin_Open.c
SRCS		+= src/Misc/Plugin_Free.c
SRCS		+= src/Misc/Valid_Class_Name.c
SRCS		+= src/Misc/Next_Tag.c
SRCS		+= src/Misc/XGet.c
SRCS		+= src/Misc/LoadFile_32.c
SRCS		+= src/Misc/LoadFile_64.c

###########################################################################

OBJS		:= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
DEPS		:= $(patsubst %.c,$(OBJDIR)/%.d,$(SRCS))

all: $(BINDIR)/$(TARGET)

###############################################################################

$(BINDIR)/$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(BINDIR)/$(TARGET) $(OBJS) $(LIBS) -Wl,--cref,-M,-Map=Reactive.map

###############################################################################

# Include dependency files
-include $(DEPS)

###############################################################################

clean:
	$(RM) $(OBJS) $(DEPS) bin/$(TARGET) Reactive.map

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
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

###########################################################################
