#ifndef LINEAR_GAUGE_HPP_
#define LINEAR_GAUGE_HPP_

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

using namespace touchgfx;

/**     
 * The purpose of the LinearGauge widget is to provide an application 
 * developer with means of advancing and declining values in a linear, 
 * graphical fashion. Possible directions are: North, South, East, West. 
 * The application developer supplies a background image for the gauge 
 * as well as an image of the movable part of the gauge. The widget supports 
 * a linear ease-in equation and for animating between set gauge-values. 
 * An animations length is determined by a configurable duration. 

 * A developer can ask the LinearGauge widget for the position of it's 
 * gauge level container in an effort to provide a visible indicator that 
 * exists outside of the widgets container. One way of implementing this 
 * could be creating a further specialization, LinearGaugeWithIndicator.
 * 
 * This widget is part of the TouchGFX Open Widget Repository. 
 * https://github.com/draupnergraphics/touchgfx-widgets 
 */
class LinearGauge : public Container
{
public:
    LinearGauge ();
    ~LinearGauge () {}

    /**
     * Orientation of the LinearGauge. Has an impact on gauge level calculations. 
     */
    enum Orientation {
      HORIZONTAL_EAST = 0,
      HORIZONTAL_WEST,
      VERTICAL_NORTH,
      VERTICAL_SOUTH      
    } orientation;

    /**
     * Horizontal/Vertical Offset container. 
     */
    typedef struct 
    {
      /**
       * x is used solely for tracking the level of Horizontal oriented gauges
       */
      uint16_t x;
      
      /**
       * y is used solely for tracking the level of Vertically oriented gauges
       */
      uint16_t y;
    } HV_Offset;
    
    /**
     * Sets a gauge level.
     * @param level The level of the gauge
     */
    void setGaugeLevel(uint16_t level);        
    
    /**
     * Sets a background 
     * @param bitmap 
     */
    void setBackground(const Bitmap& bitmap);
    
    /**
     * Sets up gauge with required parameters
     * @param bitmap is the bitmap for the gauge level itself 
     * @param x is the relative x-axis offset of the gauge level bitmap to its parent container. 
     * @param y is the relative y-axis offset of the gauge level bitmap to its parent container. 
     */    
    void setupGauge(const Bitmap& bitmap, uint16_t x, uint16_t y, uint16_t initialVal, uint16_t lowerBound, uint16_t upperBound, Orientation orientation);    

    /**
     * Steps the gauge level in the positive direction based on @see stepSize and @see orientation
     */
    void stepPos();

    /**
     * Steps the gauge level in the negative direction based on @see stepSize and @see orientation
     */
    void stepNeg();
    
    /**
     * Sets the size of each step in positive or negative direction, see @stepPos and @stepNeg
     * @size the size of each step
     */
    void setStepSize(uint8_t size);
    
    /**
     * Enables or disables animation of steps made by @stepPos and @stepNeg and @see setGaugeLevel. Default behavior is a LinearEaseIn easing equation
     * Default animation duration is 5 ticks. @see setAnimationDuration.
     * @param enable Enables animation (true), disables animation (false)
    */
    void enableAnimation(bool enable);
        
    /**
     * Sets the duration of the move animation, if animation has been enabled.
     * @param duration the duration of the animation in ticks.
     */    
    void setAnimationDuration(uint8_t duration);
    
    /**
     * Sets the boundariesof the gauge. i.e. setBounds(400-1000) causes gauge to accept only values between 400-1000.
     * @param lowerBound the lower bound for the gauge
     * @param upperBound the upper bound for the gauge
     */   
    void setBounds(uint16_t lowerBound, uint16_t upperBound);
    
    /**
     * Returns Horizontal (x-axis) / Vertical (y-axis) gauge level offset in pixels relative to the parent gauge container. Usually called from an external source to get a reference for an indicator reference.
     */
    HV_Offset getGaugeLevelIndicatorPos(); 
    
    /**
     * Sets the orientation of the gauge and influences level calculations. 
     */    
    void setOrientation(Orientation o);
    
    /**
     * Event handler for when move animation has ended.
     */
    void gaugeAnimationEndedHandler(const MoveAnimator<Image>& image);
    
private:
  
  /**
  * Returns Horizontal (x-axis) / Vertical (y-axis) gauge level offset in pixels relative to the gauge content container
  * @see c
  */  
  HV_Offset getGaugeLevelOffsetRel(); //getGaugeLevel
  
  /**
   * Current value of the gauge
   */
  uint16_t currentVal;
  
  /**
   * Lower bound for the values of the gauge
   */
  uint16_t lowerBound;
     
  /**
   * Upper bound for the values of the gauge
   */
  uint16_t upperBound;
  
  /**
   * Size of steps made by @see step()
   */  
  uint16_t stepSize;
  
  /**
   * Determines if a move between values of the gauge should be animated
   */
  bool animate;

  /**
   * The container for the movable content of the gauge
   */  
  Container gaugeContainer;
  
  /**
   * The duration in ticks of a move animation
   */  
  uint8_t animationDuration;
  
  /**
   * The movable content of the gauge in the form of an image.
   */
  MoveAnimator<Image> gaugeImg;
  
  /**
   * Background image / outer shell for the gauge
   */
  Image bg;
  
  /**
   * Callback for when move animations have finished.
   */
  Callback<LinearGauge, const MoveAnimator<Image>& > gaugeAnimationEndedCallback;       
 
protected:
  
};

#endif /* LINEAR_GAUGE_HPP_ */