#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <gui/common/GraphLine.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565Bitmap.hpp>
#include <BitmapDatabase.hpp>

#include <touchgfx/widgets/Box.hpp>

using namespace touchgfx;

/**
 * @class Graph
 *
 * @brief A connected line graph.
 *
 *        A connected line graph. The graph is limited to integer values for x and y and the
 *        values should not exceed 1000. If other values are needed they should be
 *        transformed/scaled to be in the interval [0;1000] before added to the graph.
 *
 * @sa Container
 */
class Graph : public Container
{
public:
    /**
     * @fn Graph::Graph();
     *
     * @brief Default constructor.
     */
    Graph();

    /**
     * @fn virtual Graph::~Graph()
     *
     * @brief Destructor.
     */
    virtual ~Graph();

    /**
     * @fn void Graph::setup(int newWidth, int newHeight, uint16_t lineColor);
     *
     * @brief Set characteristics of the graph.
     *
     *        Set characteristics of the graph.
     *
     * @param newWidth        Width of the new.
     * @param newHeight       Height of the new.
     * @param lineColor       The line color.
     */
    void setup(int newWidth, int newHeight, uint16_t lineColor);

    /**
     * @fn bool Graph::addValue(int x, int y)
     *
     * @brief Adds a point to the graph.
     *
     *        Adds a point to the graph.
     *
     * @param x The x coordinate.
     * @param y The y coordinate.
     *
     * @return true if it succeeds, false if it fails.
     */
    bool addValue(int x, int y)
    {
        return graphLine.addValue(x, y);
    }

    /**
     * @fn bool Graph::deleteValue(int x)
     *
     * @brief Deletes the value for the given x.
     *
     * @param x The x coordinate.
     *
     * @return true if it succeeds, false if it fails.
     */
    bool deleteValue(int x)
    {
        return graphLine.deleteValue(x);
    }

    /**
     * @fn void Graph::clear()
     *
     * @brief Clears the graph.
     *
     *        Clears the graph.
     */
    void clear()
    {
        graphLine.clearGraph();
    }

    /**
     * @fn void Graph::setRange(int left, int right, int top, int bottom);
     *
     * @brief Sets the range of the graph.
     *
     *        Sets the range of the graph.
     *
     * @param left   The value at the left of the graph area.
     * @param right  The value at the right of the graph area.
     * @param bottom The value at the bottom of the graph area.
     * @param top    The value at the top of the graph area.
     */
    void setRange(int left, int right, int bottom, int top);


    /**
     * @fn template <class T> void Graph::setLineWidth(T width)
     *
     * @brief Sets the width for this graph line in pixels.
     *
     *        Sets the width for this graph line in pixels.
     *
     * @note The graph line is invalidated.
     *
     * @tparam T Generic type parameter.
     * @param width The width of the line measured in pixels.
     */
    template <class T>
    void setLineWidth(T width)
    {
        graphLine.setLineWidth(width);
    }

    /**
     * @fn template <class T> T Graph::getLineWidth() const
     *
     * @brief Gets line width in pixels.
     *
     *        Gets line width in pixels.
     *
     * @tparam T Generic type parameter.
     *
     * @return The line width in pixels.
     */
    template <class T>
    T getLineWidth() const
    {
        return graphLine.getLineWidth<T>();
    }

    /**
     * @fn int Graph::getRangeLeft()
     *
     * @brief Gets the x value at the left of the graph area.
     *
     * @return The x value at the left of the graph area.
     */
    int getRangeLeft()
    {
        return graphLine.getRangeLeft();
    }

    /**
     * @fn int Graph::getRangeRight()
     *
     * @brief Gets the x value at the right of the graph area.
     *
     * @return The x value at the right of the graph area.
     */
    int getRangeRight()
    {
        return graphLine.getRangeRight();
    }

    /**
     * @fn int Graph::getRangeBottom()
     *
     * @brief Gets the y value at the bottom of the graph area.
     *
     * @return The y value at the bottom of the graph area.
     */
    int getRangeBottom()
    {
        return graphLine.getRangeBottom();
    }

    /**
     * @fn int Graph::getRangeTop()
     *
     * @brief Gets the y value at the top of the graph area.
     *
     * @return The y value at the top of the graph area.
     */
    int getRangeTop()
    {
        return graphLine.getRangeTop();
    }

    /**
     * @fn void Graph::setAlpha(uint8_t alpha);
     *
     * @brief Sets the alpha.
     *
     *        Sets the alpha.
     *
     * @param alpha The alpha.
     */
    void setAlpha(uint8_t alpha);

    /**
     * @fn uint8_t Graph::getAlpha();
     *
     * @brief Gets the alpha.
     *
     *        Gets the alpha.
     *
     * @return The alpha.
     */
    uint8_t getAlpha();

protected:
    static const int NUMBER_OF_POINTS = 50; ///< Max number of points in the graph

    GraphLine graphLine;           ///< The line of the graph

    GraphLine::GraphPoint graphBuffer[NUMBER_OF_POINTS]; ///< Memory for the graph points

    PainterRGB565 graphLinePainter;           ///< Painter for the line

    uint8_t myAlpha; ///< Alpha value for entire graph
};


#endif /* GRAPH_HPP */
