#include <gui/template_screen/TemplateView.hpp>
#include <gui/common/JPEGFileLoader.hpp>
#include <touchgfx/Color.hpp>
#include <stdio.h>

//buffer needed by LibJPEG when decoding
uint8_t lineBuffer[320*3];

void TemplateView::setupScreen()
{
    FILE* f = fopen("image.jpg", "rb");
    uint16_t width, height;
    
    JPEGFileLoader::getJPEGDimensions(f, width, height);
    BitmapId bmpId;

    //create dynamic bitmap matching file dimensions and in format matching LCD
    if (HAL::lcd().bitDepth() == 16)
    {
        bmpId = Bitmap::dynamicBitmapCreate(width, height, Bitmap::RGB565);
    }
    else
    {
        bmpId = Bitmap::dynamicBitmapCreate(width, height, Bitmap::RGB888);
    }

    if (bmpId != BITMAP_INVALID)
    {
        //Succesfully created, load JPEG file to bitmap
        JPEGFileLoader::readJPEGFile(Bitmap(bmpId), f, lineBuffer);
    }
    
    //Image shall show the loaded bitmap
    image.setBitmap(Bitmap(bmpId));

    //Position image and add to View
    image.setXY(20, 20);
    add(image);
}

void TemplateView::tearDownScreen()
{
}
