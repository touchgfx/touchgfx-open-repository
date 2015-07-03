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


#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>

#define CANVAS_BUFFER_SIZE (5600)

using namespace touchgfx;


int main(int argc, char** argv)
{
    NoDMA dma; //For windows/linux, DMA transfers are simulated
    LCD16bpp lcd;
    SDLTouchController tc;

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

    // Setup the CanvasWidgetRenderer. ONLY needed if you use CanvasWidgets
    // in your application. The CANVAS_BUFFER_SIZE can be adjusted to match
    // your needs in performance vs. RAM usage. Read more on this in the 
    // TouchGFX Manual.  
    static uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
    CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

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
