#include "main.h"

void Drive_Encoder_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_GPIOA_CLK_ENABLE(); /* Enable GPIOA clock */

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Enable EXTI interrupt */
    HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

    /* Configure interrupt priority */
    HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
}

/**
 * @brief This function handles EXTI4_15 Interrupt .
 */
/* void EXTI4_15_IRQHandler(void)
{
    AllStatus_S.encoder_s.EncoderIsRun = 1;
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
        AllStatus_S.encoder_s.TurnleftOrRight = 1; // 顺时针旋转
    else
        AllStatus_S.encoder_s.TurnleftOrRight = 0; // 逆时针旋转

    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);
} */

#define ENCODER_DEBOUNCE_MS 100

void EXTI4_15_IRQHandler(void)
{
    static uint8_t last_direction = 0;
    static uint32_t last_tick = 0;
    uint8_t curr_direction;

    // 100ms内触发两次则清空中断并立即返回，每100ms只允许触发一次
    if ((uwTick - last_tick) < ENCODER_DEBOUNCE_MS)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);
        return;
    }

    AllStatus_S.encoder_s.EncoderIsRun = 1;

    // 判断当前方向
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
        curr_direction = 1; // 顺时针
    else
        curr_direction = 0; // 逆时针

    // 如果距离上次旋转超过ENCODER_DEBOUNCE_MS，重置方向
    if ((uwTick - last_tick) > ENCODER_DEBOUNCE_MS)
    {
        last_direction = curr_direction;
    }

    // 如果方向发生变化但在ENCODER_DEBOUNCE_MS内，保持原方向
    if (curr_direction != last_direction && (uwTick - last_tick) <= ENCODER_DEBOUNCE_MS)
    {
        AllStatus_S.encoder_s.TurnleftOrRight = last_direction;
    }
    else
    {
        AllStatus_S.encoder_s.TurnleftOrRight = curr_direction;
        last_direction = curr_direction;
    }

    last_tick = uwTick;

    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);
}

/* void Encoder_Scan_1ms(void)
{
    static uint8_t last_A = 0, last_B = 0;
    uint8_t curr_A, curr_B;
    static uint8_t filter_cnt = 0;

    curr_A = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6);
    curr_B = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7);

    // 检测A/B变化，进行滤波
    if ((curr_A != last_A) || (curr_B != last_B))
    {
        filter_cnt++;
        if (filter_cnt >= 2) // 过滤两次抖动
        {
            AllStatus_S.encoder_s.EncoderIsRun = 1;
            // 判断方向
            if ((last_A == 0 && curr_A == 1 && curr_B == 0) ||
                (last_A == 1 && curr_A == 0 && curr_B == 1))
            {
                AllStatus_S.encoder_s.TurnleftOrRight = 0; // 顺时针
            }
            else
            {
                AllStatus_S.encoder_s.TurnleftOrRight = 1; // 逆时针
            }
            filter_cnt = 0;
        }
    }
    else
    {
        filter_cnt = 0;
    }

    last_A = curr_A;
    last_B = curr_B;
} */
