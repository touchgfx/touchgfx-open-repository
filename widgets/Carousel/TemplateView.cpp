#include <gui/template_screen/TemplateView.hpp>
#include <BitmapDatabase.hpp>

void TemplateView::setupScreen()
{
    counter = 0;

    bgImage.setBitmap(Bitmap(BITMAP_BACKGROUND_ID));
    bgImage.setXY(0, 0);

    carousel.setPosition(36, 26, 390, 170);
    
    // The y position difference between the images
    uint16_t yDiff = 20;

    uint16_t widthOfSmallElements = Bitmap(BITMAP_BROWSER00_SMALL_ID).getWidth();
    uint16_t widthOfMediumElements = Bitmap(BITMAP_BROWSER00_MEDIUM_ID).getWidth();
    uint16_t widthOfLargeElements = Bitmap(BITMAP_BROWSER00_LARGE_ID).getWidth();
    uint16_t widthOfInvisibleElements = widthOfSmallElements - 30;

    uint16_t heightOfSmallElements = Bitmap(BITMAP_BROWSER00_SMALL_ID).getHeight();
    uint16_t heightOfMediumElements = Bitmap(BITMAP_BROWSER00_MEDIUM_ID).getHeight();
    uint16_t heightOfLargeElements = Bitmap(BITMAP_BROWSER00_LARGE_ID).getHeight();
    uint16_t heightOfInvisibleElements = heightOfSmallElements - 30;

    uint16_t offsetWidthForInvisibleEndElements = 20;
    uint16_t visibleWidthOfSmallElements = 40;
    uint16_t visibleWidthOfMediumElements = 60;


    carousel.setPositionOfCarouselElement(0, 0,                                
        (3 * yDiff), widthOfInvisibleElements, heightOfInvisibleElements);

    carousel.setPositionOfCarouselElement(1, offsetWidthForInvisibleEndElements,
        (2* yDiff), widthOfSmallElements, heightOfSmallElements);

    carousel.setPositionOfCarouselElement(2, carousel.getXPositionOfVisibleElement(1) + visibleWidthOfSmallElements,
        yDiff, widthOfMediumElements, heightOfMediumElements);

    carousel.setPositionOfCarouselElement(3, carousel.getXPositionOfVisibleElement(2) + visibleWidthOfMediumElements,
        0, widthOfLargeElements, heightOfLargeElements);

    carousel.setPositionOfCarouselElement(4, carousel.getXPositionOfVisibleElement(3) + widthOfLargeElements - widthOfMediumElements + visibleWidthOfMediumElements,
        yDiff, widthOfMediumElements, heightOfMediumElements);

    carousel.setPositionOfCarouselElement(5, carousel.getXPositionOfVisibleElement(4) + widthOfMediumElements - widthOfSmallElements + visibleWidthOfSmallElements,
        (2 * yDiff), widthOfSmallElements, heightOfSmallElements);

    carousel.setPositionOfCarouselElement(6, carousel.getXPositionOfVisibleElement(5) + offsetWidthForInvisibleEndElements + 20,
        (3 * yDiff), widthOfInvisibleElements, heightOfInvisibleElements);
     

    carousel.addElement(Bitmap(BITMAP_BROWSER00_SMALL_ID), Bitmap(BITMAP_BROWSER00_MEDIUM_ID), Bitmap(BITMAP_BROWSER00_LARGE_ID));
    carousel.addElement(Bitmap(BITMAP_BROWSER01_SMALL_ID), Bitmap(BITMAP_BROWSER01_MEDIUM_ID), Bitmap(BITMAP_BROWSER01_LARGE_ID));
    carousel.addElement(Bitmap(BITMAP_BROWSER02_SMALL_ID), Bitmap(BITMAP_BROWSER02_MEDIUM_ID), Bitmap(BITMAP_BROWSER02_LARGE_ID));
    carousel.addElement(Bitmap(BITMAP_BROWSER03_SMALL_ID), Bitmap(BITMAP_BROWSER03_MEDIUM_ID), Bitmap(BITMAP_BROWSER03_LARGE_ID));
    carousel.addElement(Bitmap(BITMAP_BROWSER04_SMALL_ID), Bitmap(BITMAP_BROWSER04_MEDIUM_ID), Bitmap(BITMAP_BROWSER04_LARGE_ID));

    carousel.setSelectedElement(3);

#ifdef SIMULATOR
    carousel.setDuration(14);
#else
    carousel.setDuration(4);
#endif
    add(bgImage);
    add(carousel);

    animate = true;
    elementSelected = false;
}

void TemplateView::tearDownScreen()
{

}

void TemplateView::handleTickEvent()
{
    counter++;

    if (animate && counter%100 == 0)
    {
        carousel.selectedNext();
    }
}

void TemplateView::handleClickEvent(const ClickEvent& evt)
{

    if (evt.getType() != ClickEvent::RELEASED || evt.getX() < 0 || evt.getX() > HAL::DISPLAY_WIDTH)
    {
        return;
    }


    if (evt.getX() < 160)
    {
        animate = false;
        carousel.selectedPrevious();
    }
    else if (evt.getX() > 320)
    {
        animate = false;
        carousel.selectedNext();
    }
    else
    {
        if (!elementSelected)
        {
            carousel.highlightSelectedElement();
            animate = false;
            elementSelected = true;
        }
        else
        {
            carousel.cancelHighlightOfSelectedElement();
            animate = true;
            elementSelected = false;
        }

    }
}
