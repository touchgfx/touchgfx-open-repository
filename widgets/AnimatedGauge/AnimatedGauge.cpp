#include <gui/template_screen/AnimatedGauge.hpp>
#include <touchgfx/Color.hpp>

AnimatedGauge::AnimatedGauge()
{
}

void AnimatedGauge::init(int fgImageImageId, int bgImageId, 
			 int topPixels, int bottomPixels, 
			 int scrollSpeed, 
			 int textId, int textX, int textY, int textWidth, int textHeight,
			 int minValue, int maxValue, int startValue, int stepValue)
{

  // initialize and position foreground and background images
  fgImage.setBitmap(Bitmap(fgImageImageId));
  bgImageLeft.setBitmap(Bitmap(bgImageId));
  bgImageRight.setBitmap(Bitmap(bgImageId));
  fgImage.setXY(0, 0);
  bgImageLeft.setXY(0, 0);
  bgImageRight.setXY(bgImageLeft.getWidth(), 0);
  setWidth(fgImage.getWidth());
  setHeight(fgImage.getHeight());
  
  // set viewport
  viewportTop = topPixels;
  viewportBottom = bottomPixels;

  // intialize text
  levelTxt.setWildcard(levelTxtbuf);
  levelTxt.setTypedText(TypedText(textId));
  levelTxt.setPosition(textX, textY, textWidth, textHeight);
  levelTxt.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));

  // set level
  minLevel = minValue;
  maxLevel = maxValue;
  stepLevel = stepValue;
  setLevel(startValue);

  // add components
  add(bgImageLeft);
  add(bgImageRight);
  add(fgImage);
  add(levelTxt);

  // initizlize animation
  speed = scrollSpeed;
  Application::getInstance()->registerTimerWidget(this);
}

void AnimatedGauge::setLevel(int level)
{
  // boundary check
  if (level < minLevel) 
  {
      level = minLevel;
  }
  if (level > maxLevel) 
  {
    level = maxLevel;
  }

  // set level
  currentLevel = level;

  // move gauge up or down
  int offset = (viewportBottom-viewportTop) * (maxLevel-currentLevel)/(maxLevel-minLevel) + viewportTop;
  bgImageLeft.moveTo(bgImageLeft.getX(), offset);
  bgImageRight.moveTo(bgImageRight.getX(), offset);

  // update level text
  Unicode::snprintf(levelTxtbuf, 5, "%d", currentLevel);
  levelTxt.invalidate();
}

void AnimatedGauge::handleTickEvent()
{
  // scroll background images
  bgImageLeft.moveRelative(speed, 0);
  bgImageRight.moveRelative(speed, 0);

  // when reaching far left, scoot over to the right
  if (bgImageLeft.getX()+bgImageLeft.getWidth() < fgImage.getWidth()) 
  {
    bgImageLeft.moveRelative(bgImageLeft.getWidth(), 0);
    bgImageRight.moveRelative(bgImageLeft.getWidth(), 0);
  }

  // when reaching far right, scoot over to the left
  if (bgImageLeft.getX() > 0) 
  {
    bgImageLeft.moveRelative(-bgImageLeft.getWidth(), 0);
    bgImageRight.moveRelative(-bgImageLeft.getWidth(), 0);
  }
}

void AnimatedGauge::handleClickEvent(const ClickEvent& evt)
{
  // for demonstration purposes, adjust level up or down when clicked
  if (evt.getType() == ClickEvent::RELEASED) 
  {
    int delta = (evt.getY() < this->getHeight()/2) ? 1 : -1;
    setLevel(currentLevel + stepLevel*delta);
  }
}
