
###########################################################################

.PHONY: all clean install makedirs

###########################################################################

# Target binary file
TARGET		:= test_library.library

# Object Dir
OBJDIR		:= obj

# Binary Dir
BINDIR		:= bin

# Install Dir (Amiga target path)
INSTALLDIR	:= sys:libs

# Compiler Flags
CFLAGS		:= -O2
CFLAGS		+= -I.
CFLAGS		+= -Iinc_public
CFLAGS		+= -W
CFLAGS		+= -Wall
CFLAGS		+= -Wl,--cref,-M,-Map=$(TARGET).map
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

SRCS		+= src/_main_Obtain.c
SRCS		+= src/_main_Release.c
SRCS		+= src/_main_Expunge.c
SRCS		+= src/_main_Clone.c
SRCS		+= src/_main_FuncAdd.c

SRCS		+= src/Resources.c
SRCS		+= src/Resources_Init.c
SRCS		+= src/Resources_Free.c

SRCS		+= src/Debug.c
SRCS		+= src/Library.c

###########################################################################

OBJS		:= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
DEPS		:= $(patsubst %.c,$(OBJDIR)/%.d,$(SRCS))

all: $(BINDIR)/$(TARGET)

###############################################################################

$(BINDIR)/$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $(LDFLAGS) -o $(BINDIR)/$(TARGET) $(OBJS) $(LIBS)

$(BINDIR):
	$(MKDIR) $(BINDIR)

###############################################################################

# Include dependency files
-include $(DEPS)

###############################################################################

clean:
	$(RM) $(OBJDIR) $(DEPS) $(BINDIR)/$(TARGET) $(TARGET).map

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
