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

APP_ARDUBREAKOUT ?= 0
APP_BEEPDEMO ?= 0
APP_BUTTONS ?= 0
APP_FONTDEMO ?= 0
APP_HELLOWORLD ?= 0
APP_RGBLED ?= 0
APP_SETSYSTEMEEPROM ?= 0
APP_PLAYTUNE ?= 0
APP_RUND ?= 0
APP_HALLOWEEND ?= 0
APP_ARDYNIA ?= 0
APP_CASTLEBOY ?= 0
APP_FLAPPYBALL ?= 0
APP_ARDUBOY3D ?= 0
APP_SHADOWRUNNER ?= 0
APP_MYSTICBALLOON ?= 0
APP_ARDUBOYTETRIS ?= 0

APP_DEFS =


######################################
# building variables
######################################
# debug build?
DEBUG ?= 1
# optimization
OPT = -Og


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
Core/Src/Arduboy2_app.cpp

ifeq ($(APP_ARDUBREAKOUT), 1)
APP_DEFS = -DAPP_ARDUBREAKOUT
CPP_SOURCE += examples/ArduBreakout.cpp
endif
ifeq ($(APP_BEEPDEMO), 1)
APP_DEFS = -DAPP_BEEPDEMO
CPP_SOURCE += examples/BeepDemo.cpp
endif
ifeq ($(APP_BUTTONS), 1)
APP_DEFS = -DAPP_BUTTONS
CPP_SOURCE += examples/Buttons.cpp
endif
ifeq ($(APP_FONTDEMO), 1)
APP_DEFS = -DAPP_FONTDEMO
CPP_SOURCE += examples/FontDemo.cpp
endif
ifeq ($(APP_HELLOWORLD), 1)
APP_DEFS = -DAPP_HELLOWORLD
CPP_SOURCE += examples/HelloWorld.cpp
endif
ifeq ($(APP_RGBLED), 1)
APP_DEFS = -DAPP_RGBLED
CPP_SOURCE += examples/RGBled.cpp
endif
ifeq ($(APP_SETSYSTEMEEPROM), 1)
APP_DEFS = -DAPP_SETSYSTEMEEPROM
CPP_SOURCE += examples/SetSystemEEPROM.cpp
endif
ifeq ($(APP_PLAYTUNE), 1)
APP_DEFS = -DAPP_PLAYTUNE
CPP_SOURCE += lib/ArduboyPlaytune/src/ArduboyPlaytune.cpp
CPP_SOURCE += examples/PlayTune.cpp
endif
ifeq ($(APP_RUND), 1)
APP_DEFS = -DAPP_RUND
CPP_SOURCE += examples/rund.cpp
endif
ifeq ($(APP_HALLOWEEND), 1)
APP_DEFS = -DAPP_HALLOWEEND
CPP_SOURCE += examples/halloweend.cpp
endif
ifeq ($(APP_ARDYNIA), 1)
APP_DEFS = -DAPP_ARDYNIA
CPP_SOURCE += lib/ArduboyPlaytune/src/ArduboyPlaytune.cpp
CPP_SOURCE += examples/ardynia/src/drawBitmap.cpp \
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
	examples/ardynia/ardynia.cpp
endif
ifeq ($(APP_CASTLEBOY), 1)
APP_DEFS = -DAPP_CASTLEBOY
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/CastleBoy/CastleBoy/entity.cpp \
	examples/CastleBoy/CastleBoy/game.cpp \
	examples/CastleBoy/CastleBoy/global.cpp \
	examples/CastleBoy/CastleBoy/map.cpp \
	examples/CastleBoy/CastleBoy/menu.cpp \
	examples/CastleBoy/CastleBoy/player.cpp \
	examples/CastleBoy/CastleBoy/CastleBoy.cpp
endif
ifeq ($(APP_FLAPPYBALL), 1)
APP_DEFS = -DAPP_FLAPPYBALL
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/FlappyBall/FlappyBall.cpp
endif
ifeq ($(APP_ARDUBOY3D), 1)
APP_DEFS = -DAPP_ARDUBOY3D
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/Arduboy3D/Source/Arduboy3D/Draw.cpp \
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
	examples/Arduboy3D/Source/Arduboy3D/Arduboy3D.cpp
endif
ifeq ($(APP_SHADOWRUNNER), 1)
APP_DEFS = -DAPP_SHADOWRUNNER
CPP_SOURCE += examples/ShadowRunner/ShadowRunner.cpp
endif
ifeq ($(APP_MYSTICBALLOON), 1)
APP_DEFS = -DAPP_MYSTICBALLOON
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/ID-34-Mystic-Balloon/MYBL_AB/MYBL_AB.cpp
endif
ifeq ($(APP_ARDUBOYTETRIS), 1)
APP_DEFS = -DAPP_ARDUBOYTETRIS
CPP_SOURCE += examples/ArduboyTetris/Background.cpp \
	examples/ArduboyTetris/Piece.cpp \
	examples/ArduboyTetris/Tetris.cpp
endif

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

C_DEFS += $(APP_DEFS)
CPP_DEFS += $(APP_DEFS)

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
