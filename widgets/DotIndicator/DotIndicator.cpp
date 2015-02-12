#include <gui/common/DotIndicator.hpp>
#include <assert.h>

DotIndicator::DotIndicator() :
    Container(),
    unselectedDots(touchgfx::EAST),
    dotHighlighted(),
    numberOfDots(0),
    currentDot(0)
{
    unselectedDots.setXY(0, 0);
    dotHighlighted.setXY(0, 0);

    this->add(unselectedDots);
    this->add(dotHighlighted);
}

DotIndicator::~DotIndicator()
{
}

void DotIndicator::setNumberOfDots(uint8_t size)
{
    numberOfDots = size;

    assert(numberOfDots > 0 && "At least one dot is needed"); /*lint !e920 Ignore lint error in Visual Studio implementation of assert(...) */
    assert(numberOfDots <= MAX_SIZE && "Above maximum number of dots"); /*lint !e920 Ignore lint error in Visual Studio implementation of assert(...) */

    unselectedDots.removeAll();
    for (int i = 0; i < numberOfDots; i++)
    {
        unselectedDots.add(dotNormal[i]);
    }
    // adjust size of container according to the actual bitmaps
    setWidth(unselectedDots.getWidth());
    setHeight(unselectedDots.getHeight());
    setHighlightPosition(currentDot = 0);
}

void DotIndicator::setBitmaps(const touchgfx::Bitmap& normalDot, const touchgfx::Bitmap& highlightedDot)
{
    dotHighlighted.setBitmap(highlightedDot);
    for (int i = 0; i < MAX_SIZE - 1; i++)
    {
        dotNormal[i].setBitmap(normalDot);
    }
    if (numberOfDots > 0)
    {
        setNumberOfDots(numberOfDots);
    }
}

void DotIndicator::goRight()
{
    setHighlightPosition(currentDot = (currentDot + 1) % numberOfDots);
}

void DotIndicator::goLeft()
{
    setHighlightPosition(currentDot = (currentDot + numberOfDots - 1) % numberOfDots);
}

void DotIndicator::setHighlightPosition(uint8_t index)
{
    // note that index is unsigned
    if (index < numberOfDots)
    {
        dotHighlighted.setX( static_cast<int16_t>(index * dotNormal[0].getWidth()) );
    }
    invalidate();
}
