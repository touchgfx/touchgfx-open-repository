#ifndef LENS_HPP
#define LENS_HPP

#include <touchgfx/widgets/Widget.hpp>
#include <touchgfx/hal/Types.hpp>
#include <touchgfx/widgets/Image.hpp>

/**
* @class Lens
*
* Lens shows a lens like effect on top of the frame buffer
*
* This widget is part of the TouchGFX Open Widget Repository. 
* https://github.com/draupnergraphics/touchgfx-open-repository
*
* @note This version of a lens, will not draw it self correctly if solid
*       widgets are placed on top of it. This is due to the fact that
*       the lens uses data from the frame buffer and the data 
*       below the lens (and the solid widgets) will not be updated in this case
*
* @sa touchgfx::Widget
*/
class Lens : public touchgfx::Widget
{
public:
	/**
	* @fn Lens::Lens();
	*
	* @brief initializes the lens data
	*/
	Lens();

	/**
	* @fn virtual touchgfx::Rect Lens::getSolidRect() const;
	*
	* @brief Report the solid dimensions of this widget. 
	*        As we would like the frame buffer below to be drawn, 
	*        the widget is reported as transparent
	*        
	* @return an empty rectangle.
	*/
	virtual touchgfx::Rect getSolidRect() const;

	/**
	* @fn virtual void Lens::draw(const touchgfx::Rect& invalidatedArea) const;
	*
	* @brief read, distort and write the frame buffer contents.
	*
	* @param invalidatedArea The part of the widget that should be drawn.
	*/
	virtual void draw(const touchgfx::Rect& invalidatedArea) const;
private:
	void apply(uint16_t* fb, int absx, int absy, int x, int y) const;

	static const uint8_t lensRadius = 100;
	static const uint8_t lensWidth = 2*lensRadius;
	static const uint8_t lensZoom = 40;
	int16_t lens[lensWidth][lensWidth]; //note: move the lens data to flash
	touchgfx::Image lensImage;
};

#endif