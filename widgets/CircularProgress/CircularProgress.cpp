#include <gui/common/CircularProgress.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <texts/TextKeysAndLanguages.hpp>

CircularProgress::CircularProgress()
{
    setTouchable(true);

    background.setBitmap(Bitmap(BITMAP_CIRCULAR_PROGRESS_BACKGROUND_ID));
    background.setXY(0, 0);
    add(background);

    bitmapPainter.setBitmap(Bitmap(BITMAP_CIRCULAR_PROGRESS_WHEEL_ID));

    bar.setPosition(background.getX(), background.getY(), background.getWidth(), background.getHeight());
    bar.setCenter(bar.getWidth() / 2.0f, bar.getHeight() / 2.0f);
    bar.setRadius(103);
    bar.setLineWidth(25);
    bar.setPainter(bitmapPainter);
    bar.setCapPrecision(15);
    bar.setArc(START_DEGREE, START_DEGREE); // Set art start fixed at START_DEGREE
    add(bar);

    setWidth(background.getWidth());
    setHeight(background.getHeight());
}

CircularProgress::~CircularProgress()
{
}

void CircularProgress::setProgress(int percentage)
{
    currentPercentage = percentage;
    if (percentage < 0) percentage = 0;
    if (percentage > 100) percentage = 100;
    int angle = START_DEGREE + (END_DEGREE - START_DEGREE) * percentage / 100;
    bar.updateArcEnd(angle); // Update arc end (keeping arc start at START DEGREE)
}


int CircularProgress::getProgress()
{
    return currentPercentage;
}

void CircularProgress::handleClickEvent(const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::PRESSED)
    {
        updateBar(evt.getX(), evt.getY());
    }
}

void CircularProgress::handleDragEvent(const DragEvent& evt)
{
    updateBar(evt.getNewX(), evt.getNewY());
}

void CircularProgress::updateBar(int touchX, int touchY)
{
    int centerX = 0;
    int centerY = 0;
    bar.getCenter(centerX, centerY);

    int16_t vx = touchX - centerX;
    int16_t vy = touchY - centerY;

    int length;
    int angleInDegrees = CWRUtil::angle<int>(vx, vy, length);
    // Touch too close to center is ignored
    if (length < 50) return;

    // Convert high degress to negative degrees
    if (angleInDegrees > 180) angleInDegrees -= 360;
    // Allow touch within 30 degress of limits to easier touch end points
    if (angleInDegrees < START_DEGREE - 30) return;
    if (angleInDegrees > END_DEGREE + 30) return;
    // Touch out of range is set in range
    if (angleInDegrees < START_DEGREE) angleInDegrees = START_DEGREE;
    if (angleInDegrees > END_DEGREE) angleInDegrees = END_DEGREE;

    // Update bar
    setProgress((angleInDegrees - START_DEGREE) * 100 / (END_DEGREE - START_DEGREE));
}
