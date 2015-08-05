#include <gui/model/QRCode.hpp>
#include <stdlib.h>

//NOTE: in a real application you should override this and utilize a qr code generator
bool QRCode::at(uint16_t x, uint16_t y) const
{
    // a deterministic random value for x,y
    srand(x*123456+y*getWidth()*23456789);
    for(int i = 0; i < 100; i++)
    {
        srand(rand());
    }
    return ((rand() / (float)RAND_MAX) > 0.5);
}

uint16_t QRCode::getWidth() const
{
    return 16;
}

uint16_t QRCode::getHeight() const
{
    return 16;
}

