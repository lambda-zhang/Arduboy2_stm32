#ifndef __ARDUINO_BSP_STM32F104C8T6_H__
#define __ARDUINO_BSP_STM32F104C8T6_H__

#include "stm32f1xx_hal.h"

unsigned long millis();
void delay(unsigned long ms);
uint32_t get_adc_val(void);

#define LCDBOOTPROGRAMARR \
	0xAE, /* set display display ON/OFF,AFH/AEH */ \
	0x02, \
	0x10, \
	0x40, /* set display start line:COM0 */ \
	0xB0, \
	0x81, /* set contrast control */ \
	0xCF, \
	0xA1, /* entire display on: A4H:OFF/A5H:ON */ \
	0xC8, /* 该指令控制显示方向显示方向0xc8或者0xc0 */ \
	0xAF, \
	0xA7, /* set normal/inverse display: A6H:normal/A7H:inverse */ \
	0xA8, /* set multiplex ratio */ \
	0x3F, /* 1/64duty */ \
	0xD3, /* set display offset */ \
	0x00, \
	0xD5, /* set display clock divide ratio/oscillator frequency */ \
	0x80, /* 105Hz */ \
	0xD9, /* Dis-charge /Pre-charge Period Mode Set */ \
	0xF1, \
	0xDA, /* Common Pads Hardware Configuration Mode Set */ \
	0x12, \
	0xDB, /* set vcomh deselect level */ \
	0x40, /* VCOM = β X VREF = (0.430 + A[7:0] X 0.006415) X VREF */ \
	0xA4, \
	0xA6, \
	0xAF /* set display display ON/OFF,AEH/AFH */

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
