/******************************************************************************
 *
 * @brief     This file is part of the TouchGFX 4.4.2 evaluation distribution.
 *
 * @author    Draupner Graphics A/S <http://www.touchgfx.com>
 *
 ******************************************************************************
 *
 * @section Copyright
 * 
 * This file is free software and is provided for example purposes. You may 
 * use, copy, and modify within the terms and conditions of the license
 * agreement. 
 *
 * This is licensed software for evaluation use, any use must strictly comply
 * with the evaluation license agreement provided with delivery of the
 * TouchGFX software.
 *
 * The evaluation license agreement can be seen on www.touchgfx.com
 *
 * @section Disclaimer
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Draupner Graphics A/S has
 * no obligation to support this software. Draupner Graphics A/S is providing
 * the software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Draupner Graphics A/S can not be held liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this software.
 *
 *****************************************************************************/
#ifndef __ISR_H
#define __ISR_H

#ifdef __cplusplus
extern "C" {
#endif

void ResetISR(void) __attribute__((__interrupt__));
void NMI_Handler(void) __attribute__((__interrupt__));
void HardFault_Handler(void) __attribute__((__interrupt__));
void MemManage_Handler(void) __attribute__((__interrupt__));
void BusFault_Handler(void) __attribute__((__interrupt__));
void UsageFault_Handler(void) __attribute__((__interrupt__));
void SVC_Handler(void) __attribute__((__interrupt__));
void DebugMon_Handler(void) __attribute__((__interrupt__));
void PendSV_Handler(void) __attribute__((__interrupt__));
void SysTick_Handler(void) __attribute__((__interrupt__));
void WWDG_IRQHandler(void) __attribute__((__interrupt__));
void PVD_IRQHandler(void) __attribute__((__interrupt__));
void TAMP_STAMP_IRQHandler(void) __attribute__((__interrupt__));
void RTC_WKUP_IRQHandler(void) __attribute__((__interrupt__));
void FLASH_IRQHandler(void) __attribute__((__interrupt__));
void RCC_IRQHandler(void) __attribute__((__interrupt__));
void EXTI0_IRQHandler(void) __attribute__((__interrupt__));
void EXTI1_IRQHandler(void) __attribute__((__interrupt__));
void EXTI2_IRQHandler(void) __attribute__((__interrupt__));
void EXTI3_IRQHandler(void) __attribute__((__interrupt__));
void EXTI4_IRQHandler(void) __attribute__((__interrupt__));
void DMA1_Stream0_IRQHandler(void) __attribute__((weak, __interrupt__));
void DMA1_Stream1_IRQHandler(void) __attribute__((weak, __interrupt__));
void DMA1_Stream2_IRQHandler(void) __attribute__((weak, __interrupt__));
void DMA1_Stream3_IRQHandler(void) __attribute__((weak, __interrupt__));
void DMA1_Stream4_IRQHandler(void) __attribute__((weak, __interrupt__));
void DMA1_Stream5_IRQHandler(void) __attribute__((weak, __interrupt__));
void DMA1_Stream6_IRQHandler(void) __attribute__((weak, __interrupt__));
void ADC_IRQHandler(void) __attribute__((__interrupt__));
void CAN1_TX_IRQHandler(void) __attribute__((__interrupt__));
void CAN1_RX0_IRQHandler(void) __attribute__((__interrupt__));
void CAN1_RX1_IRQHandler(void) __attribute__((__interrupt__));
void CAN1_SCE_IRQHandler(void) __attribute__((__interrupt__));
void EXTI9_5_IRQHandler(void) __attribute__((__interrupt__));
void TIM1_BRK_TIM9_IRQHandler(void) __attribute__((__interrupt__));
void TIM1_UP_TIM10_IRQHandler(void) __attribute__((__interrupt__));
void TIM1_TRG_COM_TIM11_IRQHandler(void) __attribute__((__interrupt__));
void TIM1_CC_IRQHandler(void) __attribute__((__interrupt__));
void TIM2_IRQHandler(void) __attribute__((__interrupt__));
void TIM3_IRQHandler(void) __attribute__((__interrupt__));
void TIM4_IRQHandler(void) __attribute__((__interrupt__));
void I2C1_EV_IRQHandler(void) __attribute__((__interrupt__));
void I2C1_ER_IRQHandler(void) __attribute__((__interrupt__));
void I2C2_EV_IRQHandler(void) __attribute__((__interrupt__));
void I2C2_ER_IRQHandler(void) __attribute__((__interrupt__));
void SPI1_IRQHandler(void) __attribute__((__interrupt__));
void SPI2_IRQHandler(void) __attribute__((__interrupt__));
void USART1_IRQHandler(void) __attribute__((__interrupt__));
void USART2_IRQHandler(void) __attribute__((__interrupt__));
void USART3_IRQHandler(void) __attribute__((__interrupt__));
void EXTI15_10_IRQHandler(void) __attribute__((__interrupt__));
void RTC_Alarm_IRQHandler(void) __attribute__((__interrupt__));
void OTG_FS_WKUP_IRQHandler(void) __attribute__((__interrupt__));
void TIM8_BRK_TIM12_IRQHandler(void) __attribute__((__interrupt__));
void TIM8_UP_TIM13_IRQHandler(void) __attribute__((__interrupt__));
void TIM8_TRG_COM_TIM14_IRQHandler(void) __attribute__((__interrupt__));
void TIM8_CC_IRQHandler(void) __attribute__((__interrupt__));
void DMA1_Stream7_IRQHandler(void) __attribute__((weak, __interrupt__));
void FMC_IRQHandler(void) __attribute__((__interrupt__));
void SDIO_IRQHandler(void) __attribute__((__interrupt__));
void TIM5_IRQHandler(void) __attribute__((__interrupt__));
void SPI3_IRQHandler(void) __attribute__((__interrupt__));
void UART4_IRQHandler(void) __attribute__((__interrupt__));
void UART5_IRQHandler(void) __attribute__((__interrupt__));
void TIM6_DAC_IRQHandler(void) __attribute__((__interrupt__));
void TIM7_IRQHandler(void) __attribute__((__interrupt__));
void DMA2_Stream0_IRQHandler(void) __attribute__((__interrupt__));
void DMA2_Stream1_IRQHandler(void) __attribute__((__interrupt__));
void DMA2_Stream2_IRQHandler(void) __attribute__((__interrupt__));
void DMA2_Stream3_IRQHandler(void) __attribute__((__interrupt__));
void DMA2_Stream4_IRQHandler(void) __attribute__((__interrupt__));
void ETH_IRQHandler(void) __attribute__((__interrupt__));
void ETH_WKUP_IRQHandler(void) __attribute__((__interrupt__));
void CAN2_TX_IRQHandler(void) __attribute__((__interrupt__));
void CAN2_RX0_IRQHandler(void) __attribute__((__interrupt__));
void CAN2_RX1_IRQHandler(void) __attribute__((__interrupt__));
void CAN2_SCE_IRQHandler(void) __attribute__((__interrupt__));
void OTG_FS_IRQHandler(void) __attribute__((__interrupt__));
void DMA2_Stream5_IRQHandler(void) __attribute__((__interrupt__));
void DMA2_Stream6_IRQHandler(void) __attribute__((__interrupt__));
void DMA2_Stream7_IRQHandler(void) __attribute__((__interrupt__));
void USART6_IRQHandler(void) __attribute__((__interrupt__));
void I2C3_EV_IRQHandler(void) __attribute__((__interrupt__));
void I2C3_ER_IRQHandler(void) __attribute__((__interrupt__));
void OTG_HS_EP1_OUT_IRQHandler(void) __attribute__((__interrupt__));
void OTG_HS_EP1_IN_IRQHandler(void) __attribute__((__interrupt__));
void OTG_HS_WKUP_IRQHandler(void) __attribute__((__interrupt__));
void OTG_HS_IRQHandler(void) __attribute__((__interrupt__));
void DCMI_IRQHandler(void) __attribute__((__interrupt__));
void CRYP_IRQHandler(void) __attribute__((__interrupt__));
void HASH_RNG_IRQHandler(void) __attribute__((__interrupt__));
void FPU_IRQHandler(void) __attribute__((__interrupt__));
void UART7_IRQHandler(void) __attribute__((__interrupt__));
void UART8_IRQHandler(void) __attribute__((__interrupt__));
void SPI4_IRQHandler(void) __attribute__((__interrupt__));
void SPI5_IRQHandler(void) __attribute__((__interrupt__));
void SPI6_IRQHandler(void) __attribute__((__interrupt__));
void SAI1_IRQHandler(void) __attribute__((__interrupt__));
void LTDC_ER_IRQHandler(void) __attribute__((__interrupt__));
void LTDC_IRQHandler(void) __attribute__((__interrupt__));
void DMA2D_IRQHandler(void) __attribute__((__interrupt__));


#ifdef __cplusplus
}
#endif

#endif /* ISR_H */
