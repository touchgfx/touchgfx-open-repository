#include <gui/template_screen/TemplateView.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/FrontendApplication.hpp>

void TemplateView::setupScreen()
{
    background.setBitmap(Bitmap(BITMAP_SETTINGS_BACKGROUND_ID));
    background.setXY(0, 0);
    add(background);

    resetButton.setBitmaps(Bitmap(BITMAP_RESET_BUTTON_ID), Bitmap(BITMAP_RESET_BUTTON_PRESSED_ID));
    resetButton.setXY(60, 212);
    resetButton.setAction(buttonClickedCallback);
    add(resetButton);

    okButton.setBitmaps(Bitmap(BITMAP_OK_BUTTON_ID), Bitmap(BITMAP_OK_BUTTON_PRESSED_ID));
    okButton.setXY(300, 212);
    okButton.setAction(buttonClickedCallback);
    add(okButton);

    poolTemperatureText.setWildcard(poolTemperatureTextBuffer);
    poolTemperatureText.setTypedText(TypedText(T_TEMPERATURE_READOUT));
    poolTemperatureText.setPosition(334, 90, 140, 100);
    poolTemperatureText.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    add(poolTemperatureText);

    valueSelector.setXY(30, 120);
    valueSelector.setNewValueCallback(newTemperatureCallback);
    valueSelector.setValueRange(18, 32);
    //valueSelector.setValue(24); // Use callback instead
    valueSelector.setNewValueCallback(newTemperatureCallback);
    add(valueSelector);

    //setResetValue(24); // Called from presenter with model value instead
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
    else if (&source == &okButton)
    {
        presenter->poolTemperatureUpdated(valueSelector.getValue());
        static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreen();
    }
}

void TemplateView::setResetValue(int value)
{
    resetValue = value;
    setResetButtonActiveState(resetValue != valueSelector.getValue());
}

void TemplateView::setPoolTemperature(int value)
{
    valueSelector.setValue(value);
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

