#ifndef __ARDUINO_BSP_STM32F104C8T6_H__
#define __ARDUINO_BSP_STM32F104C8T6_H__

#include "stm32f1xx_hal.h"

unsigned long millis();
void delay(unsigned long ms);
uint32_t get_adc_val(void);

#define LCDBOOTPROGRAMARR                                                                                              \
	0xAE, /* 关LCD */                                                                                             \
		0xE3, /* NOP */                                                                                        \
		0xA1, /* 设置液晶驱动电压偏置比，偏压1/9 */                                              \
		0xA0, /* 设置RAM地址 正常 */                                                                     \
		0xC8, /* 设置COM输出扫描方向,反向 */                                                         \
		0x25, /* 设置V0内部电阻比设置，可设置范围0x20～0x27 */                                                              \
		0x81, /* 设置V0输出电压电子量寄存器 */                                                     \
		0x15, /* 1A=9.0V,此参数根据屏幕不同设置不同 0x1a,微调对比度的值，可设置范围0x00～0x3f*/                                            \
		0xF8, /* 选择升压比 */                                                                            \
		0x00, /* 2x,3x,4x */                                                                                   \
		0x2C, /* 选择内部电源操作模式 */                                                             \
		0x2E, /* */                                                                                            \
		0x2F, /* */                                                                                            \
		0xA7, /* 0xa6为常规  0xa7为反显 */ \
		0xAF, /* 开LCD */                                                                                     \
		0x40, /* 设置显示起始行 */

#define CS_PIN GPIO_PIN_1 // Display CS pin number
#define CS_PORT GPIOA // Display CS port

#define DC_PIN GPIO_PIN_3 // Display D/C pin number
#define DC_PORT GPIOA // Display D/C port

#define RST_PIN GPIO_PIN_15 // Display reset pin number
#define RST_PORT GPIOA // Display reset port

#define BL_PIN GPIO_PIN_0 // Display bl pin number
#define BL_PORT GPIOA // Display bl port

void lcd_set_cs(int val);
void lcd_set_dc(int val);
void lcd_set_rst(int val);
void lcd_set_bl(int val);
int lcd_spi_init(void);
int lcd_spi_transfer(uint8_t data);
uint8_t lcd_spi_transferAndRead(uint8_t data);

#define RED_LED_PIN GPIO_PIN_0 /**< The pin number for the red color in the RGB LED. */
#define RED_LED_PORT GPIOB

#define GREEN_LED_PIN GPIO_PIN_1 /**< The pin number for the greem color in the RGB LED. */
#define GREEN_LED_PORT GPIOB

#define BLUE_LED_PIN GPIO_PIN_2 /**< The pin number for the blue color in the RGB LED. */
#define BLUE_LED_PORT GPIOB

#define RED_LED 10 /**< The pin number for the red color in the RGB LED. */
#define GREEN_LED 11 /**< The pin number for the greem color in the RGB LED. */
#define BLUE_LED 9 /**< The pin number for the blue color in the RGB LED. */

void led_set_red(int val);
void led_set_green(int val);
void led_set_blue(int val);

// bit values for button states
// these are determined by the buttonsState() function
#define LEFT_BUTTON _BV(5) /**< The Left button value for functions requiring a bitmask */
#define RIGHT_BUTTON _BV(6) /**< The Right button value for functions requiring a bitmask */
#define UP_BUTTON _BV(7) /**< The Up button value for functions requiring a bitmask */
#define DOWN_BUTTON _BV(4) /**< The Down button value for functions requiring a bitmask */
#define A_BUTTON _BV(3) /**< The A button value for functions requiring a bitmask */
#define B_BUTTON _BV(2) /**< The B button value for functions requiring a bitmask */

#define LEFT_BUTTON_PIN GPIO_PIN_10
#define LEFT_BUTTON_PORT GPIOB

#define RIGHT_BUTTON_PIN GPIO_PIN_11
#define RIGHT_BUTTON_PORT GPIOB

#define UP_BUTTON_PIN GPIO_PIN_8
#define UP_BUTTON_PORT GPIOB

#define DOWN_BUTTON_PIN GPIO_PIN_9
#define DOWN_BUTTON_PORT GPIOB

#define A_BUTTON_PIN GPIO_PIN_13
#define A_BUTTON_PORT GPIOC

#define B_BUTTON_PIN GPIO_PIN_14
#define B_BUTTON_PORT GPIOC

int btn_get_a(void);
int btn_get_b(void);
int btn_get_up(void);
int btn_get_down(void);
int btn_get_left(void);
int btn_get_right(void);

#define PIN_SPEAKER_1 5 /**< The pin number of the first lead of the speaker */
#define PIN_SPEAKER_2 13 /**< The pin number of the second lead of the speaker */

#define SPEAKER_1_PIN GPIO_PIN_4
#define SPEAKER_1_PORT GPIOB

#define SPEAKER_2_PIN GPIO_PIN_3
#define SPEAKER_2_PORT GPIOB

void speaker_set_1(int val);
void speaker_set_2(int val);
void speaker1_set(uint16_t freq, uint16_t duty);
void speaker2_set(uint16_t freq, uint16_t duty);
void audio_timer1_set(uint16_t freq);
void audio_timer4_set(uint16_t freq);

#endif /* __ARDUINO_BSP_STM32F104C8T6_H__ */
