#include <gui/common/Graph.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <math.h>

Graph::Graph() :
    myAlpha(255)
{
}

Graph::~Graph()
{
}

void Graph::setup(int newWidth, int newHeight, uint16_t lineColor)
{
    setWidth(newWidth);
    setHeight(newHeight);
    
    graphLinePainter.setColor(lineColor);

    graphLine.setPosition(0, 0, getWidth(), getHeight());
    graphLine.setPainter(graphLinePainter);
    graphLine.setBuffer(graphBuffer, NUMBER_OF_POINTS);
    graphLine.setLineWidth(2);
    graphLine.setRange(-6, 400, 400, 0);

    add(graphLine);
}

void Graph::setRange(int left, int right, int bottom, int top) 
{ 
    graphLine.setRange(left, right, bottom, top); 
}

void Graph::setAlpha(uint8_t alpha)
{
    myAlpha = alpha;
    graphLine.setAlpha(myAlpha);
    invalidate();
}

uint8_t Graph::getAlpha()
{
    return myAlpha;
}
