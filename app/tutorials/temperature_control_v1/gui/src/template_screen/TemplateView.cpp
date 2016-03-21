#include <gui/template_screen/TemplateView.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

void TemplateView::setupScreen()
{
    background.setBitmap(Bitmap(BITMAP_SETTINGS_BACKGROUND_ID));
    background.setXY(0, 0);
    add(background);

    setResetButtonActiveState(false);
    resetButton.setXY(60, 212);
    resetButton.setAction(buttonClickedCallback);
    add(resetButton);

    poolTemperatureText.setWildcard(poolTemperatureTextBuffer);
    poolTemperatureText.setTypedText(TypedText(T_TEMPERATURE_READOUT));
    poolTemperatureText.setPosition(334, 90, 140, 100);
    poolTemperatureText.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    add(poolTemperatureText);

    valueSelector.setXY(30, 120);
    valueSelector.setNewValueCallback(newTemperatureCallback);
    valueSelector.setValueRange(18, 32);
    valueSelector.setValue(24); // Default start value
    add(valueSelector);

    setResetValue(24); // Default reset value
}

void TemplateView::tearDownScreen()
{

}

void TemplateView::buttonClicked(const AbstractButton& source)
{
    if (&source == &resetButton)
    {
        valueSelector.setValue(resetValue);
        setResetButtonActiveState(false);
    }
}

void TemplateView::setResetValue(int value)
{
    resetValue = value;
    setResetButtonActiveState(resetValue != valueSelector.getValue());
}

void TemplateView::updatePoolTemperatureText(int16_t value)
{
    // Update wildcard text and invalidate text area,
    // which will result in it being redrawn.
    Unicode::snprintf(poolTemperatureTextBuffer, 5, "%d", value);
    poolTemperatureText.invalidate();
}

void TemplateView::newTemperatureHandler(const ValueSelector& selector, int value)
{
    updatePoolTemperatureText(value);

    // Make the reset button active if chosen value differs from the reset value
    setResetButtonActiveState(resetValue != value);
}

void TemplateView::setResetButtonActiveState(bool active)
{
    if (active)
    {
        resetButton.setBitmaps(Bitmap(BITMAP_RESET_BUTTON_ID), Bitmap(BITMAP_RESET_BUTTON_PRESSED_ID));
    }
    else
    {
        resetButton.setBitmaps(Bitmap(BITMAP_RESET_BUTTON_INACTIVE_ID), Bitmap(BITMAP_RESET_BUTTON_INACTIVE_ID));
    }
    resetButton.setTouchable(active);

    resetButton.invalidate();
}


