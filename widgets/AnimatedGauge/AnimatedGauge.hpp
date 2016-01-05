#ifndef ANIMATED_GAUGE_HPP
#define ANIMATED_GAUGE_HPP

#include <mvp/View.hpp>
#include <gui/template_screen/TemplatePresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <texts/TextKeysAndLanguages.hpp>

using namespace touchgfx;

class AnimatedGauge : public Container
{
public:
  AnimatedGauge();
  void init(int bgImageId, // foreground image
	    int fgImageId, // background image
	    int topPixels, // top of transparent foreground image viewport
	    int bottomPixels, // bottom of transparent foreground image viewport
	    int scrollSpeed, // number of pixels to scroll at a time
	    int textId, // text label id
	    int textX, // text label postion X
	    int textY, // text label position Y
	    int textWidth, // text label width
	    int textHeight, // text label height
	    int minValue, // minimum gauge value
	    int maxValue, // maximum gauge value
	    int startValue, // starting gauge value
	    int stepValue); // gauge value changed when clicked
  void setLevel(int level);
  void handleTickEvent();
  virtual void handleClickEvent(const ClickEvent& evt);
private:
  Image fgImage, bgImageLeft, bgImageRight;
  int viewportTop, viewportBottom;
  int minLevel, maxLevel, currentLevel, stepLevel;
  int speed;
  TextAreaWithOneWildcard levelTxt;
  Unicode::UnicodeChar levelTxtbuf[20];
};

#endif // ANIMATED_GAUGE_HPP
