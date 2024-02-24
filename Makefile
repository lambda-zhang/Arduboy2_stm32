##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [4.2.0-B44] date: [Tue Feb 20 12:11:04 CST 2024] 
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = Arduboy2_stm32f103c8t6


######################################
# building variables
######################################
# debug build?
DEBUG ?= 0
# optimization
OPT = -Os


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Core/Src/main.c \
Core/Src/stm32f1xx_it.c \
Core/Src/stm32f1xx_hal_msp.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd_ex.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_usb.c \
Core/Src/system_stm32f1xx.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2c.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c \
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c

# CPP sources
CPP_SOURCE = \
lib/Arduboy2/src/Arduboy2.cpp \
lib/Arduboy2/src/Arduboy2Audio.cpp \
lib/Arduboy2/src/Arduboy2Beep.cpp \
lib/Arduboy2/src/Arduboy2Core.cpp \
lib/Arduboy2/src/Arduboy2Data.cpp \
lib/Arduboy2/src/Sprites.cpp \
lib/Arduboy2/src/SpritesB.cpp \
lib/Arduino/EEPROM.cpp \
lib/Arduino/Arduino.cpp \
lib/Arduino/Print.cpp \
lib/Arduino/Arduino_bsp_stm32f104c8t6.cpp \
lib/ArduboyPlaytune/src/ArduboyPlaytune.cpp \
lib/ArduboyTones/src/ArduboyTones.cpp \
Core/Src/Arduboy2_app.cpp \
examples/ArduBreakout.cpp \
examples/BeepDemo.cpp \
examples/Buttons.cpp \
examples/FontDemo.cpp \
examples/HelloWorld.cpp \
examples/RGBled.cpp \
examples/SetSystemEEPROM.cpp \
examples/PlayTune.cpp \
examples/halloweend.cpp \
examples/rund.cpp \
examples/ardynia/src/drawBitmap.cpp \
examples/ardynia/src/entity.cpp \
examples/ardynia/src/game.cpp \
examples/ardynia/src/hud.cpp \
examples/ardynia/src/inGameMenu.cpp \
examples/ardynia/src/loadEntity.cpp \
examples/ardynia/src/map.cpp \
examples/ardynia/src/renderer.cpp \
examples/ardynia/src/sfx.cpp \
examples/ardynia/src/state.cpp \
examples/ardynia/src/tileRoom.cpp \
examples/ardynia/src/util.cpp \
examples/ardynia/src/entities/bat.cpp \
examples/ardynia/src/entities/blob.cpp \
examples/ardynia/src/entities/blobMother.cpp \
examples/ardynia/src/entities/bomb.cpp \
examples/ardynia/src/entities/boomerang.cpp \
examples/ardynia/src/entities/chest.cpp \
examples/ardynia/src/entities/commonEnemy.cpp \
examples/ardynia/src/entities/explosion.cpp \
examples/ardynia/src/entities/lock.cpp \
examples/ardynia/src/entities/nemesis.cpp \
examples/ardynia/src/entities/player.cpp \
examples/ardynia/src/entities/pot.cpp \
examples/ardynia/src/entities/projectile.cpp \
examples/ardynia/src/entities/secretWall.cpp \
examples/ardynia/src/entities/skeleton.cpp \
examples/ardynia/src/entities/snake.cpp \
examples/ardynia/src/entities/spike.cpp \
examples/ardynia/src/entities/switch.cpp \
examples/ardynia/src/entities/sword.cpp \
examples/ardynia/src/entities/torch.cpp \
examples/ardynia/src/entities/triggerDoor.cpp \
examples/ardynia/ardynia.cpp \
examples/CastleBoy/CastleBoy/entity.cpp \
examples/CastleBoy/CastleBoy/game.cpp \
examples/CastleBoy/CastleBoy/global.cpp \
examples/CastleBoy/CastleBoy/map.cpp \
examples/CastleBoy/CastleBoy/menu.cpp \
examples/CastleBoy/CastleBoy/player.cpp \
examples/CastleBoy/CastleBoy/CastleBoy.cpp \
examples/FlappyBall/FlappyBall.cpp \
examples/Arduboy3D/Source/Arduboy3D/Draw.cpp \
examples/Arduboy3D/Source/Arduboy3D/Enemy.cpp \
examples/Arduboy3D/Source/Arduboy3D/Entity.cpp \
examples/Arduboy3D/Source/Arduboy3D/FixedMath.cpp \
examples/Arduboy3D/Source/Arduboy3D/Font.cpp \
examples/Arduboy3D/Source/Arduboy3D/Game.cpp \
examples/Arduboy3D/Source/Arduboy3D/Map.cpp \
examples/Arduboy3D/Source/Arduboy3D/MapGenerator.cpp \
examples/Arduboy3D/Source/Arduboy3D/Menu.cpp \
examples/Arduboy3D/Source/Arduboy3D/Particle.cpp \
examples/Arduboy3D/Source/Arduboy3D/Player.cpp \
examples/Arduboy3D/Source/Arduboy3D/Projectile.cpp \
examples/Arduboy3D/Source/Arduboy3D/Sounds.cpp \
examples/Arduboy3D/Source/Arduboy3D/Arduboy3D.cpp \
examples/ShadowRunner/ShadowRunner.cpp \
examples/ID-34-Mystic-Balloon/MYBL_AB/MYBL_AB.cpp \
examples/ArduboyTetris/Background.cpp \
examples/ArduboyTetris/Piece.cpp \
examples/ArduboyTetris/Tetris.cpp

# ASM sources
ASM_SOURCES =  \
startup_stm32f103xb.s

# ASM sources
ASMM_SOURCES = 


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
CPP = $(GCC_PATH)/$(PREFIX)g++
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
CPP = $(PREFIX)g++
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m3

# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi


# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F103xB

# CPP defines
CPP_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F103xB

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-ICore/Inc \
-IDrivers/STM32F1xx_HAL_Driver/Inc \
-IDrivers/STM32F1xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS/Device/ST/STM32F1xx/Include \
-IDrivers/CMSIS/Include

# CPP includes
CPP_INCLUDES =  \
-Ilib/Arduboy2/src \
-Ilib/Arduino \
-Ilib/ArduboyPlaytune/src \
-Ilib/ArduboyTones/src


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

# compile g++ flags
CPPFLAGS += $(MCU) $(C_DEFS) $(CPP_INCLUDES) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -fno-rtti -fno-exceptions

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
CPPFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
CPPFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F103C8Tx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections -lstdc++

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(C_SOURCES:.c=.o))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of cpp objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(CPP_SOURCE:.cpp=.o))
vpath %.cpp $(sort $(dir $(CPP_SOURCE)))

# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(ASM_SOURCES:.s=.o))
vpath %.s $(sort $(dir $(ASM_SOURCES)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(ASMM_SOURCES:.S=.o))
vpath %.S $(sort $(dir $(ASMM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@echo CC $<
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(<:.c=.lst) $< -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	@echo CPP $<
	@mkdir -p $(dir $@)
	@$(CPP) -c $(CPPFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(<:.cpp=.lst) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
