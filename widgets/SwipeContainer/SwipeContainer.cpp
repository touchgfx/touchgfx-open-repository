#include <gui/common/SwipeContainer.hpp>
#include <touchgfx/EasingEquations.hpp>

using namespace touchgfx;

SwipeContainer::SwipeContainer() :
    Container(),
    currentState(NO_ANIMATION),
    numberOfScreens(0),
    animationCounter(0),
    swipeCutoff(80),
    dragX(0),
    animateDistance(0),
    startX(0),
    currentScreen(0),
    endElasticWidth(30),
    dotIndicator(),
    screens(EAST),
    childFocus(0),
    pressedX(0),
    pressedY(0),
    hasIssuedCancelEvent(false)
{
    touchgfx::Application::getInstance()->registerTimerWidget(this);

    setTouchable(true);

    Container::add(screens);
    Container::add(dotIndicator);
}

SwipeContainer::~SwipeContainer()
{
    touchgfx::Application::getInstance()->unregisterTimerWidget(this);
}

void SwipeContainer::add(Drawable& screen)
{
    screens.add(screen);
    numberOfScreens++;

    dotIndicator.setNumberOfDots(numberOfScreens);

    setWidth(screen.getWidth());
    setHeight(screen.getHeight());
}

void SwipeContainer::setEndSwipeElasticWidth(uint16_t width)
{
    endElasticWidth = width;
}

void SwipeContainer::setSwipeCutoff(uint16_t cutoff)
{
    swipeCutoff = cutoff;
}

void SwipeContainer::setDotIndicatorBitmaps(const touchgfx::Bitmap& normalDot, const touchgfx::Bitmap& highlightedDot)
{
    dotIndicator.setBitmaps(normalDot, highlightedDot);
}

void SwipeContainer::setDotIndicatorXY(int16_t x, int16_t y)
{
    dotIndicator.setXY(x, y);
}

void SwipeContainer::setDotIndicatorXYWithCenteredX(int16_t x, int16_t y)
{
    dotIndicator.setXY(x - dotIndicator.getWidth() / 2, y);
}

void SwipeContainer::setSelectedScreen(uint8_t screenIndex)
{
    currentScreen = screenIndex;
    dotIndicator.setHighlightPosition(currentScreen);
    adjustScreens();
}

void SwipeContainer::handleTickEvent()
{
    if (currentState == ANIMATE_SWIPE_CANCELLED_LEFT)
    {
        animateSwipeCancelledLeft();
    }
    else if (currentState == ANIMATE_SWIPE_CANCELLED_RIGHT)
    {
        animateSwipeCancelledRight();
    }
    else if (currentState == ANIMATE_LEFT)
    {
        animateLeft();
    }
    else if (currentState == ANIMATE_RIGHT)
    {
        animateRight();
    }
}

void SwipeContainer::handleClickEvent(const ClickEvent& evt)
{
    // If an animation is already in progress do not
    // react to clicks
    if (currentState != NO_ANIMATION)
    {
        return;
    }

    if (evt.getType() == ClickEvent::RELEASED)
    {
        // Save current position for use during animation
        animateDistance = dragX;
        startX = screens.getX();

        if (dragX < 0)
        {
            if (currentScreen == getNumberOfScreens()-1 || dragX > -swipeCutoff)
            {
                currentState = ANIMATE_SWIPE_CANCELLED_LEFT;
            }
            else
            {
                currentState = ANIMATE_LEFT;
            }
        }
        else if (dragX > 0)
        {
            if (currentScreen == 0 || dragX < swipeCutoff)
            {
                currentState = ANIMATE_SWIPE_CANCELLED_RIGHT;
            }
            else
            {
                currentState = ANIMATE_RIGHT;
            }
        }
    }
    // Check to see if any children should be notified of this event
    if (evt.getType() == ClickEvent::PRESSED)
    {
        Container::getLastChild(evt.getX(), evt.getY(), &childFocus);
        if (childFocus == this)
        {
            // If we found ourselves only, disregard
            childFocus = 0;
        }
        if (childFocus)
        {
            // We found a child which was also interested in this click event.
            // Delegate to the child
            hasIssuedCancelEvent = false;
            pressedX = evt.getX();
            pressedY = evt.getY();
            Rect r = childFocus->getAbsoluteRect();
            ClickEvent relative(evt.getType(), evt.getX() + rect.x - r.x, evt.getY() + rect.y - r.y);
            childFocus->handleClickEvent(relative);
        }
    }
    else if  (childFocus && evt.getType() == ClickEvent::RELEASED)
    {
        Rect r = childFocus->getAbsoluteRect();
        ClickEvent relative(evt.getType(), evt.getX() + rect.x - r.x, evt.getY() + rect.y - r.y);
        childFocus->handleClickEvent(relative);
        childFocus = 0;
    }
}

void SwipeContainer::handleDragEvent(const DragEvent& evt)
{
    // If an animation is already in progress do not
    // react to drags
    if (currentState != NO_ANIMATION)
    {
        return;
    }

    dragX += evt.getDeltaX();

    if (childFocus && !hasIssuedCancelEvent)
    {
        // If we have dragged further than the threshold, send a cancel event
        // to the child, such that e.g. a button will no longer be pressed.
        if (abs(dragX) > DRAG_CANCEL_THRESHOLD)
        {
            ClickEvent ce(ClickEvent::CANCEL, 0, 0);
            childFocus->handleClickEvent(ce);
            hasIssuedCancelEvent = true;
        }
    }

    // Do not show too much background next to end screens
    if (currentScreen == 0 && dragX > endElasticWidth)
    {
        dragX = static_cast<int16_t>(endElasticWidth);
    }
    else if (currentScreen == getNumberOfScreens()-1 && dragX < -endElasticWidth)
    {
        dragX = -static_cast<int16_t>(endElasticWidth);
    }

    adjustScreens();
}

void SwipeContainer::handleGestureEvent(const GestureEvent& evt)
{
    // Do not accept gestures while animating
    if (currentState != NO_ANIMATION)
    {
        return;
    }

    if (evt.getType() == evt.SWIPE_HORIZONTAL)
    {
        // Save current position for use during animation
        animateDistance = dragX;
        startX = screens.getX();

        if (childFocus && !hasIssuedCancelEvent)
        {
            ClickEvent ce(ClickEvent::CANCEL, 0, 0);
            childFocus->handleClickEvent(ce);
            hasIssuedCancelEvent = true;
        }

        if (evt.getVelocity() < 0  && currentScreen < getNumberOfScreens()-1)
        {
            currentState = ANIMATE_LEFT;
        }
        else if (evt.getVelocity() > 0  && currentScreen > 0)
        {
            currentState = ANIMATE_RIGHT;
        }
    }
}

void SwipeContainer::adjustScreens()
{
    screens.moveTo(-static_cast<int16_t>(currentScreen * getWidth()) + dragX, 0);
}

void SwipeContainer::animateSwipeCancelledLeft()
{
    uint8_t duration = 14;

    if (animationCounter <= duration)
    {
        int16_t delta = EasingEquations::backEaseOut(animationCounter, 0, -animateDistance, duration);
        dragX = animateDistance + delta;

        adjustScreens();
    }
    else
    {
        // Final step: stop the animation
        currentState = NO_ANIMATION;
        animationCounter = 0;
        dragX = 0;
        adjustScreens();
    }
    animationCounter++;
}

void SwipeContainer::animateSwipeCancelledRight()
{
    uint8_t duration = 14;

    if (animationCounter <= duration)
    {
        int16_t delta = EasingEquations::backEaseOut(animationCounter, 0, animateDistance, duration);
        dragX = animateDistance - delta;

        adjustScreens();
    }
    else
    {
        // Final step: stop the animation
        currentState = NO_ANIMATION;
        animationCounter = 0;
        dragX = 0;
        adjustScreens();
    }
    animationCounter++;
}

void SwipeContainer::animateLeft()
{
    uint8_t duration = 10;

    if (animationCounter <= duration)
    {
        int16_t delta = EasingEquations::cubicEaseOut(animationCounter, 0, getWidth() + animateDistance, duration);
        dragX = animateDistance - delta;

        adjustScreens();
    }
    else
    {
        // Final step: stop the animation
        currentState = NO_ANIMATION;
        animationCounter = 0;
        currentScreen++;
        dragX = 0;
        adjustScreens();
        dotIndicator.goRight();
    }
    animationCounter++;
}

void SwipeContainer::animateRight()
{
    uint8_t duration = 10;

    if (animationCounter <= duration)
    {
        int16_t delta = EasingEquations::cubicEaseOut(animationCounter, 0, getWidth() - animateDistance, duration);
        dragX = animateDistance + delta;

        adjustScreens();
    }
    else
    {
        // Final step: stop the animation
        currentState = NO_ANIMATION;
        animationCounter = 0;
        currentScreen--;
        dragX = 0;
        adjustScreens();
        dotIndicator.goLeft();
    }
    animationCounter++;
}

void SwipeContainer::getLastChild(int16_t x, int16_t y, Drawable** last)
{
    if (isTouchable())
    {
        // Hijack touch events - no do ask children.
        *last = this;
    }
}
