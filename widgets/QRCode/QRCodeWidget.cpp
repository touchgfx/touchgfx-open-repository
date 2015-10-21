#include <gui/template_screen/QRCodeWidget.hpp>


QRCodeWidget::QRCodeWidget() : 
    code(0),
    scale(1)
{
}

void QRCodeWidget::setQRCode(QRCode *qrCode)
{
    code = qrCode;
    updateSize();
}

void QRCodeWidget::draw(const touchgfx::Rect& invalidatedArea) const
{
    if(!code)
    {
        return;
    }

    touchgfx::Rect absolute = getAbsoluteRect();

    uint16_t *framebuffer = touchgfx::HAL::getInstance()->lockFrameBuffer();

    for(int y = invalidatedArea.y; y < invalidatedArea.bottom(); y++)
    {
        for(int x = invalidatedArea.x; x < invalidatedArea.right(); x++)
        {
            framebuffer[absolute.x + x + (absolute.y + y) * touchgfx::HAL::DISPLAY_WIDTH] = code->at(x / scale, y / scale) ? 0x0000 : 0xffff;
        }
    }

    touchgfx::HAL::getInstance()->unlockFrameBuffer();
}

touchgfx::Rect QRCodeWidget::getSolidRect() const
{
    return touchgfx::Rect(0,0,getWidth(), getHeight());
}

void QRCodeWidget::setScale(uint8_t s)
{
    scale = s;
    updateSize();
}

void QRCodeWidget::updateSize()
{
    if(code)
    {
        setWidth(code->getWidth() * scale);
        setHeight(code->getHeight() * scale);
    }    
}

