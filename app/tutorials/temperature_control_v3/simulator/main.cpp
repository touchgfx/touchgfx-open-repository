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
#include <platform/hal/simulator/sdl/HALSDL.hpp>
#include <touchgfx/hal/NoDMA.hpp>
#include <touchgfx/Application.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TypedTextDatabase.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <platform/driver/touch/SDLTouchController.hpp>
#include <platform/driver/lcd/LCD16bpp.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <stdlib.h>

using namespace touchgfx;

int main(int argc, char** argv)
{
    NoDMA dma; //For windows/linux, DMA transfers are simulated
    LCD16bpp lcd;
    SDLTouchController tc;

    // Create hardware layer. Use a display size of 480x272.
    HALSDL hal(dma, lcd, tc, 480, 272); 

    if (!hal.sdl_init(argc, argv))
    {
        return EXIT_FAILURE;
    }
    hal.initialize();

    Bitmap::registerBitmapDatabase(BitmapDatabase::getInstance(),
                                   BitmapDatabase::getInstanceSize(),
                                   0,
                                   0);

    Texts texts;
    TypedText::registerTexts(&texts);
    Texts::setLanguage(0); // Change '0' to the initial language, e.g. 'GB'

    //The Keyboard uses the FontManager to get at FontProvider.
    ApplicationFontProvider fontProvider;
    FontManager::setFontProvider(&fontProvider);

    FrontendHeap& heap = FrontendHeap::getInstance();
    (void)heap; // we need to obtain the reference above to initialize the frontend heap.

    hal.registerEventListener(*(Application::getInstance()));

    touchgfx::HAL::getInstance()->taskEntry(); //Never returns

    return EXIT_SUCCESS;
}
