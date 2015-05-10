#include <gui/common/Lens.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <math.h>
#include <BitmapDatabase.hpp>

Lens::Lens()
{
	// calculate the distortion of the lens
	// derivations of the formula can be found online, for instance in the demo effects collection at 
	// http://demo-effects.cvs.sourceforge.net/viewvc/demo-effects/demo-effects/LENS/lens.c?view=markup
	for (int y = 0; y < lensRadius; y++) {
		for (int x = 0; x < lensRadius; x++) {
			int ix, iy, offset;
			if ((x * x + y * y) < (lensRadius * lensRadius)) 
			{
				float shift = lensZoom/sqrt((float)lensZoom*lensZoom - (x*x + y*y - lensRadius*lensRadius));
				ix = (int)(x * shift - x);
				iy = (int)(y * shift - y);
			} 
			else 
			{
				ix = 0;
				iy = 0;
			}
			offset = (iy * touchgfx::HAL::DISPLAY_WIDTH + ix);
			lens[lensRadius - y][lensRadius - x] = -offset;
			lens[lensRadius + y][lensRadius + x] = offset;
			offset = (-iy * touchgfx::HAL::DISPLAY_WIDTH + ix);
			lens[lensRadius + y][lensRadius - x] = -offset;
			lens[lensRadius - y][lensRadius + x] = offset;
		}
	}
	setWidth(lensWidth);
	setHeight(lensWidth);

	lensImage.setBitmap(touchgfx::Bitmap(BITMAP_LENS_IMAGE_ID));
}

touchgfx::Rect Lens::getSolidRect() const
{
	return touchgfx::Rect();
}

void Lens::draw(const touchgfx::Rect& invalidatedArea) const
{
	uint16_t *fb = touchgfx::HAL::getInstance()->lockFrameBuffer();

	touchgfx::Rect abs(0,0,getWidth(),getHeight());
	translateRectToAbsolute(abs);

	// since we both read and write the frame buffer, we split the loops in to four sections/quadrants
	// and run through them left to right or right to left, top to bottom or bottom to top,
	int16_t middleX = getWidth()/2;
	int16_t middleY = getHeight()/2;

	for(int y = invalidatedArea.y; y < invalidatedArea.bottom() && y <= middleY; y++)
	{
		for(int x = invalidatedArea.x; x < invalidatedArea.right() && x <= middleX; x++)
		{
			apply(fb, abs.x, abs.y, x, y);
		}

		for(int x = invalidatedArea.right()-1; x > middleX && x >= invalidatedArea.x; x--)
		{
			apply(fb, abs.x, abs.y, x, y);
		}
	}

	for(int y = invalidatedArea.bottom()-1; y > middleY && y >= invalidatedArea.y; y--)
	{
		for(int x = invalidatedArea.x; x < invalidatedArea.right() && x <= middleX; x++)
		{
			apply(fb, abs.x, abs.y, x, y);
		}

		for(int x = invalidatedArea.right()-1; x > middleX && x >= invalidatedArea.x; x--)
		{
			apply(fb, abs.x, abs.y, x, y);
		}
	}

	touchgfx::HAL::getInstance()->unlockFrameBuffer();

	touchgfx::Rect dirtyBitmapArea = touchgfx::Bitmap(lensImage.getBitmap()).getRect() & invalidatedArea;
	touchgfx::HAL::lcd().drawPartialBitmap(touchgfx::Bitmap(lensImage.getBitmap()), abs.x, abs.y, dirtyBitmapArea, 255);
}

void Lens::apply(uint16_t* fb, int absx, int absy, int x, int y) const
{
	int16_t lensOffset = lens[y][x];
	uint32_t fbOffset = x+absx + (y+absy) * touchgfx::HAL::DISPLAY_WIDTH;
	if((int32_t)fbOffset + lensOffset < 0)
	{
		fb[fbOffset] = fb[fbOffset + lensOffset + touchgfx::HAL::DISPLAY_HEIGHT*touchgfx::HAL::DISPLAY_WIDTH];
	}
	else if((int32_t)fbOffset + lensOffset > touchgfx::HAL::DISPLAY_HEIGHT*touchgfx::HAL::DISPLAY_WIDTH)
	{
		fb[fbOffset] = fb[fbOffset + lensOffset - touchgfx::HAL::DISPLAY_HEIGHT*touchgfx::HAL::DISPLAY_WIDTH];
	}
	else
	{
		fb[fbOffset] = fb[fbOffset + lensOffset];
	}
}

