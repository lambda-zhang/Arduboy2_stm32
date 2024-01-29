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

```
$ export PATH=$PATH:/your/path/gcc-arm-none-eabi-10.3-2021.10/bin
$ make
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

## 连接
### swd+uart
| STM32F103C8T6 | JLINK |       |
| ------------- | ----- | ----- |
| PA9           | pin17 | TX    |
| PA13          | pin7  | SWDIO |
| PA14          | pin9  | SWCLK |

### usb
| STM32F103C8T6 | USB         |       |
| ------------- | ----------- | ----- |
| PA11          | USB_DM      |       |
| PA12          | USB_DP      |       |
| PA8           | GPIO_Outout | EN    |

### flash
| STM32F103C8T6 | Nor Flash PIN | Nor Flash |
| ------------- | ------------- | --------- |
| PA4           | pin1          | CS        |
| PA5           | pin6          | CLK       |
| PA6           | pin2          | IO1/MISO  |
| PA7           | pin5          | IO0/MOSI  |

### lcd IRQT17
| STM32F103C8T6 | FUNC        | IRQT17 PIN    |           |
| ------------- | ----------- | ------------- | --------- |
| PA0           | TIM2_CH1    |               | BL        |
| PA1           | GPIO_Outout | pin4          | CS        |
| PA15          | GPIO_Outout | pin5          | RST       |
| PA3           | GPIO_Outout | pin6          | DC        |
| PB13          | SPI2_SCK    | pin7          | SCL       |
| PB15          | SPI2_MOSI   | pin8          | SDA       |

### e2prom
| STM32F103C8T6 | FUNC      | AT24C02 PIN   |           |
| ------------- | --------- | ------------- | --------- |
| PB6           | I2C1_SCL  | pin6          | SCL       |
| PB7           | I2C1_SDA  | pin5          | SDA       |

### led
| STM32F103C8T6 | FUNC        |       |        |
| ------------- | ----------- | ----- | ------ |
| PB0           | GPIO_Outout | RED   |        |
| PB1           | GPIO_Outout | GREEN |        |
| PB2           | GPIO_Outout | BLUE  |        |

### button
| STM32F103C8T6 | FUNC       |       |        |
| ------------- | ---------- | ----- | ------ |
| PB10          | GPIO_Input | Left  |        |
| PB11          | GPIO_Input | Right |        |
| PB8           | GPIO_Input | Up    |        |
| PB9           | GPIO_Input | Down  |        |
| PC13          | GPIO_Input | A     |        |
| PC14          | GPIO_Input | B     |        |

### speaker
| STM32F103C8T6 | FUNC        |           |           |
| ------------- | ----------- | --------- | --------- |
| PB4           | GPIO_Outout | SPEAKER_1 |           |
| PB3           | GPIO_Outout | SPEAKER_2 |           |

### adc (for generateRandomSeed)
| STM32F103C8T6 | FUNC        |           |           |
| ------------- | ----------- | --------- | --------- |
| PA2           | ADC1_EXTI15 |           |           |
