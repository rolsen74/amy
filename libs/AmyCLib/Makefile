
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
#CFLAGS		+= -DDEBUG
#CFLAGS		+= -gstabs
CFLAGS		+= -W
CFLAGS		+= -Wall
CFLAGS		+= -MMD
CFLAGS		+= -MP
CFLAGS		+= -mcrt=clib2
CFLAGS		+= -fno-builtin
CFLAGS		+= -D__DO_FUNCTION_LOG__

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
SRCS		+= src/_Main/Check_Abort.c
SRCS		+= src/_Main/Convert_DS_to_Time.c
SRCS		+= src/_Main/Convert_ED_to_Stat.c
SRCS		+= src/_Main/Convert_IOErr_to_ErrNo.c
SRCS		+= src/_Main/Convert_Time_to_TM.c
SRCS		+= src/_Main/FB_Read.c
SRCS		+= src/_Main/FB_Read_Drop_Buffer.c
SRCS		+= src/_Main/FB_Read_Fill_Buffer.c
SRCS		+= src/_Main/FB_Write.c
SRCS		+= src/_Main/FB_Write_Flush_Buffer.c
SRCS		+= src/_Main/FB_Write_Flush_Buffer2.c
SRCS		+= src/_Main/FD_IFC_File.c
SRCS		+= src/_Main/FD_Array_Insert.c
SRCS		+= src/_Main/FD_Array_Remove.c
SRCS		+= src/_Main/FD_Init.c
SRCS		+= src/_Main/FD_Init_Struct.c
SRCS		+= src/_Main/FD_Node_Alloc.c
SRCS		+= src/_Main/FD_Node_Free.c
SRCS		+= src/_Main/FD_Lock_Nr.c
SRCS		+= src/_Main/FD_Lock_Stream.c
SRCS		+= src/_Main/FD_Lock_Unlock.c
SRCS		+= src/_Main/Func_Log.c
SRCS		+= src/_Main/main_Obtain.c
SRCS		+= src/_Main/main_Release.c
SRCS		+= src/_Main/main_Expunge.c
SRCS		+= src/_Main/main_Clone.c
SRCS		+= src/_Main/Memory_Mem_Alloc.c
SRCS		+= src/_Main/Memory_Mem_Free.c
SRCS		+= src/_Main/Memory_Mem_Realloc.c
SRCS		+= src/_Main/Memory_Pool_Alloc.c
SRCS		+= src/_Main/Memory_Pool_Create.c
SRCS		+= src/_Main/Memory_Pool_Delete.c
SRCS		+= src/_Main/Memory_Pool_Flush.c
SRCS		+= src/_Main/Memory_Pool_Free.c
SRCS		+= src/_Main/Print.c
SRCS		+= src/_Main/Scan.c
SRCS		+= src/_Main/Startup_Init.c
SRCS		+= src/_Main/Startup_Main.c
SRCS		+= src/_Main/Startup_Free.c

# Main .. assert
SRCS		+= src/_Main_Assert/assert.c

# Main .. ctype
SRCS		+= src/_Main_CType/isalpha.c
SRCS		+= src/_Main_CType/isalpha_locale.c
SRCS		+= src/_Main_CType/isdigit.c
SRCS		+= src/_Main_CType/isdigit_locale.c
SRCS		+= src/_Main_CType/isspace.c
SRCS		+= src/_Main_CType/isspace_locale.c
SRCS		+= src/_Main_CType/isupper.c
SRCS		+= src/_Main_CType/isupper_locale.c
SRCS		+= src/_Main_CType/isxdigit.c
SRCS		+= src/_Main_CType/isxdigit_locale.c
SRCS		+= src/_Main_CType/tolower.c
SRCS		+= src/_Main_CType/tolower_locale.c
SRCS		+= src/_Main_CType/toupper.c
SRCS		+= src/_Main_CType/toupper_locale.c
SRCS		+= src/_Main_CType/islower.c
#SRCS		+= src/_Main_CType/islower_locale.c

# Main .. fcntl
SRCS		+= src/_Main_FCntl/open.c

# Main .. Inttypes
SRCS		+= src/_Main_Inttypes/strtoimax.c
SRCS		+= src/_Main_Inttypes/strtoumax.c

# Main .. Math
SRCS		+= src/_Main_Math/d__get_huge_val.c
SRCS		+= src/_Main_Math/d__inf.c
SRCS		+= src/_Main_Math/d__isinf.c
SRCS		+= src/_Main_Math/d__isnan.c
SRCS		+= src/_Main_Math/d_copysign.c
SRCS		+= src/_Main_Math/d_nan.c
SRCS		+= src/_Main_Math/d_fabs.c
SRCS		+= src/_Main_Math/d_pow.c
SRCS		+= src/_Main_Math/d_scalbn.c
SRCS		+= src/_Main_Math/d_sqrt.c

# Main .. setjmp
ASMSRCS		+= src/_Main_SetJmp/longjmp.s
ASMSRCS		+= src/_Main_SetJmp/setjmp.s

# Main .. signal
SRCS		+= src/_Main_Signal/raise.c
SRCS		+= src/_Main_Signal/signal.c

# Main .. stdio
SRCS		+= src/_Main_Stdio/clearerr.c
SRCS		+= src/_Main_Stdio/fclose.c
SRCS		+= src/_Main_Stdio/fflush.c
SRCS		+= src/_Main_Stdio/fgetpos.c
SRCS		+= src/_Main_Stdio/flockfile.c
SRCS		+= src/_Main_Stdio/fopen.c
SRCS		+= src/_Main_Stdio/fputc.c
SRCS		+= src/_Main_Stdio/fputc_unlocked.c
SRCS		+= src/_Main_Stdio/fgetc.c
SRCS		+= src/_Main_Stdio/fread.c
SRCS		+= src/_Main_Stdio/fseek.c
SRCS		+= src/_Main_Stdio/fseeko.c
SRCS		+= src/_Main_Stdio/ftell.c
SRCS		+= src/_Main_Stdio/funlockfile.c
SRCS		+= src/_Main_Stdio/ferror.c
#SRCS		+= src/_Main_Stdio/printf.c
SRCS		+= src/_Main_Stdio/putchar.c
SRCS		+= src/_Main_Stdio/puts.c
SRCS		+= src/_Main_Stdio/setvbuf.c
#SRCS		+= src/_Main_Stdio/snprintf.c
#SRCS		+= src/_Main_Stdio/sprintf.c
SRCS		+= src/_Main_Stdio/ungetc.c
SRCS		+= src/_Main_Stdio/vasprintf.c
SRCS		+= src/_Main_Stdio/vprintf.c
SRCS		+= src/_Main_Stdio/vsprintf.c
SRCS		+= src/_Main_Stdio/vsnprintf.c
SRCS		+= src/_Main_Stdio/vsscanf.c

# Main .. stdlib
SRCS		+= src/_Main_Stdlib/_Exit.c
SRCS		+= src/_Main_Stdlib/abort.c
SRCS		+= src/_Main_Stdlib/atoi.c
SRCS		+= src/_Main_Stdlib/calloc.c
SRCS		+= src/_Main_Stdlib/exit.c
SRCS		+= src/_Main_Stdlib/free.c
SRCS		+= src/_Main_Stdlib/malloc.c
SRCS		+= src/_Main_Stdlib/rand.c
SRCS		+= src/_Main_Stdlib/rand_r.c
SRCS		+= src/_Main_Stdlib/realloc.c
SRCS		+= src/_Main_Stdlib/srand.c
SRCS		+= src/_Main_Stdlib/strtod.c
SRCS		+= src/_Main_Stdlib/strtof.c
SRCS		+= src/_Main_Stdlib/strtol.c

# Main .. string
SRCS		+= src/_Main_String/memcmp.c
SRCS		+= src/_Main_String/memcpy.c
SRCS		+= src/_Main_String/memmove.c
SRCS		+= src/_Main_String/memset.c
SRCS		+= src/_Main_String/strcat.c
SRCS		+= src/_Main_String/strcmp.c
SRCS		+= src/_Main_String/strcpy.c
SRCS		+= src/_Main_String/strdup.c
SRCS		+= src/_Main_String/strlen.c
SRCS		+= src/_Main_String/strncmp.c
SRCS		+= src/_Main_String/strncpy.c
SRCS		+= src/_Main_String/strndup.c
SRCS		+= src/_Main_String/strnlen.c

# Main .. strings
SRCS		+= src/_Main_Strings/bzero.c
SRCS		+= src/_Main_Strings/strcasecmp.c
SRCS		+= src/_Main_Strings/strncasecmp.c

# Main .. time
SRCS		+= src/_Main_Time/localtime.c
SRCS		+= src/_Main_Time/strftime.c
SRCS		+= src/_Main_Time/time.c
SRCS		+= src/_Main_Time/gmtime.c
SRCS		+= src/_Main_Time/gmtime_r.c

# Main .. unistd
SRCS		+= src/_Main_Unistd/close.c

###########################################################################

OBJS		:= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
DEPS		:= $(patsubst %.c,$(OBJDIR)/%.d,$(SRCS))
ASMOBJS		:= $(patsubst %.s,$(OBJDIR)/%.o,$(ASMSRCS))
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
