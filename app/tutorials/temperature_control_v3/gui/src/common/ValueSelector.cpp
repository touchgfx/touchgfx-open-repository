#include <gui/common/ValueSelector.hpp>
#include <BitmapDatabase.hpp>

ValueSelector::ValueSelector() :
    currentValue(0),
    newValueCallback(0)
{
    background.setBitmap(Bitmap(BITMAP_VALUE_SELECTOR_BACKGROUND_ID));
    background.setXY(0, VERTICAL_HEIGHT_SPACING);
    add(background);

    bar.setBitmap(Bitmap(BITMAP_VALUE_SELECTOR_BAR_ID));
    bar.setXY(0, 0);

    barViewport.setPosition(3, background.getY() + 7, bar.getWidth(), bar.getHeight());
    barViewport.add(bar);
    add(barViewport);

    knob.setBitmap(Bitmap(BITMAP_KNOB_ID));
    knob.setXY(0, background.getY() + 2);
    add(knob);

    knobOffset = knob.getWidth() / 2;

    setWidth(background.getWidth());
    setHeight(background.getHeight() + 2 * VERTICAL_HEIGHT_SPACING); 

    setTouchable(true);
    setValueRange(0, 100); // Set default value range
}

ValueSelector::~ValueSelector()
{
}

void ValueSelector::setNewValueCallback(GenericCallback<const ValueSelector&, int>& callback)
{
    newValueCallback = &callback;
}

void ValueSelector::handleClickEvent(const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::PRESSED)
    {
        setBarSize(evt.getX());
    }
}

void ValueSelector::handleDragEvent(const DragEvent& evt)
{
    setBarSize(evt.getNewX());
}

void ValueSelector::setBarSize(int16_t xClickPosition)
{
    int barWidth = MIN(MAX(0, xClickPosition - knobOffset), bar.getWidth());

    // Adjust the visible part of the bar
    barViewport.setWidth(barWidth);

    // Move the knob to the end of the bar
    knob.moveTo(barViewport.getX() + barWidth, knob.getY());

    // Make sure the value selector is repainted
    invalidate();

    int value = pixelsToValue(barWidth);

    if (value != currentValue)
    {
        currentValue = value;
        if ((newValueCallback != 0) && newValueCallback->isValid())
        {
            newValueCallback->execute(*this, currentValue);
        }
    }
}

void ValueSelector::setValueRange(int min, int max)
{
    minValue = min;
    maxValue = max;
}

void ValueSelector::setValue(int value)
{
    setBarSize(valueToPixels(value));
}

int ValueSelector::getValue()
{
    return currentValue;
}

int ValueSelector::pixelsToValue(int pixels)
{
    // Convert pixel offset for the bar to a value in the value range
    // The (maxBarWidth() - 1) factor makes sure that rounding is correct
    return ((pixels * valueRangeSize() + (maxBarWidth() - 1)) / maxBarWidth()) + minValue;
}

int ValueSelector::valueToPixels(int value)
{
    // Convert value to a pixel offset for the bar
    return (maxBarWidth() * (value - minValue) / valueRangeSize());
}

int ValueSelector::maxBarWidth()
{
    return bar.getWidth();
}

int ValueSelector::valueRangeSize()
{
    return maxValue - minValue;
}

