#pragma once

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_i2c.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_usart.h"

extern "C" TIM_HandleTypeDef  htim1;
extern "C" TIM_HandleTypeDef  htim2;
extern "C" TIM_HandleTypeDef  htim3;
extern "C" UART_HandleTypeDef huart1;
extern "C" UART_HandleTypeDef huart2;
extern "C" UART_HandleTypeDef huart3;
extern "C" UART_HandleTypeDef huart4;
extern "C" UART_HandleTypeDef huart5;
extern "C" UART_HandleTypeDef huart6;
extern "C" DMA_HandleTypeDef  hdma_usart1_rx;
extern "C" DMA_HandleTypeDef  hdma_usart1_tx;
extern "C" DMA_HandleTypeDef  hdma_usart2_rx;
extern "C" DMA_HandleTypeDef  hdma_usart2_tx;
extern "C" DMA_HandleTypeDef  hdma_usart3_rx;
extern "C" DMA_HandleTypeDef  hdma_usart3_tx;
extern "C" DMA_HandleTypeDef  hdma_uart4_rx;
extern "C" DMA_HandleTypeDef  hdma_uart4_tx;
extern "C" DMA_HandleTypeDef  hdma_uart5_rx;
extern "C" DMA_HandleTypeDef  hdma_uart5_tx;
extern "C" DMA_HandleTypeDef  hdma_usart6_rx;
extern "C" DMA_HandleTypeDef  hdma_usart6_tx;
extern "C" I2C_HandleTypeDef  hi2c1;

#define tim_System (&htim2)

#define tim_SteeringServo            (&htim1)
#define tim_chnl_FrontServo          TIM_CHANNEL_1
#define tim_chnl_RearServo           TIM_CHANNEL_2

#define tim_ServoX                   (&htim3)
#define tim_chnl_ServoX1             TIM_CHANNEL_3
#define tim_chnl_ServoX2             TIM_CHANNEL_4

#define uart_MotorPanel              (&huart1)
#define uart_Command                 (&huart2)
#define uart_RadioModule             (&huart3)
#define uart_X1                      (&huart4)
#define uart_RearLineDetectPanel     (&huart5)
#define uart_FrontLineDetectPanel    (&huart6)

#define dmaBase_Command              DMA2
#define dmaBase_MotorPanel           DMA1
#define dmaBase_RadioModule          DMA1
#define dmaBase_UartX1               DMA1
#define dmaBase_RearLineDetectPanel  DMA1
#define dmaBase_FrontLineDetectPanel DMA1

#define dma_Command                  (&hdma_usart1_rx)
#define dma_MotorPanel               (&hdma_usart2_rx)
#define dma_RadioModule              (&hdma_usart3_rx)
#define dma_UartX1                   (&hdma_uart4_rx)
#define dma_RearLineDetectPanel      (&hdma_uart5_rx)
#define dma_FrontLineDetectPanel     (&hdma_usart6_rx)

#define i2c_Gyro                     (&hi2c1)

#define gpio_Led                     GPIOA
#define gpioPin_Led                  GPIO_PIN_5
