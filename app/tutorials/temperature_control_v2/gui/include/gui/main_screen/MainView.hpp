#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <mvp/View.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/common/ValueSelector.hpp>

using namespace touchgfx;

/**
 * The View for a template screen. In the MVP paradigm, the view is a
 * passive interface that only displays the user interface and routes
 * any events from the user interface to the presenter. Normally it is the
 * responsibility of the presenter to act upon those events.
 *
 * By deriving from View, this class has a presenter pointer, which is configured
 * automatically.
 */
class MainView : public View<MainPresenter>
{
public:
    /**
     * The view constructor. Note that the constructor runs before the new screen is
     * completely initialized, so do not place code here that causes anything to be drawn.
     * Use the setupScreen function instead.
     */
    MainView()
        : buttonClickedCallback(this, &MainView::buttonClicked)
    {
    }
    virtual ~MainView() { }

    /**
     * This function is called automatically when the view is activated. This function
     * should add widgets to the root container, configure widget sizes and event
     * callbacks, et cetera.
     */
    virtual void setupScreen();

    /**
     * This function is called automatically when transitioning to a different screen
     * than this one. Can optionally be used to clean up.
     */
    virtual void tearDownScreen();

    void buttonClicked(const AbstractButton& source);

    void setOutdoorTemperature(int newTemperature);
    void setPoolTemperature(int newTemperature);

private:
    Image background;

    Button adjustButton;
    Callback<MainView, const AbstractButton&> buttonClickedCallback;

    TextAreaWithOneWildcard outdoorTemperatureText;
    Unicode::UnicodeChar outdoorTemperatureTextBuffer[5];
        
    TextAreaWithOneWildcard poolTemperatureText;
    Unicode::UnicodeChar poolTemperatureTextBuffer[5];
};

#endif // MAIN_VIEW_HPP
