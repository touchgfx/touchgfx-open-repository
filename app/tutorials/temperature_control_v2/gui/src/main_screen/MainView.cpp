#include <gui/main_screen/MainView.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/FrontendApplication.hpp>

void MainView::setupScreen()
{
    background.setBitmap(Bitmap(BITMAP_MAIN_BACKGROUND_ID));
    background.setXY(0, 0);
    add(background);

    adjustButton.setBitmaps(Bitmap(BITMAP_ADJUST_BUTTON_ID), Bitmap(BITMAP_ADJUST_BUTTON_PRESSED_ID));
    adjustButton.setXY(300, 212);
    adjustButton.setAction(buttonClickedCallback);
    add(adjustButton);

    outdoorTemperatureText.setWildcard(outdoorTemperatureTextBuffer);
    outdoorTemperatureText.setTypedText(TypedText(T_TEMPERATURE_READOUT));
    outdoorTemperatureText.setPosition(114, 100, 120, 80);
    outdoorTemperatureText.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    add(outdoorTemperatureText);
    setOutdoorTemperature(18);

    poolTemperatureText.setWildcard(poolTemperatureTextBuffer);
    poolTemperatureText.setTypedText(TypedText(T_TEMPERATURE_READOUT));
    poolTemperatureText.setPosition(outdoorTemperatureText.getX() + (HAL::DISPLAY_WIDTH / 2), outdoorTemperatureText.getY(), 120, 80);
    poolTemperatureText.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    add(poolTemperatureText);
    setPoolTemperature(23);
}

void MainView::tearDownScreen()
{

}

void MainView::buttonClicked(const AbstractButton& source)
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoTemplateScreen();
}

void MainView::setOutdoorTemperature(int newTemperature)
{
    Unicode::snprintf(outdoorTemperatureTextBuffer, 5, "%d", newTemperature);
    outdoorTemperatureText.invalidate();
}

void MainView::setPoolTemperature(int newTemperature)
{
    Unicode::snprintf(poolTemperatureTextBuffer, 5, "%d", newTemperature);
    poolTemperatureText.invalidate();
}
