/******************************************************************************
 *
 * @brief     This file is part of the TouchGFX 4.4.1 evaluation distribution.
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
void DAC_IRQHandler(void) __attribute__((__interrupt__));
void DMA_IRQHandler(void) __attribute__((__interrupt__));
void ETH_IRQHandler(void) __attribute__((__interrupt__));
void SDIO_IRQHandler(void) __attribute__((__interrupt__));
void LCD_IRQHandler(void) __attribute__((__interrupt__));
void USB0_IRQHandler(void) __attribute__((__interrupt__));
void USB1_IRQHandler(void) __attribute__((__interrupt__));
void SCT_IRQHandler(void) __attribute__((__interrupt__));
void RIT_IRQHandler(void) __attribute__((__interrupt__));
void TIMER0_IRQHandler(void) __attribute__((__interrupt__));
void TIMER1_IRQHandler(void) __attribute__((__interrupt__));
void TIMER2_IRQHandler(void) __attribute__((__interrupt__));
void TIMER3_IRQHandler(void) __attribute__((__interrupt__));
void MCPWM_IRQHandler(void) __attribute__((__interrupt__));
void ADC0_IRQHandler(void) __attribute__((__interrupt__));
void I2C0_IRQHandler(void) __attribute__((__interrupt__));
void I2C1_IRQHandler(void) __attribute__((__interrupt__));
void ADC1_IRQHandler(void) __attribute__((__interrupt__));
void SSP0_IRQHandler(void) __attribute__((__interrupt__));
void SSP1_IRQHandler(void) __attribute__((__interrupt__));
void UART0_IRQHandler(void) __attribute__((__interrupt__));
void UART1_IRQHandler(void) __attribute__((__interrupt__));
void UART2_IRQHandler(void) __attribute__((__interrupt__));
void UART3_IRQHandler(void) __attribute__((__interrupt__));
void I2S0_IRQHandler(void) __attribute__((__interrupt__));
void I2S1_IRQHandler(void) __attribute__((__interrupt__));
void SPIFI_IRQHandler(void) __attribute__((__interrupt__));
void SGPIO_IRQHandler(void) __attribute__((__interrupt__));
void GPIO0_IRQHandler(void) __attribute__((__interrupt__));
void GPIO1_IRQHandler(void) __attribute__((__interrupt__));
void GPIO2_IRQHandler(void) __attribute__((__interrupt__));
void GPIO3_IRQHandler(void) __attribute__((__interrupt__));
void GPIO4_IRQHandler(void) __attribute__((__interrupt__));
void GPIO5_IRQHandler(void) __attribute__((__interrupt__));
void GPIO6_IRQHandler(void) __attribute__((__interrupt__));
void GPIO7_IRQHandler(void) __attribute__((__interrupt__));
void GINT0_IRQHandler(void) __attribute__((__interrupt__));
void GINT1_IRQHandler(void) __attribute__((__interrupt__));
void EVRT_IRQHandler(void) __attribute__((__interrupt__));
void CAN1_IRQHandler(void) __attribute__((__interrupt__));
void ATIMER_IRQHandler(void) __attribute__((__interrupt__));
void RTC_IRQHandler(void) __attribute__((__interrupt__));
void WDT_IRQHandler(void) __attribute__((__interrupt__));
void CAN0_IRQHandler(void) __attribute__((__interrupt__));
void QEI_IRQHandler(void) __attribute__((__interrupt__));

#ifdef __cplusplus
}
#endif

#endif /* ISR_H */
