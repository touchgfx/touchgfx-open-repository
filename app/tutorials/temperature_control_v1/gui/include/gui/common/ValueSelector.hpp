#ifndef VALUE_SELECTOR_HPP
#define VALUE_SELECTOR_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>

using namespace touchgfx;

class ValueSelector : public Container
{
public:
    ValueSelector();
    virtual ~ValueSelector();

    void handleClickEvent(const ClickEvent& evt);
    void handleDragEvent(const DragEvent& evt);

    /**
     * Associates a callback with the event that the ValueSelector bar has changed to a new
     * value.
     *
     * @param callback The callback to be associated with the callback.
     */
    void setNewValueCallback(GenericCallback<const ValueSelector&, int>& callback);

    /**
     * Sets value range.
     *
     * @param min The value returned when the ValueSelector bar is at its minimum position.
     * @param max The value returned when the ValueSelector bar is at its maximum position.
     */
    void setValueRange(int min, int max);

    /**
     * Updates the ValueSelector with a new value (must be in the value range).
     *
     * @param value The new value.
     */
    void setValue(int value);
        
    /**
     * Get the current value.
     * 
     * @return The current value.
     */
    int getValue();

private:
    // Vertical spacing that increases the height of the value selector and thereby the touch area
    static const int VERTICAL_HEIGHT_SPACING = 10;  

    int minValue;
    int maxValue;

    Image background;
    Image bar;
    Image knob;
    Container barViewport;

    int knobOffset;

    int currentValue;
    GenericCallback<const ValueSelector&, int>* newValueCallback;    

    void setBarSize(int16_t xValue);

    int pixelsToValue(int pixels);
    int valueToPixels(int value);
    int valueRangeSize();
    int maxBarWidth();
};

#endif /* VALUE_SELECTOR_HPP */
