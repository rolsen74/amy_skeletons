
###########################################################################

.PHONY: all clean install makedirs

###########################################################################

# Target binary file
TARGET		:= test_sana2.device

# Object Dir
OBJDIR		:= obj

# Binary Dir
BINDIR		:= bin

# Install Dir (Amiga target path)
INSTALLDIR	:= devs:Networks

# Compiler Flags
CFLAGS		:= -O2
CFLAGS		+= -I.
CFLAGS		+= -W
CFLAGS		+= -Wall
CFLAGS		+= -D__USE_INLINE__

# Save .map file with compile informations (optional)
CFLAGS		+= -Wl,--cref,-M,-Map=$(TARGET).map

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
SRCS		+= src/_man_AbortIO.c
SRCS		+= src/_man_BeginIO.c
SRCS		+= src/_man_Init.c

SRCS		+= src/_cmd_0002_Read.c
SRCS		+= src/_cmd_0003_Write.c
SRCS		+= src/_cmd_0008_Flush.c
SRCS		+= src/_cmd_0009_S2_DeviceQuery.c
SRCS		+= src/_cmd_000A_S2_GetStationAddress.c
SRCS		+= src/_cmd_000B_S2_ConfigInterface.c
SRCS		+= src/_cmd_000E_S2_AddMulticastAddress.c
SRCS		+= src/_cmd_000F_S2_DelMulticastAddress.c
SRCS		+= src/_cmd_0010_S2_Multicast.c
SRCS		+= src/_cmd_0011_S2_Broadcast.c
SRCS		+= src/_cmd_0015_S2_GetSpecialStats.c
SRCS		+= src/_cmd_0016_S2_GetGlobalStats.c
SRCS		+= src/_cmd_0017_S2_OnEvent.c
SRCS		+= src/_cmd_0018_S2_ReadOrphan.c
SRCS		+= src/_cmd_0019_S2_Online.c
SRCS		+= src/_cmd_001A_S2_Offline.c
SRCS		+= src/_cmd_4000_DeviceQuery.c
SRCS		+= src/_cmd_C004_S2_GetExtendedGlobalStats.c
SRCS		+= src/_cmd_C007_S2_Sample_ThroughPut.c
SRCS		+= src/_cmd_C008_S2_Sana2Hook.c

SRCS		+= src/Unit_Alloc.c
SRCS		+= src/Unit_Free.c
SRCS		+= src/Unit_Startup.c

SRCS		+= src/Resources.c
SRCS		+= src/Resources_Init.c
SRCS		+= src/Resources_Free.c

SRCS		+= src/Process.c
SRCS		+= src/Process_Init.c
SRCS		+= src/Process_Main.c
SRCS		+= src/Process_Free.c
SRCS		+= src/Process_Handle_AbortIO.c
SRCS		+= src/Process_Handle_BeginIO.c

SRCS		+= src/Abort_All.c
SRCS		+= src/Abort_IOReq.c
SRCS		+= src/Debug.c
SRCS		+= src/Device.c
SRCS		+= src/Event_Check.c
SRCS		+= src/Packet_Read_Handle.c
SRCS		+= src/Packet_Read_Done.c
SRCS		+= src/Packet_Send_Schedule.c
SRCS		+= src/Packet_Send_Done.c

###########################################################################

OBJS		:= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
DEPS		:= $(patsubst %.c,$(OBJDIR)/%.d,$(SRCS))

all: $(BINDIR)/$(TARGET)

###########################################################################

$(BINDIR)/$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $(LDFLAGS) -o $(BINDIR)/$(TARGET) $(OBJS) $(LIBS)

$(BINDIR):
	$(MKDIR) $(BINDIR)

###########################################################################

# Include dependency files
-include $(DEPS)

###########################################################################

clean:
	$(RM) $(OBJDIR) $(DEPS) $(BINDIR)/$(TARGET) $(TARGET).map

###########################################################################

install:
ifeq ($(HOSTOS),AmigaOS)
	$(COPY) $(BINDIR)/$(TARGET) $(INSTALLDIR)
else
	@echo "Install is AmigaOS-oriented. On Linux, copy manually to target media:"
	@echo "  $(COPY) $(BINDIR)/$(TARGET) <your-amiga-volume>/devs/"
endif

###########################################################################

strip:
	@$(LS)		$(BINDIR)/$(TARGET)
	@$(STRIP)	$(BINDIR)/$(TARGET)
	@$(LS)		$(BINDIR)/$(TARGET)

###########################################################################

$(OBJDIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

###########################################################################
