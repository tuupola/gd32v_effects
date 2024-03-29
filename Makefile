TARGET = firmware
NUCLEI_SDK_ROOT = ../nuclei-sdk
# Remove comment if using self compiled toolchain
COMPILE_PREFIX = riscv64-unknown-elf-
SRCDIRS = . lib/hagl/src lib/hagl_hal/src
INCDIRS = . lib/hagl/include lib/hagl_hal/include
COMMON_FLAGS += -O2 --std=gnu99
# For Longan Nano
COMMON_FLAGS += -DHAGL_HAL_USE_DOUBLE_BUFFER #-include ./longan_nano.h
#COMMON_FLAGS += -DHAGL_HAL_USE_SINGLE_BUFFER #-include ./longan_nano.h
# For TTGO T-Display GD32.
# This will be slow since there is not enough memory for double buffering.
# COMMON_FLAGS += -include ./ttgo_t_display.h
LDFLAGS += -lm
PFLOAT = 1
JLINK = JLinkExe

include $(NUCLEI_SDK_ROOT)/Build/Makefile.base

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) $< -O ihex $(TARGET).hex

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) $< -O binary $(TARGET).bin

upload-jlink: $(TARGET).hex
	@$(ECHO) "Download and run $<"
	$(JLINK) -device GD32VF103VBT6 -speed 4000 -if JTAG -jtagconf -1,-1 -autoconnect 1 -CommanderScript upload.jlink

upload-dfu: $(TARGET).bin
	@$(ECHO) "Download and run $<"
	dfu-util -d 28e9:0189 -a 0 --dfuse-address 0x08000000:leave -D $(TARGET).bin