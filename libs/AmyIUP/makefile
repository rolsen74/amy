
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
TARGET		:= AmyIUP.library

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
CFLAGS		+= -Wno-unused-parameter
CFLAGS		+= -MMD
CFLAGS		+= -MP
CFLAGS		+= -mcrt=amyclib

# Linker Flags
LDFLAGS		:= -mcrt=amyclib
LDFLAGS		+= -nostartfiles

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
SRCS		+= src/_Main/main_Obtain.c
SRCS		+= src/_Main/main_Release.c
SRCS		+= src/_Main/main_Clone.c
SRCS		+= src/_Main/main_Expunge.c
SRCS		+= src/_Main/iup_IupClose.c
SRCS		+= src/_Main/iup_IupMainLoop.c
SRCS		+= src/_Main/iup_IupOpen.c
SRCS		+= src/_Main/iup_IupSetGlobal.c

# UIP Source
SRCS		+= src/iup_array.c
SRCS		+= src/iup_attrib.c
SRCS		+= src/iup_box.c
SRCS		+= src/iup_button.c
SRCS		+= src/iup_callback.c
SRCS		+= src/iup_canvas.c
SRCS		+= src/iup_childtree.c
SRCS		+= src/iup_class.c
SRCS		+= src/iup_classattrib.c
SRCS		+= src/iup_classbase.c
SRCS		+= src/iup_classinfo.c
SRCS		+= src/iup_colorbar.c
SRCS		+= src/iup_colorbrowser.c
SRCS		+= src/iup_colordlg.c
SRCS		+= src/iup_colorhsi.c
SRCS		+= src/iup_datepick.c
SRCS		+= src/iup_dialog.c
SRCS		+= src/iup_dlglist.c
SRCS		+= src/iup_draw.c
SRCS		+= src/iup_elemprodpdlg.c
SRCS		+= src/iup_export.c
SRCS		+= src/iup_filedlg.c
SRCS		+= src/iup_fill.c
SRCS		+= src/iup_flatseparator.c
SRCS		+= src/iup_flattoggle.c
SRCS		+= src/iup_focus.c
SRCS		+= src/iup_font.c
SRCS		+= src/iup_fontdlg.c
SRCS		+= src/iup_frame.c
SRCS		+= src/iup_func.c
SRCS		+= src/iup_getparam.c
SRCS		+= src/iup_globalattrib.c
SRCS		+= src/iup_globaldlg.c
SRCS		+= src/iup_hbox.c
SRCS		+= src/iup_image.c
SRCS		+= src/iup_key.c
SRCS		+= src/iup_label.c
SRCS		+= src/iup_layout.c
SRCS		+= src/iup_layoutdlg.c
SRCS		+= src/iup_link.c
SRCS		+= src/iup_list.c
SRCS		+= src/iup_mask.c
SRCS		+= src/iup_maskmatch.c
SRCS		+= src/iup_maskparsed.c
SRCS		+= src/iup_menu.c
SRCS		+= src/iup_messagedlg.c
SRCS		+= src/iup_multibox.c
SRCS		+= src/iup_names.c
SRCS		+= src/iup_normalizer.c
SRCS		+= src/iup_object.c
SRCS		+= src/iup_open.c
SRCS		+= src/iup_predialogs.c
SRCS		+= src/iup_radio.c
SRCS		+= src/iup_register.c
SRCS		+= src/iup_sbox.c
SRCS		+= src/iup_show.c
SRCS		+= src/iup_space.c
SRCS		+= src/iup_split.c
SRCS		+= src/iup_str.c
SRCS		+= src/iup_strmessage.c
SRCS		+= src/iup_table.c
SRCS		+= src/iup_tabs.c
SRCS		+= src/iup_text.c
SRCS		+= src/iup_timer.c
SRCS		+= src/iup_toggle.c
SRCS		+= src/iup_tree.c
SRCS		+= src/iup_user.c
SRCS		+= src/iup_val.c
SRCS		+= src/iup_vbox.c

# UIP Source - Amiga Specific
SRCDIRS		:= src/_AOS4
SRCS		+= $(wildcard $(addsuffix /*.c, $(SRCDIRS)))

###########################################################################

OBJS		:= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
DEPS		:= $(patsubst %.c,$(OBJDIR)/%.d,$(SRCS))

all: $(BINDIR)/$(TARGET)

###############################################################################

$(BINDIR)/$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(BINDIR)/$(TARGET) $(OBJS) $(LIBS) -Wl,--cref,-M,-Map=AmyIUP.map

###############################################################################

# Include dependency files
-include $(DEPS)

###############################################################################

clean:
	$(RM) $(OBJS) $(DEPS) bin/$(TARGET) AmyIUP.map

elfinfo:
	@readelf -S $(BINDIR)/$(TARGET)

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
