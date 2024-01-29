#include "Arduino_bsp_stm32f104c8t6.h"
#include <stdio.h>

extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

// return applox number of ms since boot
unsigned long millis()
{
	return HAL_GetTick();
}

void delay(unsigned long ms)
{
	HAL_Delay(ms);
	return;
}

void lcd_set_cs(int val)
{
	if (val == 0) {
		HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);
	}
}

void lcd_set_dc(int val)
{
	if (val == 0) {
		HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_SET);
	}
}

void lcd_set_rst(int val)
{
	if (val == 0) {
		HAL_GPIO_WritePin(RST_PORT, RST_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(RST_PORT, RST_PIN, GPIO_PIN_SET);
	}
}

void lcd_set_bl(int val)
{
	if (val == 0) {
		HAL_GPIO_WritePin(BL_PORT, BL_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(BL_PORT, BL_PIN, GPIO_PIN_SET);
	}
}

void led_set_red(int val)
{
	if (val == 0) {
		HAL_GPIO_WritePin(RED_LED_PORT, RED_LED_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(RED_LED_PORT, RED_LED_PIN, GPIO_PIN_SET);
	}
}

void led_set_green(int val)
{
	if (val == 0) {
		HAL_GPIO_WritePin(GREEN_LED_PORT, GREEN_LED_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(GREEN_LED_PORT, GREEN_LED_PIN, GPIO_PIN_SET);
	}
}

void led_set_blue(int val)
{
	if (val == 0) {
		HAL_GPIO_WritePin(BLUE_LED_PORT, BLUE_LED_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(BLUE_LED_PORT, BLUE_LED_PIN, GPIO_PIN_SET);
	}
}

void speaker_set_1(int val)
{
	if (val == 0) {
		HAL_GPIO_WritePin(SPEAKER_1_PORT, SPEAKER_1_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(SPEAKER_1_PORT, SPEAKER_1_PIN, GPIO_PIN_SET);
	}
}

void speaker_set_2(int val)
{
	if (val == 0) {
		HAL_GPIO_WritePin(SPEAKER_2_PORT, SPEAKER_2_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(SPEAKER_2_PORT, SPEAKER_2_PIN, GPIO_PIN_SET);
	}
}

/**
  * @brief  set pwm freq and duty.
  *
  * @note   Fpwm = TCLK / ( (ARR + 1) * (PSC + 1) )
  *         duty = CCRX /（ARR + 1)
  *
  * @param  freq: 100=100HZ
  * @param  duty: 50=50%
  * @retval None
  */
void speaker1_set(uint16_t freq, uint16_t duty)
{
	uint32_t cru_pclk2 = HAL_RCC_GetPCLK2Freq(); // APB2的总线时钟
	uint32_t cru_tim3_freq = cru_pclk2 / (htim3.Instance->PSC + 1); // 输入timer分频之后的时钟
	// uint32_t cru_out_freq = cru_tim3_freq / (htim3.Instance->ARR + 1);
	uint32_t _ARR = (cru_tim3_freq / freq) - 1;
	uint32_t _duty = duty * (_ARR + 1) / 100;

	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);

	if (freq < 1) {
		return;
	}

	if (_duty > 65535 || _ARR > 65535) {
		printf("bad freq or bad duty !!\r\n");
	}

	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, _duty);
	__HAL_TIM_SET_AUTORELOAD(&htim3, _ARR);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

/**
  * @brief  set pwm freq and duty.
  *
  * @note   Fpwm = TCLK / ( (ARR + 1) * (PSC + 1) )
  *         duty = CCRX /（ARR + 1)
  *
  * @param  freq: 100=100HZ
  * @param  duty: 50=50%
  * @retval None
  */
void speaker2_set(uint16_t freq, uint16_t duty)
{
	uint32_t cru_pclk2 = HAL_RCC_GetPCLK2Freq(); // APB2的总线时钟
	uint32_t cru_tim2_freq = cru_pclk2 / (htim2.Instance->PSC + 1); // 输入timer分频之后的时钟
	// uint32_t cru_out_freq = cru_tim2_freq / (htim2.Instance->ARR + 1);
	uint32_t _ARR = (cru_tim2_freq / freq) - 1;
	uint32_t _duty = duty * (_ARR + 1) / 100;

	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);

	if (freq < 1) {
		return;
	}

	if (_duty > 65535 || _ARR > 65535) {
		printf("bad freq or bad duty !!\r\n");
	}

	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, _duty);
	__HAL_TIM_SET_AUTORELOAD(&htim2, _ARR);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}

extern ADC_HandleTypeDef hadc1;

uint32_t get_adc_val(void)
{
	HAL_StatusTypeDef ret = HAL_OK;
	uint32_t val = 0;
	ret = HAL_ADC_Start(&hadc1); /* 开启ADC */
	if (ret != HAL_OK) {
		printf("HAL_ADC_Start failed!\r\n");
	}
	ret = HAL_ADC_PollForConversion(&hadc1, 100); /* 等待转换结束 */
	if (ret != HAL_OK) {
		printf("HAL_ADC_PollForConversion failed!\r\n");
	}
	val = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	return val;
}

int btn_get_a(void)
{
	if (HAL_GPIO_ReadPin(A_BUTTON_PORT, A_BUTTON_PIN) == GPIO_PIN_RESET) {
		return 0;
	}
	return 1;
}

int btn_get_b(void)
{
	if (HAL_GPIO_ReadPin(B_BUTTON_PORT, B_BUTTON_PIN) == GPIO_PIN_RESET) {
		return 0;
	}
	return 1;
}

int btn_get_up(void)
{
	if (HAL_GPIO_ReadPin(UP_BUTTON_PORT, UP_BUTTON_PIN) == GPIO_PIN_RESET) {
		return 0;
	}
	return 1;
}

int btn_get_down(void)
{
	if (HAL_GPIO_ReadPin(DOWN_BUTTON_PORT, DOWN_BUTTON_PIN) == GPIO_PIN_RESET) {
		return 0;
	}
	return 1;
}

int btn_get_left(void)
{
	if (HAL_GPIO_ReadPin(LEFT_BUTTON_PORT, LEFT_BUTTON_PIN) == GPIO_PIN_RESET) {
		return 0;
	}
	return 1;
}

int btn_get_right(void)
{
	if (HAL_GPIO_ReadPin(RIGHT_BUTTON_PORT, RIGHT_BUTTON_PIN) == GPIO_PIN_RESET) {
		return 0;
	}
	return 1;
}

int lcd_spi_init(void)
{
	return 0;
}

int lcd_spi_transfer(uint8_t data)
{
	if (HAL_SPI_Transmit(&hspi2, &data, 1, 3000) != HAL_OK) {
		printf("HAL_SPI_Transmit failed\r\n");
		return -1;
	}
	return 0;
}

uint8_t lcd_spi_transferAndRead(uint8_t data)
{
	if (HAL_SPI_Transmit(&hspi2, &data, 1, 3000) != HAL_OK) {
		printf("HAL_SPI_Transmit failed\r\n");
		return -1;
	}
	return 0;
}
