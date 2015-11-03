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
#include "isr.h"

extern int main(void);
extern int SystemInit(void);

extern unsigned long _etext;
extern unsigned long __data_start;
extern unsigned long _edata;
extern unsigned long __bss_start__;
extern unsigned long __bss_end__;
extern unsigned long __stack_end__;
extern unsigned long __valid_user_code_checksum;
/*
int _sbrk_r (struct _reent *r, int incr)
{
    return 0;
}
*/

__attribute__ ((section(".isr_vectors"), used))
void (* const g_pfnVectors[])(void) = {
    (void (*)(void))((unsigned long)&__stack_end__),
    ResetISR,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    (void (*)(void))((unsigned long)&__valid_user_code_checksum),
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
    WWDG_IRQHandler,  // Window WatchDog                                        
    PVD_IRQHandler,  // PVD through EXTI Line detection                        
    TAMP_STAMP_IRQHandler,  // Tamper and TimeStamps through the EXTI line            
    RTC_WKUP_IRQHandler,  // RTC Wakeup through the EXTI line                       
    FLASH_IRQHandler,  // FLASH                                           
    RCC_IRQHandler,  // RCC                                             
    EXTI0_IRQHandler,  // EXTI Line0                                             
    EXTI1_IRQHandler,  // EXTI Line1                                             
    EXTI2_IRQHandler,  // EXTI Line2                                             
    EXTI3_IRQHandler,  // EXTI Line3                                             
    EXTI4_IRQHandler,  // EXTI Line4                                             
    DMA1_Stream0_IRQHandler,  // DMA1 Stream 0                                   
    DMA1_Stream1_IRQHandler,  // DMA1 Stream 1                                   
    DMA1_Stream2_IRQHandler,  // DMA1 Stream 2                                   
    DMA1_Stream3_IRQHandler,  // DMA1 Stream 3                                   
    DMA1_Stream4_IRQHandler,  // DMA1 Stream 4                                   
    DMA1_Stream5_IRQHandler,  // DMA1 Stream 5                                   
    DMA1_Stream6_IRQHandler,  // DMA1 Stream 6                                   
    ADC_IRQHandler,  // ADC1, ADC2 and ADC3s                            
    CAN1_TX_IRQHandler,  // CAN1 TX                                                
    CAN1_RX0_IRQHandler,  // CAN1 RX0                                               
    CAN1_RX1_IRQHandler,  // CAN1 RX1                                               
    CAN1_SCE_IRQHandler,  // CAN1 SCE                                               
    EXTI9_5_IRQHandler,  // External Line[9:5]s                                    
    TIM1_BRK_TIM9_IRQHandler,  // TIM1 Break and TIM9                   
    TIM1_UP_TIM10_IRQHandler,  // TIM1 Update and TIM10                 
    TIM1_TRG_COM_TIM11_IRQHandler,  // TIM1 Trigger and Commutation and TIM11
    TIM1_CC_IRQHandler,  // TIM1 Capture Compare                                   
    TIM2_IRQHandler,  // TIM2                                            
    TIM3_IRQHandler,  // TIM3                                            
    TIM4_IRQHandler,  // TIM4                                            
    I2C1_EV_IRQHandler,  // I2C1 Event                                             
    I2C1_ER_IRQHandler,  // I2C1 Error                                             
    I2C2_EV_IRQHandler,  // I2C2 Event                                             
    I2C2_ER_IRQHandler,  // I2C2 Error                                               
    SPI1_IRQHandler,  // SPI1                                            
    SPI2_IRQHandler,  // SPI2                                            
    USART1_IRQHandler,  // USART1                                          
    USART2_IRQHandler,  // USART2                                          
    USART3_IRQHandler,  // USART3                                          
    EXTI15_10_IRQHandler,  // External Line[15:10]s                                  
    RTC_Alarm_IRQHandler,  // RTC Alarm (A and B) through EXTI Line                  
    OTG_FS_WKUP_IRQHandler,  // USB OTG FS Wakeup through EXTI line                        
    TIM8_BRK_TIM12_IRQHandler,  // TIM8 Break and TIM12                  
    TIM8_UP_TIM13_IRQHandler,  // TIM8 Update and TIM13                 
    TIM8_TRG_COM_TIM14_IRQHandler,  // TIM8 Trigger and Commutation and TIM14
    TIM8_CC_IRQHandler,  // TIM8 Capture Compare                                   
    DMA1_Stream7_IRQHandler,  // DMA1 Stream7                                           
    FMC_IRQHandler,  // FMC                                            
    SDIO_IRQHandler,  // SDIO                                            
    TIM5_IRQHandler,  // TIM5                                            
    SPI3_IRQHandler,  // SPI3                                            
    UART4_IRQHandler,  // UART4                                           
    UART5_IRQHandler,  // UART5                                           
    TIM6_DAC_IRQHandler,  // TIM6 and DAC1&2 underrun errors                   
    TIM7_IRQHandler,  // TIM7                   
    DMA2_Stream0_IRQHandler,  // DMA2 Stream 0                                   
    DMA2_Stream1_IRQHandler,  // DMA2 Stream 1                                   
    DMA2_Stream2_IRQHandler,  // DMA2 Stream 2                                   
    DMA2_Stream3_IRQHandler,  // DMA2 Stream 3                                   
    DMA2_Stream4_IRQHandler,  // DMA2 Stream 4                                   
    ETH_IRQHandler,  // Ethernet                                        
    ETH_WKUP_IRQHandler,  // Ethernet Wakeup through EXTI line                      
    CAN2_TX_IRQHandler,  // CAN2 TX                                                
    CAN2_RX0_IRQHandler,  // CAN2 RX0                                               
    CAN2_RX1_IRQHandler,  // CAN2 RX1                                               
    CAN2_SCE_IRQHandler,  // CAN2 SCE                                               
    OTG_FS_IRQHandler,  // USB OTG FS                                      
    DMA2_Stream5_IRQHandler,  // DMA2 Stream 5                                   
    DMA2_Stream6_IRQHandler,  // DMA2 Stream 6                                   
    DMA2_Stream7_IRQHandler,  // DMA2 Stream 7                                   
    USART6_IRQHandler,  // USART6                                           
    I2C3_EV_IRQHandler,  // I2C3 event                                             
    I2C3_ER_IRQHandler,  // I2C3 error                                             
    OTG_HS_EP1_OUT_IRQHandler,  // USB OTG HS End Point 1 Out                      
    OTG_HS_EP1_IN_IRQHandler,  // USB OTG HS End Point 1 In                       
    OTG_HS_WKUP_IRQHandler,  // USB OTG HS Wakeup through EXTI                         
    OTG_HS_IRQHandler,  // USB OTG HS                                      
    DCMI_IRQHandler,  // DCMI                                            
    CRYP_IRQHandler,  // CRYP crypto                                     
    HASH_RNG_IRQHandler,  // Hash and Rng
    FPU_IRQHandler,  // FPU
    UART7_IRQHandler,  // UART7
    UART8_IRQHandler,  // UART8
    SPI4_IRQHandler,  // SPI4
    SPI5_IRQHandler,  // SPI5
    SPI6_IRQHandler,  // SPI6
    SAI1_IRQHandler,  // SAI1
    LTDC_IRQHandler,  // LTDC
    LTDC_ER_IRQHandler,  // LTDC error
    DMA2D_IRQHandler,  // DMA2D
};

extern void (*__init_array_start []) (void) __attribute__((weak));
extern void (*__init_array_end []) (void) __attribute__((weak));

void ResetISR(void)
{
    unsigned long *src, *dst;
    
    int count;
    int i;

    
    src = &_etext;
    for(dst = &__data_start; dst < &_edata; ) {
        *dst++ = *src++;
    }

    for(dst = &__bss_start__; dst < &__bss_end__; ) {
        *dst++ = 0;
    }
    
    count = __init_array_end - __init_array_start;
    for (i = 0; i < count; i++)
        __init_array_start[i] ();
    
    SystemInit();
    main();
}

void NMI_Handler(void) 
{
  while(1);
}

void HardFault_Handler(void) 
{
  while(1);
}

void MemManage_Handler(void) 
{
  while(1);
}

void BusFault_Handler(void) 
{
  while(1);
}

void UsageFault_Handler(void) 
{
  while(1);
}

void DebugMon_Handler(void) 
{
  while(1);
}

void WWDG_IRQHandler()
{

}

void PVD_IRQHandler()
{

}

void TAMP_STAMP_IRQHandler()
{

}

void RTC_WKUP_IRQHandler()
{

}

void FLASH_IRQHandler()
{

}

void RCC_IRQHandler()
{

}

void EXTI0_IRQHandler()
{

}

void EXTI1_IRQHandler()
{

}

void EXTI2_IRQHandler()
{

}

void EXTI3_IRQHandler()
{

}

void EXTI4_IRQHandler()
{

}

void DMA1_Stream0_IRQHandler()
{

}

void DMA1_Stream1_IRQHandler()
{

}

void DMA1_Stream2_IRQHandler()
{

}

void DMA1_Stream3_IRQHandler()
{

}

void DMA1_Stream4_IRQHandler()
{

}

void DMA1_Stream5_IRQHandler()
{

}

void DMA1_Stream6_IRQHandler()
{

}

void ADC_IRQHandler()
{

}
 
void CAN1_TX_IRQHandler()
{

}

void CAN1_RX0_IRQHandler()
{

}

void CAN1_RX1_IRQHandler()
{

}

void CAN1_SCE_IRQHandler()
{

}

void EXTI9_5_IRQHandler()
{

}

void TIM1_BRK_TIM9_IRQHandler()
{

}

void TIM1_UP_TIM10_IRQHandler()
{

}

void TIM1_TRG_COM_TIM11_IRQHandler()
{

}

void TIM1_CC_IRQHandler()
{

}

void TIM2_IRQHandler()
{

}

void TIM3_IRQHandler()
{

}

void TIM4_IRQHandler()
{

}

void I2C1_EV_IRQHandler()
{

}

void I2C1_ER_IRQHandler()
{

}

void I2C2_EV_IRQHandler()
{

}

void I2C2_ER_IRQHandler()
{

}

void SPI1_IRQHandler()
{

}

void SPI2_IRQHandler()
{

}

void USART1_IRQHandler()
{

}
 
void USART2_IRQHandler()
{

}

void USART3_IRQHandler()
{

}

void EXTI15_10_IRQHandler() 
{

}

void RTC_Alarm_IRQHandler()
{

}

void OTG_FS_WKUP_IRQHandler()
{

}
 
void TIM8_BRK_TIM12_IRQHandler()
{

}

void TIM8_UP_TIM13_IRQHandler()
{

}

void TIM8_TRG_COM_TIM14_IRQHandler()
{

}
 
void TIM8_CC_IRQHandler()
{

}
 
void DMA1_Stream7_IRQHandler()
{

}

void FMC_IRQHandler()
{

}
 
void SDIO_IRQHandler()
{

}

void TIM5_IRQHandler()
{

}
 
void SPI3_IRQHandler()
{

}
 
void UART4_IRQHandler()
{

}

void UART5_IRQHandler()
{

}
 
void TIM6_DAC_IRQHandler()
{

}
 
void TIM7_IRQHandler()
{

}
 
void DMA2_Stream0_IRQHandler()
{

}

void DMA2_Stream1_IRQHandler()
{

}

void DMA2_Stream2_IRQHandler()
{

}

void DMA2_Stream3_IRQHandler()
{

}
 
void DMA2_Stream4_IRQHandler()
{

}
 
void ETH_IRQHandler()
{

}
 
void ETH_WKUP_IRQHandler()
{

}
 
void CAN2_TX_IRQHandler()
{

}
 
void CAN2_RX0_IRQHandler()
{

}
 
void CAN2_RX1_IRQHandler()
{

}
 
void CAN2_SCE_IRQHandler()
{

}

void OTG_FS_IRQHandler()
{

}
 
void DMA2_Stream5_IRQHandler()
{

}
 
void DMA2_Stream6_IRQHandler()
{

}
 
void DMA2_Stream7_IRQHandler()
{

}
 
void USART6_IRQHandler()
{

}
  
void I2C3_EV_IRQHandler()
{

}
  
void I2C3_ER_IRQHandler()
{

}
  
void OTG_HS_EP1_OUT_IRQHandler()
{

}

void OTG_HS_EP1_IN_IRQHandler()
{

}
 
void OTG_HS_WKUP_IRQHandler()
{

}
 
void OTG_HS_IRQHandler()
{

}
 
void DCMI_IRQHandler()
{

}
  
void CRYP_IRQHandler()
{

}
  
void HASH_RNG_IRQHandler()
{

}
  
void FPU_IRQHandler()
{

}
  
void UART7_IRQHandler()
{

}
 
void UART8_IRQHandler()
{

}
 
void SPI4_IRQHandler()
{

}
 
void SPI5_IRQHandler()
{

}
 
void SPI6_IRQHandler()
{

}
 
void SAI1_IRQHandler()
{

}
  
void LTDC_ER_IRQHandler()
{

}

