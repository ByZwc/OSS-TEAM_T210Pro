#include "main.h"

void Drive_BUTTON_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;

  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

uint32_t Drive_BUTTON_GetState(void)
{
  return !(HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_2));
}

uint32_t Drive_Sleep_GetState(void)
{
  return !(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12));
}
