TARGET = firmware
# RTOS = FreeRTOS
NUCLEI_SDK_ROOT = ../nuclei-sdk
SRCDIRS = . src components/hagl/src components/hagl_gd32v_mipi/src
INCDIRS = . include components/hagl/include components/hagl_gd32v_mipi/include
# COMMON_FLAGS := -O2 --std=gnu99 -D_POSIX_C_SOURCE=199309
COMMON_FLAGS := -O2 --std=gnu99
LDFLAGS = -lm

PFLOAT = 1

JLINK = JLinkExe

include $(NUCLEI_SDK_ROOT)/Build/Makefile.base

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) $< -O ihex $(TARGET).hex

upload-jlink: $(TARGET).hex
	@$(ECHO) "Download and run $<"
	$(JLINK) -device GD32VF103VBT6 -speed 1000 -if JTAG -jtagconf -1,-1 -autoconnect 1 -CommanderScript upload.jlink

#  dfu-util -d 28e9:0189 -a 0 --dfuse-address 0x08000000:leave -D firmware.bin
