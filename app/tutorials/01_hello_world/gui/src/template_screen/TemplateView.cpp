#include <gui/template_screen/TemplateView.hpp>
#include <BitmapDatabase.hpp>

void TemplateView::setupScreen()
{

  background.setBitmap(Bitmap(BITMAP_BACKGROUND_ID));
  background.setXY(0, 0);
  add(background);

  borderBox.setBitmap(Bitmap(BITMAP_BORDER_BOX_ID));
  borderBox.setXY(162, 60);
  add(borderBox);

  imageViewport.setPosition(borderBox.getX(), borderBox.getY(), borderBox.getWidth(), borderBox.getHeight());
  add(imageViewport);

  leftButton.setBitmaps(Bitmap(BITMAP_LEFT_BUTTON_ID), Bitmap(BITMAP_LEFT_BUTTON_PRESSED_ID));
  leftButton.setXY(54, 70);
  leftButton.setAction(buttonClickedCallback);
  add(leftButton);

  rightButton.setBitmaps(Bitmap(BITMAP_RIGHT_BUTTON_ID), Bitmap(BITMAP_RIGHT_BUTTON_PRESSED_ID));
  rightButton.setXY(370, 70);
  rightButton.setAction(buttonClickedCallback);
  add(rightButton);

  images[0].setBitmap(Bitmap(BITMAP_IMAGE00_ID));
  images[1].setBitmap(Bitmap(BITMAP_IMAGE01_ID));
  images[2].setBitmap(Bitmap(BITMAP_IMAGE02_ID));

  for (int i = 0; i < NUMBER_OF_IMAGES; i++)
  {
    imageViewport.add(images[i]);

    // Place all the images outside the imageViewport so that they are not shown
    images[i].setXY(-images[selectedImageIndex].getWidth(), (imageViewport.getHeight() - images[i].getHeight()) / 2);
  }

  selectedImageIndex = 0;

  // Animate an image in from the left at start up
  slideImages(LEFT);
}

void TemplateView::tearDownScreen()
{

}

void TemplateView::buttonClicked(const AbstractButton &source)
{
  if (&source == &leftButton)
  {
    slideImages(LEFT);
  }
  else if (&source == &rightButton)
  {
    slideImages(RIGHT);
  }
}

void TemplateView::slideImages(SlideDirection direction)
{
  // Make sure that there is no animation running already
  for (int i = 0; i < NUMBER_OF_IMAGES; i++)
  {
    if (images[i].isRunning())
    {
      return;
    }
  }

  int animationDuration = 14;
  int animationDirection = (direction == LEFT) ? -1 : 1;
  int animationDistance = animationDirection * imageViewport.getWidth();

  // Select the next image index based on the animationDirection. Adding NUMBER_OF_IMAGES to avoid underrun.
  int nextSelectedImageIndex = (selectedImageIndex + NUMBER_OF_IMAGES + animationDirection) % NUMBER_OF_IMAGES;

  // Animate the current selected image out
  images[selectedImageIndex].startMoveAnimation(
    images[selectedImageIndex].getX() + animationDistance,
    images[selectedImageIndex].getY(),
    animationDuration,
    EasingEquations::cubicEaseOut);

  // Calculate the x position of the new selected image so that it will be centered in the imageViewport
  int xOffsetForImage = (imageViewport.getWidth() - images[nextSelectedImageIndex].getWidth()) / 2;

  // Position the selected image so that it will enter the imageViewport from the correct side
  images[nextSelectedImageIndex].moveTo(
    xOffsetForImage - animationDistance,
    images[nextSelectedImageIndex].getY());

  // Animate the next image in
  images[nextSelectedImageIndex].startMoveAnimation(
    images[nextSelectedImageIndex].getX() + animationDistance,
    images[nextSelectedImageIndex].getY(),
    animationDuration,
    EasingEquations::cubicEaseOut);

  selectedImageIndex = nextSelectedImageIndex;
}
