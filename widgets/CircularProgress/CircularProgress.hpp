#ifndef CIRCULARPROGRESS_HPP
#define CIRCUlARPROGRESS_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565Bitmap.hpp>
#include <BitmapDatabase.hpp>

using namespace touchgfx;

/**
 * @class CircularProgress CircularProgress.hpp CircularProgress.hpp
 *
 * @brief A circular progress bar.
 *        
 *        A circular progress bar. Using a nice bitmap and a fat circle with round end caps, it
 *        is possible to create a nice circular progress bar. The circular progress also
 *        accepts touch input which could be used if the widget is used as a volume control.
 *
 * @sa Container
 */
class CircularProgress : public Container
{
public:
    /**
     * @fn CircularProgress::CircularProgress();
     *
     * @brief Default constructor.
     *        
     *        Default constructor.
     */
    CircularProgress();

    /**
     * @fn virtual CircularProgress::~CircularProgress();
     *
     * @brief Destructor.
     *        
     *        Destructor.
     */
    virtual ~CircularProgress();

    /**
     * @fn void CircularProgress::setProgress(int percentage);
     *
     * @brief Sets the progress.
     *        
     *        Sets the progress. Progress is given in percentage (0-100).
     *
     * @param percentage The percentage.
     */
    void setProgress(int percentage);

    /**
     * @fn int CircularProgress::getProgress();
     *
     * @brief Gets the progress.
     *        
     *        Gets the progress.
     *
     * @return The progress.
     */
    int getProgress();

    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleDragEvent(const DragEvent& evt);

protected:
    static const int END_DEGREE = 116;           ///< Start angle for circular progress
    static const int START_DEGREE = -END_DEGREE; ///< End angle for circular progress

    Image background;                  ///< Background for entire circle progress
    Circle bar;                        ///< The actual circle progress
    PainterRGB565Bitmap bitmapPainter; ///< Painter to paint gradient bitmap as progress bar

    int currentPercentage;  ///< The current percentage

    /**
     * @fn void CircularProgress::updateBar(int touchX, int touchY);
     *
     * @brief Updates the bar.
     *        
     *        Updates the bar based on a touch event at newX, newY.
     *
     * @param touchX The new x coordinate.
     * @param touchY The new y coordinate.
     */
    void updateBar(int touchX, int touchY);
};

#endif /* CIRCULARPROGRESS_HPP */
