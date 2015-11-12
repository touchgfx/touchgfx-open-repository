#ifndef LIQUID_CONTAINER_HPP
#define LIQUID_CONTAINER_HPP

#include <mvp/View.hpp>
#include <gui/template_screen/TemplatePresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <texts/TextKeysAndLanguages.hpp>

using namespace touchgfx;

class LiquidContainer : public Container
{
public:
  LiquidContainer();
  void init(int containerImageId, int liquidImageId, 
	    int containerTopOffset, int containerBottomOffset, 
	    int liquidSpeed, 
	    int textId, int textX, int textY, int textWidth, int textHeight,
	    int min, int max, int start, int step);
  void setLevel(int level);
  void handleTickEvent();
  virtual void handleClickEvent(const ClickEvent& evt);
private:
  Image container, liquid, liquid2;
  int pixelTopOffset, pixelBottomOffset;
  int minLevel, maxLevel, currentLevel, stepLevel;
  int speed;
  TextAreaWithOneWildcard levelTxt;
  Unicode::UnicodeChar levelTxtbuf[20];
};

#endif // LIQUID_CONTAINER_HPP
