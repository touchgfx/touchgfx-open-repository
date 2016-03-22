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
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/BoardConfiguration.hpp>

using namespace touchgfx;

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/**
 * Define the FreeRTOS task priorities and stack sizes
 */
#define configGUI_TASK_PRIORITY                 ( tskIDLE_PRIORITY + 3 )

#define configGUI_TASK_STK_SIZE                 ( 950 )


static void GUITask(void* params)
{
  touchgfx::HAL::getInstance()->taskEntry();
}


int main (void)
{
  hw_init();
  touchgfx_init();


  /**
   * IMPORTANT NOTICE!
   *
   * The GUI task stack size might need to be increased if creating a new application.
   * The current value of 950 in this template is enough for the examples distributed with
   * TouchGFX, but is often insufficient for larger applications. 
   * For reference, the touchgfx_2014 demo uses a stacksize of 2000.
   * If you experience inexplicable hard faults with your custom application, try increasing the 
   * stack size.
   *
   * Also note that in FreeRTOS, stack size is in words. So a stack size of 950 actually consumes
   * 3800 bytes of memory. The configTOTAL_HEAP_SIZE define in platform/os/FreeRTOSConfig.h configures
   * the total amount of memory available for FreeRTOS, including task stacks. This value is expressed
   * in BYTES, not words. So, with a stack size of 950, your total heap should be at least 4K.
   */
  xTaskCreate( GUITask, (TASKCREATE_NAME_TYPE)"GUITask",
               configGUI_TASK_STK_SIZE,
               NULL,
               configGUI_TASK_PRIORITY,
               NULL);

  vTaskStartScheduler();

  for(;;);

}

