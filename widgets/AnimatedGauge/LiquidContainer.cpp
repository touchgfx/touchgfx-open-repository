#include <gui/template_screen/LiquidContainer.hpp>
#include <touchgfx/Color.hpp>

LiquidContainer::LiquidContainer()
{
}

void LiquidContainer
::init(int containerImageId, int liquidImageId, 
       int containerTopOffset, int containerBottomOffset,
       int liquidSpeed, 
       int textId, int textX, int textY, int textWidth, int textHeight,
       int min, int max, int start, int step)
{

  // initialize and position container and liquid images
  container.setBitmap(Bitmap(containerImageId));
  liquid.setBitmap(Bitmap(liquidImageId));
  liquid2.setBitmap(Bitmap(liquidImageId));
  container.setXY(0, 0);
  liquid.setXY(0, 0);
  liquid2.setXY(liquid.getWidth(), 0);
  setWidth(container.getWidth());
  setHeight(container.getHeight());
  
  // set number of pixels from top of image to top and bottom of container
  pixelTopOffset = containerTopOffset;
  pixelBottomOffset = containerBottomOffset;

  // intialize text
  levelTxt.setWildcard(levelTxtbuf);
  levelTxt.setTypedText(TypedText(textId));
  levelTxt.setPosition(textX, textY, textWidth, textHeight);
  levelTxt.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));

  // set level
  minLevel = min;
  maxLevel = max;
  stepLevel = step;
  setLevel(start);

  // add components
  add(liquid);
  add(liquid2);
  add(container);
  add(levelTxt);

  // initizlize animation
  speed = liquidSpeed;
  Application::getInstance()->registerTimerWidget(this);
}

void LiquidContainer::setLevel(int level)
{
  // boundary check
  if (level < minLevel)
    level = minLevel;
  if (level > maxLevel)
    level = maxLevel;

  // set level
  currentLevel = level;

  // move liquid up or down
  int offset = 
    (pixelBottomOffset-pixelTopOffset) 
    * (maxLevel-currentLevel)/(maxLevel-minLevel) 
    + pixelTopOffset;
  liquid.moveTo(liquid.getX(), offset);
  liquid2.moveTo(liquid2.getX(), offset);

  // update level text
  Unicode::snprintf(levelTxtbuf, 5, "%d", currentLevel);
  levelTxt.invalidate();
}

void LiquidContainer::handleTickEvent()
{
  // scroll liquid images
  liquid.moveRelative(speed, 0);
  liquid2.moveRelative(speed, 0);

  // when reaching far left, scoot over to the right
  if (liquid.getX()+liquid.getWidth() < container.getWidth()) {
    liquid.moveRelative(liquid.getWidth(), 0);
    liquid2.moveRelative(liquid.getWidth(), 0);
  }

  // when reaching far right, scoot over to the left
  if (liquid.getX() > 0) {
    liquid.moveRelative(-liquid.getWidth(), 0);
    liquid2.moveRelative(-liquid.getWidth(), 0);
  }
}

void LiquidContainer::handleClickEvent(const ClickEvent& evt)
{
  // for demonstration purposes, adjust level up or down when clicked
  if (evt.getType() == ClickEvent::RELEASED) {
    int delta = (evt.getY() < this->getHeight()/2) ? 1 : -1;
    setLevel(currentLevel + stepLevel*delta);
  }
}
