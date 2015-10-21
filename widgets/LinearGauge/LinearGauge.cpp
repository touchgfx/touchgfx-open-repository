#include <gui/common/LinearGauge.hpp>
#include <BitmapDatabase.hpp>

LinearGauge::LinearGauge() : 
  Container(),
  orientation(VERTICAL_NORTH),
  currentVal(0),
  lowerBound(0),
  upperBound(100),
  stepSize(1),
  animate(0),
  animationDuration(5),
  gaugeAnimationEndedCallback(this, &LinearGauge::gaugeAnimationEndedHandler)
{
  gaugeImg.setMoveAnimationEndedAction(gaugeAnimationEndedCallback);
  add(bg);
  add(gaugeContainer);
}
  
void LinearGauge::setBounds(uint16_t lower, uint16_t upper)
{
  lowerBound = lower;
  upperBound = upper;
}

void LinearGauge::enableAnimation(bool enable)
{
  animate = enable;
}

void LinearGauge::setAnimationDuration(uint8_t duration)
{
  animationDuration = duration;
}
  
void LinearGauge::setOrientation(Orientation o)
{
  orientation = o;
}

LinearGauge::HV_Offset LinearGauge::getGaugeLevelOffsetRel()
{
  HV_Offset offset;
  
  offset.x = (gaugeContainer.getWidth()*(currentVal-lowerBound))/(upperBound-lowerBound);
  offset.y = (gaugeContainer.getHeight()*(currentVal-lowerBound))/(upperBound-lowerBound);  
  
  return offset;
}

LinearGauge::HV_Offset LinearGauge::getGaugeLevelIndicatorPos()
{
  HV_Offset offset, offset_rel;
  
  //Get local gauge offset
  offset_rel = getGaugeLevelOffsetRel();
    
  //Apply orientation
  switch(orientation)
  {
    case HORIZONTAL_WEST:
      offset.x = gaugeContainer.getX()+ offset_rel.x;
      offset.y = 0;
      break;  
      
    case HORIZONTAL_EAST:
      offset.x = gaugeContainer.getX()+gaugeContainer.getWidth()-offset_rel.x;
      offset.y = 0; 
      break;  
      
    case VERTICAL_NORTH:
      offset.x = 0;
      offset.y = gaugeContainer.getY()+gaugeContainer.getHeight()-offset_rel.y;
      break;          
      
    case VERTICAL_SOUTH:
      offset.x = 0;
      offset.y = gaugeContainer.getY()+offset_rel.y;
      break;           
  }
  
  return offset;
}

void LinearGauge::setGaugeLevel(uint16_t level)
{    
  //Set current value reference
  currentVal = level; 
  
  if(level >= lowerBound && level<=upperBound)
  {  
    uint16_t move_x, move_y;
    HV_Offset offset_rel = getGaugeLevelOffsetRel();
        
    switch(orientation)
    {            
      case HORIZONTAL_WEST:
        move_x = -gaugeContainer.getWidth()+offset_rel .x; 
        move_y = gaugeImg.getY();
        break;  
        
      case HORIZONTAL_EAST:
        move_x = gaugeContainer.getWidth()-offset_rel .x;
        move_y = gaugeImg.getY();
        break;  
        
      case VERTICAL_NORTH:
        move_x = gaugeImg.getX();
        move_y = gaugeContainer.getHeight()-offset_rel .y;            
        break;          
        
      case VERTICAL_SOUTH:
        move_x = gaugeImg.getX();
        move_y = -gaugeContainer.getHeight()+offset_rel.y;            
        break;                  
    }    
    //Depending on animate setting start a move animation or use regular moveTo 
    animate? gaugeImg.startMoveAnimation( move_x, move_y, animationDuration, EasingEquations::linearEaseNone, EasingEquations::linearEaseIn ) : gaugeImg.moveTo(move_x, move_y);   
  }
  else 
  {
    //Out of bounds - Reset to lowerBound
    setGaugeLevel(lowerBound);
  }
  
  //Redraw
  invalidate();    
}

void LinearGauge::setBackground(const touchgfx::Bitmap& background)
{
  bg.setBitmap(background);
  setWidth(background.getWidth());
  setHeight(background.getHeight());
}

void LinearGauge::setupGauge(const touchgfx::Bitmap& gauge, uint16_t x, uint16_t y, uint16_t initialVal, uint16_t lowerBound, uint16_t upperBound, Orientation orientation)
{
  gaugeImg.setBitmap(gauge);
  gaugeContainer.setWidth(gaugeImg.getWidth());
  gaugeContainer.setHeight(gaugeImg.getHeight());
  
  //Configure gauge
  setBounds(lowerBound, upperBound);
  setOrientation(orientation);
  
  //Set reference point: adjust gauge relative to background container (100% filled)
  gaugeContainer.setXY(x, y);
  gaugeContainer.add(gaugeImg);  
  
  //Temporarily disable Animation, if enabled, while setting initial value 
  enableAnimation(false);
  setGaugeLevel(initialVal);
  enableAnimation(animate);
}

void LinearGauge::setStepSize(uint8_t size)
{
  stepSize = size;        
}

void LinearGauge::stepPos()
{  
  if(currentVal+stepSize <= (upperBound) ) 
  {
    currentVal += stepSize; 
  }
  else
  {
    currentVal = upperBound;
  }
  
  setGaugeLevel(currentVal);
}


void LinearGauge::stepNeg()
{
  if(currentVal-stepSize >= lowerBound )
  {
    currentVal-=stepSize;
  }
  else
  {
    currentVal = lowerBound;
  }
  
  setGaugeLevel(currentVal);
}

void LinearGauge::gaugeAnimationEndedHandler(const MoveAnimator<Image>& image)
{

}
