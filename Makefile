TARGET = firmware
NUCLEI_SDK_ROOT = ../nuclei-sdk
SRCDIRS = . lib/hagl/src lib/hagl_hal/src
INCDIRS = . lib/hagl/include lib/hagl_hal/include
COMMON_FLAGS += -O2 --std=gnu99 -DHAGL_HAL_USE_DOUBLE_BUFFER
LDFLAGS += -lm
LINKER_SCRIPT = gd32vf103cbt6.ld
PFLOAT = 1
JLINK = JLinkExe

include $(NUCLEI_SDK_ROOT)/Build/Makefile.base

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) $< -O ihex $(TARGET).hex

upload-jlink: $(TARGET).hex
	@$(ECHO) "Download and run $<"
	$(JLINK) -device GD32VF103VBT6 -speed 4000 -if JTAG -jtagconf -1,-1 -autoconnect 1 -CommanderScript upload.jlink

#  dfu-util -d 28e9:0189 -a 0 --dfuse-address 0x08000000:leave -D firmware.bin
