##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [4.2.0-B44] date: [Tue Mar 19 21:12:43 CST 2024]
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
APP_BUBBLEPOP ?= 0
APP_DUNGEONS ?= 0
APP_ESCAPERDROID ?= 0
APP_BLOBATTACK ?= 0
APP_BEGEMMED ?= 0
APP_RMH ?= 0
APP_ECOMD ?= 0
APP_TROLLYFISH ?= 0
APP_DICEOFFATE ?= 0
APP_VIRUSLQP79 ?= 0
APP_SIRENE ?= 0
APP_PINBALL ?= 0
APP_ARDUVENTURE ?= 0
APP_HELMETSHORDES ?= 0
APP_FANTASYRAMPAGE ?= 0
APP_OUTPOSTDEFENSE ?= 0
APP_SUNFIRE ?= 0
APP_EEPROMTOOL ?= 0
APP_DARKANDUNDER ?= 0
APP_SANSAN ?= 0
APP_NIGHTRAID ?= 0
APP_SPACEFIGHTER ?= 0
APP_OMEGACHASE ?= 0
APP_HUMANITYREVENGEDC ?= 0
APP_COSMICPODS ?= 0
APP_ARDUBOYARCODIA ?= 0
APP_MINIROGUE ?= 0
APP_BOMBERBOY ?= 0
APP_MINESWEEPER ?= 0
APP_2048 ?= 0
APP_ARDUMAN ?= 0
APP_MICROCITY ?= 0

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
lib/Arduino/HardwareSerial.cpp \
lib/Arduino/WString.cpp \
Core/Src/Arduboy2_app.cpp

# lambda:
APP_CPP_INCLUDES =
APP_SND_DEFS =

ifeq ($(APP_ARDUBREAKOUT), 1)
CPP_SOURCE += examples/ArduBreakout.cpp
endif
ifeq ($(APP_BEEPDEMO), 1)
CPP_SOURCE += examples/BeepDemo.cpp
endif
ifeq ($(APP_BUTTONS), 1)
CPP_SOURCE += examples/Buttons.cpp
endif
ifeq ($(APP_FONTDEMO), 1)
CPP_SOURCE += examples/FontDemo.cpp
endif
ifeq ($(APP_HELLOWORLD), 1)
CPP_SOURCE += examples/HelloWorld.cpp
endif
ifeq ($(APP_RGBLED), 1)
CPP_SOURCE += examples/RGBled.cpp
endif
ifeq ($(APP_SETSYSTEMEEPROM), 1)
CPP_SOURCE += examples/SetSystemEEPROM.cpp
endif
ifeq ($(APP_PLAYTUNE), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyPlaytune/src
APP_SND_DEFS += -DSND1_ARDUBOYPLAYTUNE
CPP_SOURCE += lib/ArduboyPlaytune/src/ArduboyPlaytune.cpp
CPP_SOURCE += examples/PlayTune.cpp
endif
ifeq ($(APP_RUND), 1)
CPP_SOURCE += examples/arduboy-rund-ino/rund/rund.cpp
endif
ifeq ($(APP_HALLOWEEND), 1)
CPP_SOURCE += examples/arduboy-rund-ino/halloweend/halloweend.cpp
endif
ifeq ($(APP_ARDYNIA), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyPlaytune/src
APP_SND_DEFS += -DSND1_ARDUBOYPLAYTUNE
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
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
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
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/FlappyBall/FlappyBall.cpp
endif
ifeq ($(APP_ARDUBOY3D), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
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
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/ID-15-Shadow-Runner/SHRUN_AB/SHRUN_AB.cpp
endif
ifeq ($(APP_MYSTICBALLOON), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/ID-34-Mystic-Balloon/MYBL_AB/MYBL_AB.cpp
endif
ifeq ($(APP_ARDUBOYTETRIS), 1)
CPP_SOURCE += examples/ArduboyTetris/Background.cpp \
	examples/ArduboyTetris/Piece.cpp \
	examples/ArduboyTetris/Tetris.cpp
endif
ifeq ($(APP_BUBBLEPOP), 1)
APP_CPP_INCLUDES += -Ilib/ATMlib/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/ID-14-Bubble-PoP/BPOP_AB/BPOP_AB.cpp
endif
ifeq ($(APP_DUNGEONS), 1)
CPP_SOURCE += examples/ID-10-Dungeons/DUN_AB/DUN_AB.cpp
endif
ifeq ($(APP_ESCAPERDROID), 1)
CPP_SOURCE += examples/ID-20-Escaper-Droid/ESCD_AB/ESCD_AB.cpp
endif
ifeq ($(APP_BLOBATTACK), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/ID-28-Blob-Attack/BLBA_AB/BLBA_AB.cpp
endif
ifeq ($(APP_BEGEMMED), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/ID-30-BEGEMMED/BGEM_AB/BGEM_AB.cpp
endif
ifeq ($(APP_RMH), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/ID-31-RMH/RMH_AB/RMH_AB.cpp
endif
ifeq ($(APP_ECOMD), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/ID-33-ECOMD/ECOMD_AB/ECOMD_AB.cpp
endif
ifeq ($(APP_TROLLYFISH), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/ID-36-Trolly-Fish/FISH_AB/FISH_AB.cpp
endif
ifeq ($(APP_DICEOFFATE), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/ID-37-DICE-of-FATE/DICE_AB/DICE_AB.cpp
endif
ifeq ($(APP_VIRUSLQP79), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/ID-40-VIRUS-LQP-79/VLQP_AB/VLQP_AB.cpp \
	examples/ID-40-VIRUS-LQP-79/VLQP_AB/bullet.cpp \
	examples/ID-40-VIRUS-LQP-79/VLQP_AB/door.cpp \
	examples/ID-40-VIRUS-LQP-79/VLQP_AB/elements.cpp \
	examples/ID-40-VIRUS-LQP-79/VLQP_AB/enemies.cpp \
	examples/ID-40-VIRUS-LQP-79/VLQP_AB/game.cpp \
	examples/ID-40-VIRUS-LQP-79/VLQP_AB/globals.cpp \
	examples/ID-40-VIRUS-LQP-79/VLQP_AB/level.cpp \
	examples/ID-40-VIRUS-LQP-79/VLQP_AB/menu.cpp \
	examples/ID-40-VIRUS-LQP-79/VLQP_AB/pickup.cpp \
	examples/ID-40-VIRUS-LQP-79/VLQP_AB/player.cpp
endif
ifeq ($(APP_SIRENE), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/ID-42-Sirene/SRN_AB/SRN_AB.cpp
endif
ifeq ($(APP_PINBALL), 1)
CPP_SOURCE += examples/ID-44-Pinball/PNBL_AB/PNBL_AB.cpp
endif
ifeq ($(APP_ARDUVENTURE), 1)
APP_CPP_INCLUDES += -Ilib/ATMlib/src
APP_SND_DEFS += -DSND3_ATMLIB
CPP_SOURCE += lib/ATMlib/src/ATMlib.cpp
CPP_SOURCE += examples/ID-46-Arduventure/ARDU_AB/ARDU_AB.cpp
endif
ifeq ($(APP_HELMETSHORDES), 1)
APP_CPP_INCLUDES += -Ilib/ATMlib/src
CPP_SOURCE += examples/ID-47-Helmets-Hordes/HEHO_AB/HEHO_AB.cpp
endif
ifeq ($(APP_FANTASYRAMPAGE), 1)
APP_CPP_INCLUDES += -Ilib/ATMlib/src
APP_SND_DEFS += -DSND3_ATMLIB
CPP_SOURCE += lib/ATMlib/src/ATMlib.cpp
CPP_SOURCE += examples/ID-48-Fantasy-Rampage/FRMP_AB/FRMP_AB.cpp
endif
ifeq ($(APP_OUTPOSTDEFENSE), 1)
APP_CPP_INCLUDES += -Ilib/ATMlib/src
CPP_SOURCE += examples/ID-49-Outpost-Defense/OPDE_AB/OPDE_AB.cpp
endif
ifeq ($(APP_SUNFIRE), 1)
APP_CPP_INCLUDES += -Ilib/ATMlib/src
APP_SND_DEFS += -DSND3_ATMLIB
CPP_SOURCE += lib/ATMlib/src/ATMlib.cpp
CPP_SOURCE += examples/ID-50-Sunfire/SUNF_AB/SUNF_AB.cpp
endif
ifeq ($(APP_EEPROMTOOL), 1)
CPP_SOURCE += examples/ID-51-EEPROM-TOOL/ERTL_AB/ERTL_AB.cpp
endif
ifeq ($(APP_DARKANDUNDER), 1)
CPP_SOURCE += examples/Dark-And-Under/Dark-And-Under/src/controllers/BaseController.cpp \
	examples/Dark-And-Under/Dark-And-Under/src/controllers/EnemyController.cpp \
	examples/Dark-And-Under/Dark-And-Under/src/controllers/PlayerController.cpp \
	examples/Dark-And-Under/Dark-And-Under/src/entities/Base.cpp \
	examples/Dark-And-Under/Dark-And-Under/src/entities/Enemy.cpp \
	examples/Dark-And-Under/Dark-And-Under/src/entities/Item.cpp \
	examples/Dark-And-Under/Dark-And-Under/src/entities/Player.cpp \
	examples/Dark-And-Under/Dark-And-Under/src/fonts/Font3x5.cpp \
	examples/Dark-And-Under/Dark-And-Under/src/levels/Level.cpp \
	examples/Dark-And-Under/Dark-And-Under/src/utils/Arduboy2Ext.cpp \
	examples/Dark-And-Under/Dark-And-Under/src/utils/EnemyNames.cpp \
	examples/Dark-And-Under/Dark-And-Under/Dark-And-Under.cpp
endif
ifeq ($(APP_SANSAN), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/sansan/bitmaps.cpp \
	examples/sansan/obj.cpp \
	examples/sansan/sin.cpp \
	examples/sansan/sansan.cpp
endif
ifeq ($(APP_NIGHTRAID), 1)
CPP_SOURCE += examples/night-raid/night-raid.cpp
endif
ifeq ($(APP_SPACEFIGHTER), 1)
CPP_SOURCE += examples/SpaceFighter/SpaceFighter.cpp \
	examples/SpaceFighter/SpaceFigther_bitmaps.cpp \
	examples/SpaceFighter/collision.cpp \
	examples/SpaceFighter/draw.cpp \
	examples/SpaceFighter/generator.cpp \
	examples/SpaceFighter/movement.cpp
endif
ifeq ($(APP_OMEGACHASE), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/OmegaChase/Omega_chase_V_1_0.cpp
endif
ifeq ($(APP_HUMANITYREVENGEDC), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/Humanity_Revenge_DC/Humanity_Revenge_DC.cpp
endif
ifeq ($(APP_COSMICPODS), 1)
CPP_SOURCE += examples/CosmicPods/CosmicPods.cpp
endif
ifeq ($(APP_ARDUBOYARCODIA), 1)
CPP_SOURCE += examples/ArduboyArcodia/Arcodia.cpp
endif
ifeq ($(APP_MINIROGUE), 1)
CPP_SOURCE += examples/MiniRogue/MiniRogue/MiniRogue.cpp \
	examples/MiniRogue/MiniRogue/src/Game.cpp \
	examples/MiniRogue/MiniRogue/src/fonts/Font3x5.cpp \
	examples/MiniRogue/MiniRogue/src/states/BaseState.cpp \
	examples/MiniRogue/MiniRogue/src/states/EventState.cpp \
	examples/MiniRogue/MiniRogue/src/states/FightMonstersState.cpp \
	examples/MiniRogue/MiniRogue/src/states/GameOverState.cpp \
	examples/MiniRogue/MiniRogue/src/states/MerchantState.cpp \
	examples/MiniRogue/MiniRogue/src/states/RestingState.cpp \
	examples/MiniRogue/MiniRogue/src/states/ShowCardsState.cpp \
	examples/MiniRogue/MiniRogue/src/states/SplashScreenState.cpp \
	examples/MiniRogue/MiniRogue/src/states/TitleScreenState.cpp \
	examples/MiniRogue/MiniRogue/src/states/TrapState.cpp \
	examples/MiniRogue/MiniRogue/src/states/TreasureState.cpp \
	examples/MiniRogue/MiniRogue/src/utils/Arduboy2Ext.cpp \
	examples/MiniRogue/MiniRogue/src/utils/GameContext.cpp
endif
ifeq ($(APP_BOMBERBOY), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/Bomberboy/Bomberboy/Game.cpp \
	examples/Bomberboy/Bomberboy/Map.cpp \
	examples/Bomberboy/Bomberboy/Menu.cpp \
	examples/Bomberboy/Bomberboy/Player.cpp \
	examples/Bomberboy/Bomberboy/Unit.cpp \
	examples/Bomberboy/Bomberboy/assets.cpp \
	examples/Bomberboy/Bomberboy/audio.cpp \
	examples/Bomberboy/Bomberboy/Bomberboy.cpp
endif
ifeq ($(APP_MINESWEEPER), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyTones/src
APP_SND_DEFS += -DSND2_ARDUBOYTONES
CPP_SOURCE += lib/ArduboyTones/src/ArduboyTones.cpp
CPP_SOURCE += examples/minesweeper/minesweeper.cpp
endif
ifeq ($(APP_2048), 1)
CPP_SOURCE += examples/2048-Arduboy/2048-Arduboy/2048-Arduboy.cpp \
	examples/2048-Arduboy/2048-Arduboy/controller.cpp \
	examples/2048-Arduboy/2048-Arduboy/draw.cpp \
	examples/2048-Arduboy/2048-Arduboy/font.cpp \
	examples/2048-Arduboy/2048-Arduboy/game.cpp \
	examples/2048-Arduboy/2048-Arduboy/stars.cpp \
	examples/2048-Arduboy/2048-Arduboy/utils.cpp
endif
ifeq ($(APP_ARDUMAN), 1)
APP_CPP_INCLUDES += -Ilib/ArduboyPlaytune/src
APP_SND_DEFS += -DSND1_ARDUBOYPLAYTUNE
CPP_SOURCE += lib/ArduboyPlaytune/src/ArduboyPlaytune.cpp
CPP_SOURCE += examples/arduman/ardu_main.cpp \
	examples/arduman/arduman.cpp \
	examples/arduman/Fruit.cpp \
	examples/arduman/Ghost.cpp \
	examples/arduman/Highscores.cpp \
	examples/arduman/Player.cpp \
	examples/arduman/Utils.cpp \
	examples/arduman/ab_printer.cpp
endif
ifeq ($(APP_MICROCITY), 1)
CPP_SOURCE += examples/MicroCity/Source/MicroCity/Building.cpp \
	examples/MicroCity/Source/MicroCity/Connectivity.cpp \
	examples/MicroCity/Source/MicroCity/Draw.cpp \
	examples/MicroCity/Source/MicroCity/Font.cpp \
	examples/MicroCity/Source/MicroCity/Game.cpp \
	examples/MicroCity/Source/MicroCity/Interface.cpp \
	examples/MicroCity/Source/MicroCity/MicroCity.cpp \
	examples/MicroCity/Source/MicroCity/Simulation.cpp \
	examples/MicroCity/Source/MicroCity/Strings.cpp \
	examples/MicroCity/Source/MicroCity/Terrain.cpp
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
C_DEFS =  $(APP_SND_DEFS) \
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
CPP_INCLUDES =  $(APP_CPP_INCLUDES) \
-Ilib/Arduboy2/src \
-Ilib/Arduino


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -fsigned-char

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -fsigned-char

# compile g++ flags
CPPFLAGS += $(MCU) $(C_DEFS) $(CPP_INCLUDES) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -fno-rtti -fno-exceptions -fsigned-char

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
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections -lstdc++ -fsigned-char

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
