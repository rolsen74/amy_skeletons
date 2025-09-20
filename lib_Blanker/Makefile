
###########################################################################

.PHONY: all clean install makedirs

###########################################################################

# Target binary file
TARGET		:= test_blanker.blanker

# Object Dir
OBJDIR		:= obj

# Binary Dir
BINDIR		:= bin

# Install Dir (Amiga target path)
INSTALLDIR	:= sys:Utilities/Blankers

# Compiler Flags
CFLAGS		:= -O2
CFLAGS		+= -I.
CFLAGS		+= -W
CFLAGS		+= -Wall
CFLAGS		+= -D__USE_INLINE__

# Create .d files (optinal)
CFLAGS		+= -MMD
CFLAGS		+= -MP

# Add debug info like source file / line nr ( huge binary file )
CFLAGS		+= -gstabs

# Print Error Messages on serial
CFLAGS		+= -DDO_ERROR

# Print Info Messages on serial
CFLAGS		+= -DDO_INFO

# Print Debug Messages on serial
CFLAGS		+= -DDO_DEBUG

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

SRCS		+= src/_man_Obtain.c
SRCS		+= src/_man_Release.c
SRCS		+= src/_man_Open.c
SRCS		+= src/_man_Close.c
SRCS		+= src/_man_Expunge.c
SRCS		+= src/_man_Init.c

SRCS		+= src/_blanker_Obtain.c
SRCS		+= src/_blanker_Release.c
SRCS		+= src/_blanker_Clone.c
SRCS		+= src/_blanker_Expunge.c
SRCS		+= src/_blanker_Get.c
SRCS		+= src/_blanker_Set.c
SRCS		+= src/_blanker_Blank.c

SRCS		+= src/Resources.c
SRCS		+= src/Resources_Init.c
SRCS		+= src/Resources_Free.c

SRCS		+= src/Debug.c
SRCS		+= src/Library.c

SRCS		+= src/Blanker_Init.c
SRCS		+= src/Blanker_Free.c
SRCS		+= src/Blanker_Render_Main.c
SRCS		+= src/Blanker_Render_Preview.c
SRCS		+= src/Blanker_Render_Screen.c

SRCS		+= src/GUI_Create.c
SRCS		+= src/GUI_Handle.c
SRCS		+= src/GUI_Refresh.c

SRCS		+= src/Settings_Default.c
SRCS		+= src/Settings_Load.c
SRCS		+= src/Settings_Save.c

###########################################################################

OBJS		:= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
DEPS		:= $(patsubst %.c,$(OBJDIR)/%.d,$(SRCS))

all: $(BINDIR)/$(TARGET)

###############################################################################

$(BINDIR)/$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $(LDFLAGS) -o $(BINDIR)/$(TARGET) $(OBJS) $(LIBS) -Wl,--cref,-M,-Map=$(TARGET).map

$(BINDIR):
	$(MKDIR) $(BINDIR)

###############################################################################

# Include dependency files
-include $(DEPS)

###############################################################################

clean:
	$(RM) $(OBJS) $(DEPS) $(BINDIR)/$(TARGET) $(TARGET).map

###############################################################################

install:
ifeq ($(HOSTOS),AmigaOS)
	$(COPY) $(BINDIR)/$(TARGET) $(INSTALLDIR)
else
	@echo "Install is AmigaOS-oriented. On Linux, copy manually to target media:"
	@echo "  $(COPY) $(BINDIR)/$(TARGET) <your-amiga-volume>/devs/"
endif

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
