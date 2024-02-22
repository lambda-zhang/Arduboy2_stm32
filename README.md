# 说明
原理图参考这个 [stm32_arduboy_V1.0](https://oshwhub.com/lambda_zhang/stm32_arduboy)

介绍视频参考这个： [stm32_arduboy_V1.0游戏机 - 介绍](https://www.bilibili.com/video/BV11b4y1A7qp/?share_source=copy_web&vd_source=aa0a3cf16c5fa8d0a52107104c68d663)

# 开发
## 开发环境准备
安装必要的软件包
```
$ sudo apt-get install build-essential git gdb-multiarch
```
从[这个链接](https://developer.arm.com/downloads/-/gnu-rm)下载gcc,找gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 ，解压到/opt

从[这个链接](https://gitee.com/xpack-dev-tools/openocd-xpack/releases/tag/v0.11.0-5)下载openocd，找xpack-openocd-0.11.0-5-linux-x64.tar.gz ，解压到/opt

## 编译
以编译ARDUBREAKOUT为例
```
$ export PATH=$PATH:/your/path/gcc-arm-none-eabi-10.3-2021.10/bin
$ make APP_ARDUBREAKOUT=1
```

## 下载到单片机
```
$ /your/path/xpack-openocd-0.12.0-1/bin/openocd -f config/jlink.cfg -f config/stm32f1x.cfg \
-c init -c "reset halt" -c wait_halt \
-c "flash write_image erase build/Arduboy2_stm32f103c8t6.bin 0x08000000" \
-c reset -c shutdown
```

## 调试
```
$ /your/path/xpack-openocd-0.12.0-1/bin/openocd -f config/jlink.cfg -f config/stm32f1x.cfg
$ gdb-multiarch build/Arduboy2_stm32f103c8t6.elf
(gdb) tar ext:3333
```

# 支持的应用和游戏
| 应用/游戏名称         | 分类  | 来源 | 编译方法  |
| ------------------- | ---- | ----- | ----- |
| ArduBreakout    | 游戏  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/ArduBreakout),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_ARDUBREAKOUT=1    |
| BeepDemo        | 应用  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/BeepDemo),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_BEEPDEMO=1        |
| Buttons         | 应用  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/Buttons),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_BUTTONS=1         |
| FontDemo        | 应用  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/FontDemo),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_FONTDEMO=1        |
| HelloWorld      | 应用  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/HelloWorld),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_HELLOWORLD=1      |
| RGBled          | 应用  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/RGBled),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_RGBLED=1          |
| SetSystemEEPROM | 应用  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/SetSystemEEPROM),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_SETSYSTEMEEPROM=1 |
| PlayTune        | 应用  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/PlayTune),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_PLAYTUNE=1        |
| arduboy-rund-ino | 游戏  | [这个链接](https://github.com/flaki/arduboy-rund-ino),[这次commit](https://github.com/flaki/arduboy-rund-ino/commit/ff8615fd457f08fd3a5ccc0434d67ee31ca87d8d) | make APP_RUND=1            |
| arduboy-rund-ino/halloweend | 游戏  | [这个链接](https://github.com/flaki/arduboy-rund-ino),[这次commit](https://github.com/flaki/arduboy-rund-ino/commit/ff8615fd457f08fd3a5ccc0434d67ee31ca87d8d) | make APP_HALLOWEEND=1      |
| Ardynia  | 游戏  | [这个链接](https://github.com/city41/ardynia),[这次commit](https://github.com/city41/ardynia/commit/23e1f2449c7f4919eb88f23faa40cbd141d05249) | make APP_ARDYNIA=1         |
| CastleBoy | 游戏  | [这个链接](https://github.com/jlauener/CastleBoy),[这次commit](https://github.com/jlauener/CastleBoy/commit/1d758fdd862d6269dc459661779c52d75cc87f98) | make APP_CASTLEBOY=1       |
| Flappy Ball | 游戏  | [这个链接](https://github.com/MLXXXp/FlappyBall),[这次commit](https://github.com/MLXXXp/FlappyBall/commit/263e70f240a6811541c3794d2d27bf8323d347a6) | make APP_FLAPPYBALL=1      |
| Catacombs of the damned! | 游戏  | [这个链接](https://github.com/jhhoward/Arduboy3D),[这次commit](https://github.com/jhhoward/Arduboy3D/commit/929db9f3429cc20a318934099d992f1219a081bd) | make APP_ARDUBOY3D=1       |
| Shadow Runner | 游戏  | [这个链接](https://github.com/Team-ARG-Museum/ID-15-Shadow-Runner/tree/master/SHRUN_AB),[这个commit](https://github.com/Team-ARG-Museum/ID-15-Shadow-Runner/commit/25f277508f28bd379deadba48ff2871f82970344) | make APP_SHADOWRUNNER=1    |
| Mystic Balloon | 游戏  | [这个链接](https://github.com/Gaveno/ID-34-Mystic-Balloon),[这次commit](https://github.com/Gaveno/ID-34-Mystic-Balloon/commit/a2ca9eee92016cf75ec1d6ea9f1126b2403549f5) | make APP_MYSTICBALLOON=1   |
| ArduboyTetris | 游戏  | [这个链接](https://github.com/Nautili/ArduboyTetris),[这次commit](https://github.com/Nautili/ArduboyTetris/commit/3cc72e452c4a7dd3737f72e728e165f666ef9e80) | make APP_ARDUBOYTETRIS=1   |

# 硬件连接
## swd+uart
| STM32F103C8T6 | FUNC           | JLINK | DESC  |
| ------------- | -------------- | ----- | ----- |
| PA9           | USART1_TX      | pin17 | TX    |
| PA13          | SYS_JTMS-SWDIO | pin7  | SWDIO |
| PA14          | SYS_JTCK-SWCLK | pin9  | SWCLK |

## usb
| STM32F103C8T6 | FUNC        | USB     | DESC   |
| ------------- | ----------- | ------- | ------ |
| PA11          | USB_DM      |         | USB_DM |
| PA12          | USB_DP      |         | USB_DP |
| PA8           | GPIO_Output |         | EN     |

## flash
| STM32F103C8T6 | FUNC        | Nor Flash PIN | DESC     |
| ------------- | ----------- | ------------- | -------- |
| PA4           | GPIO_Output | pin1          | CS       |
| PA5           | SPI1_SCK    | pin6          | CLK      |
| PA6           | SPI1_MISO   | pin2          | IO1/MISO |
| PA7           | SPI1_MOSI   | pin5          | IO0/MOSI |

## lcd IRQT17
| STM32F103C8T6 | FUNC        | IRQT17 PIN | DESC |
| ------------- | ----------- | ---------- | ---- |
| PA0           | GPIO_Output |            | BL   |
| PA1           | GPIO_Output | pin4       | CS   |
| PA15          | GPIO_Outout | pin5       | RST  |
| PA3           | GPIO_Outout | pin6       | DC   |
| PB13          | SPI2_SCK    | pin7       | SCL  |
| PB15          | SPI2_MOSI   | pin8       | SDA  |

## e2prom
| STM32F103C8T6 | FUNC     | AT24C02 PIN | DESC |
| ------------- | -------- | ----------- | ---- |
| PB6           | I2C1_SCL | pin6        | SCL  |
| PB7           | I2C1_SDA | pin5        | SDA  |

## led
| STM32F103C8T6 | FUNC        | LED   | DESC   |
| ------------- | ----------- | ----- | ------ |
| PB0           | GPIO_Outout |       | RED    |
| PB1           | GPIO_Outout |       | GREEN  |
| PB2           | GPIO_Outout |       | BLUE   |

## button
| STM32F103C8T6 | FUNC       | BTN   | DESC   |
| ------------- | ---------- | ----- | ------ |
| PB10          | GPIO_Input |       | Left   |
| PB11          | GPIO_Input |       | Right  |
| PB8           | GPIO_Input |       | Up     |
| PB9           | GPIO_Input |       | Down   |
| PC13          | GPIO_Input |       | A      |
| PC14          | GPIO_Input |       | B      |

## speaker
| STM32F103C8T6 | FUNC        |           | DESC      |
| ------------- | ----------- | --------- | --------- |
| PB4           | GPIO_Outout |           | SPEAKER_1 |
| PB3           | GPIO_Outout |           | SPEAKER_2 |

## adc (for generateRandomSeed)
| STM32F103C8T6 | FUNC        |           | DESC      |
| ------------- | ----------- | --------- | --------- |
| PA2           | ADC1_EXTI15 |           |           |
