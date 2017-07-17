#include <platform/hal/simulator/sdl2/HALSDL2.hpp>
#include <touchgfx/hal/NoDMA.hpp>
#include <common/TouchGFXInit.hpp>
#include <platform/driver/touch/SDL2TouchController.hpp>
#if !defined(USE_BPP) || USE_BPP==16
#include <platform/driver/lcd/LCD16bpp.hpp>
#elif USE_BPP==24
#include <platform/driver/lcd/LCD24bpp.hpp>
#elif USE_BPP==1
#include <platform/driver/lcd/LCD1bpp.hpp>
#endif
#include <stdlib.h>

using namespace touchgfx;

//allocate memory for bitmap cache 200 Kb can hold an 320x240 image
uint8_t bmpCache[300*1024];

int main(int argc, char** argv)
{
    NoDMA dma; //For windows/linux, DMA transfers are simulated
#if !defined(USE_BPP) || USE_BPP==16
    LCD16bpp lcd;
#elif USE_BPP==24
    LCD24bpp lcd;
#elif USE_BPP==1
    LCD1bpp lcd;
#endif
    SDL2TouchController tc;

    // Create hardware layer. Use a display size of 480x272. BMP cache with a single dynamic BMP
    HAL& hal = touchgfx_generic_init<HALSDL2>(dma, lcd, tc, 480, 272,  (uint16_t*)bmpCache, sizeof(bmpCache), 1);

    // Initialize SDL
    if (!dynamic_cast<HALSDL2&>(hal).sdl_init(argc, argv))
    {
        return EXIT_FAILURE;
    }

    touchgfx::HAL::getInstance()->taskEntry(); //Never returns

    return EXIT_SUCCESS;
}
