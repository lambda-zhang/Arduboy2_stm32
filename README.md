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
| 应用/游戏名称         | 分类  | 来源 | 编译方法  | 备注 |
| ------------------- | ---- | ----- | ----- | ----- |
| ArduBreakout    | 游戏  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/ArduBreakout),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_ARDUBREAKOUT=1    | 可正常运行 |
| BeepDemo        | 应用  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/BeepDemo),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_BEEPDEMO=1        | 可正常运行 |
| Buttons         | 应用  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/Buttons),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_BUTTONS=1         | 可正常运行 |
| FontDemo        | 应用  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/FontDemo),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_FONTDEMO=1        | 可正常运行 |
| HelloWorld      | 应用  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/HelloWorld),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_HELLOWORLD=1      | 可正常运行 |
| RGBled          | 应用  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/RGBled),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_RGBLED=1          | 可正常运行 |
| SetSystemEEPROM | 应用  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/SetSystemEEPROM),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_SETSYSTEMEEPROM=1 | 不正常 |
| PlayTune        | 应用  | [这个链接](https://github.com/MLXXXp/Arduboy2/tree/master/examples/PlayTune),[这次commit](https://github.com/MLXXXp/Arduboy2/commit/bc460a2cff1a3e116880991aa2f88bae4b2e3160) | make APP_PLAYTUNE=1        | 可正常运行 |
| arduboy-rund-ino | 游戏  | [这个链接](https://github.com/flaki/arduboy-rund-ino),[这次commit](https://github.com/flaki/arduboy-rund-ino/commit/ff8615fd457f08fd3a5ccc0434d67ee31ca87d8d) | make APP_RUND=1            | 可正常运行 |
| arduboy-rund-ino/halloweend | 游戏  | [这个链接](https://github.com/flaki/arduboy-rund-ino),[这次commit](https://github.com/flaki/arduboy-rund-ino/commit/ff8615fd457f08fd3a5ccc0434d67ee31ca87d8d) | make APP_HALLOWEEND=1      | 可正常运行 |
| Ardynia  | 游戏  | [这个链接](https://github.com/city41/ardynia),[这次commit](https://github.com/city41/ardynia/commit/23e1f2449c7f4919eb88f23faa40cbd141d05249) | make APP_ARDYNIA=1         | 可正常运行，走到图像边缘有bug已经尝试修改但不一定对 |
| CastleBoy | 游戏  | [这个链接](https://github.com/jlauener/CastleBoy),[这次commit](https://github.com/jlauener/CastleBoy/commit/1d758fdd862d6269dc459661779c52d75cc87f98) | make APP_CASTLEBOY=1       | 不正常 |
| Flappy Ball | 游戏  | [这个链接](https://github.com/MLXXXp/FlappyBall),[这次commit](https://github.com/MLXXXp/FlappyBall/commit/263e70f240a6811541c3794d2d27bf8323d347a6) | make APP_FLAPPYBALL=1      | 可正常运行 |
| Catacombs of the damned! | 游戏  | [这个链接](https://github.com/jhhoward/Arduboy3D),[这次commit](https://github.com/jhhoward/Arduboy3D/commit/929db9f3429cc20a318934099d992f1219a081bd) | make APP_ARDUBOY3D=1       | 可正常运行 |
| Shadow Runner | 游戏  | [这个链接](https://github.com/Team-ARG-Museum/ID-15-Shadow-Runner/tree/master/SHRUN_AB),[这个commit](https://github.com/Team-ARG-Museum/ID-15-Shadow-Runner/commit/25f277508f28bd379deadba48ff2871f82970344) | make APP_SHADOWRUNNER=1    | 可正常运行 |
| Mystic Balloon | 游戏  | [这个链接](https://github.com/Gaveno/ID-34-Mystic-Balloon),[这次commit](https://github.com/Gaveno/ID-34-Mystic-Balloon/commit/a2ca9eee92016cf75ec1d6ea9f1126b2403549f5) | make APP_MYSTICBALLOON=1   | 可正常运行 |
| ArduboyTetris | 游戏  | [这个链接](https://github.com/Nautili/ArduboyTetris),[这次commit](https://github.com/Nautili/ArduboyTetris/commit/3cc72e452c4a7dd3737f72e728e165f666ef9e80) | make APP_ARDUBOYTETRIS=1   | 可正常运行 |
| Dark-And-Under | 游戏 | [这个链接](https://hub.nuaa.cf/Garage-Collective/Dark-And-Under),[这次commit](https://hub.nuaa.cf/Garage-Collective/Dark-And-Under/commit/7dd8f6a03eb179cec12ebc9261ddcb7a88259ce5) | make APP_DARKANDUNDER=1 | 不正常 |
| Bubble PoP | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-14-Bubble-PoP),[这次commit](https://github.com/Team-ARG-Museum/ID-14-Bubble-PoP/commit/17bc3feb1240556dd3ca2b0a0ab0292b9c9eab71) | make APP_BUBBLEPOP=1 |  |
| ID-10-Dungeons | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-10-Dungeons),[这次commit](https://github.com/Team-ARG-Museum/ID-10-Dungeons/commit/ac8ff35bbd6bd74f2a54bfc2b853e581b8c35ecb) | make APP_DUNGEONS=1 |  |
| ID-20-Escaper-Droid | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-20-Escaper-Droid),[这次commit](https://github.com/Team-ARG-Museum/ID-20-Escaper-Droid/commit/d8a6bf7274ca917a46213c668164bd99f6f653f5) | make APP_ESCAPERDROID=1 |  |
| Blob Attack | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-28-Blob-Attack),[这个commit](https://github.com/Team-ARG-Museum/ID-28-Blob-Attack/commit/71d33c8a5df90a27500f27fbe899eacf8f5a0ecd) | make APP_BLOBATTACK=1 |  |
| BEGEMMED | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-30-BEGEMMED),[这次commit](https://github.com/Team-ARG-Museum/ID-30-BEGEMMED/commit/7dcb1be9e1dd3fb833f8b3933ad259d8c7f4cd03) | make APP_BEGEMMED=1 |  |
| Reverse Mermaid Hockey | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-31-RMH),[这个commit](https://github.com/Team-ARG-Museum/ID-31-RMH/commit/377a31443e4571873d6cdf25e685d2d1269083e1) | make APP_RMH=1 |  |
| Epic Crates Of Mass Destruction | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-33-ECOMD),[这个commit](https://github.com/Team-ARG-Museum/ID-33-ECOMD/commit/c2dac94a6af7cc56389447271935bc322e5aa19b) | make APP_ECOMD=1 |  |
| Trolly Fish | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-36-Trolly-Fish),[这个commit](https://github.com/Team-ARG-Museum/ID-36-Trolly-Fish/commit/ddaf606287aded96adf441521b6515b5f86d50f2) | make APP_TROLLYFISH=1 |  |
| DICE of FATE | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-37-DICE-of-FATE),[这个commit](https://github.com/Team-ARG-Museum/ID-37-DICE-of-FATE/commit/d2d7cf40f81e69a64dee461114f79ef8a8e7e714) | make APP_DICEOFFATE=1 |  |
| VIRUS LQP-79 | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-40-VIRUS-LQP-79),[这个commit](https://github.com/Team-ARG-Museum/ID-40-VIRUS-LQP-79/commit/9f664f0f7b87aca7654d8113b98e41e53c8f5ed0) | make APP_VIRUSLQP79=1 |  |
| Sirène | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-42-Sirene),[这次commit](https://github.com/Team-ARG-Museum/ID-42-Sirene/commit/2b96c1dc36fcb40697160bbec77668956d2a4089) | make APP_SIRENE=1 |  |
| PINBALL | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-44-Pinball),[这个commit](https://github.com/Team-ARG-Museum/ID-44-Pinball/commit/62ec62d27b2ece0e78a7f40f86bb8e41fd5ce2e7) | make APP_PINBALL=1 |  |
| ARDUVENTURE | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-46-Arduventure),[这个commit](https://github.com/Team-ARG-Museum/ID-46-Arduventure/commit/938fae770f04369ae4e4dd29c1039f7b43e7d96c) | make APP_ARDUVENTURE=1 |  |
| Helmets & Hordes | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-47-Helmets-Hordes),[这个commit](https://github.com/Team-ARG-Museum/ID-47-Helmets-Hordes/commit/87d1b7e1cc7419be84e078404cbceba58f76a64e) | make APP_HELMETSHORDES=1 |  |
| Fantasy Rampage | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-48-Fantasy-Rampage),[这个commit](https://github.com/Team-ARG-Museum/ID-48-Fantasy-Rampage/commit/29d30d3574e31074aa8bb5d070c073f652b85f1a) | make APP_FANTASYRAMPAGE=1 |  |
| Outpost Defense | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-49-Outpost-Defense),[这个commit](https://github.com/Team-ARG-Museum/ID-49-Outpost-Defense/commit/9297095e4b9e074ef28495185a4925d0ff0de0c2) | make APP_OUTPOSTDEFENSE=1 |  |
| Sunfire | 游戏 | [这个链接](https://github.com/Team-ARG-Museum/ID-50-Sunfire),[这个commit](https://github.com/Team-ARG-Museum/ID-50-Sunfire/commit/e99fff73e2d7ba974b8fbef90f7adf90c764397b) | make APP_SUNFIRE=1 |  |
| ID-51-EEPROM-TOOL | 应用 | [这个链接](https://github.com/Team-ARG-Museum/ID-51-EEPROM-TOOL),[这个commit](https://github.com/Team-ARG-Museum/ID-51-EEPROM-TOOL/commit/68f6802a5bc57fa95ad627c77eb6ec64362750d9) | make APP_EEPROMTOOL=1 | 不正常 |

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
| STM32F103C8T6 | FUNC        | speaker | DESC      |
| ------------- | ----------- | ------- | --------- |
| PB4           | GPIO_Outout |         | SPEAKER_1 |
| PB3           | GPIO_Outout |         | SPEAKER_2 |

## adc (for generateRandomSeed)
| STM32F103C8T6 | FUNC        |           | DESC      |
| ------------- | ----------- | --------- | --------- |
| PA2           | ADC1_EXTI15 |           |           |

# 问题
### 是否支持多个游戏打包到Flash？
不支持。现在使用的stm32f103c8t6的sram只有20KB，同时也不支持FSMC，无法搞一个loder的功能，所以当前版本不打算做多个游戏打包。

目前只能使用JLINK烧写单个游戏到单片机，要换另一个游戏就要重新烧录。

### 是否能通过USB下载？

不支持。还没有做开发。

### 后续计划？

- 使用RP2040再做另外一个版本，这样就可以支持多个游戏打包。具体计划未定。
- 在当前平台好几个游戏有bug，尝试看看能不能在当前平台解决
- EEPROM的支持
