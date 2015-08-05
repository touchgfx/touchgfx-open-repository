#ifndef QR_CODE_HPP
#define QR_CODE_HPP

#include <touchgfx/hal/Types.hpp>

/**
* @class QRCode
* 
* @brief An interface for getting the value of a qr code at a particular x,y position
*
*        This implementation generates random values for the different x,y coordinates.
*        A real qr code will probably save the qr code values in an array like structure and report these instead.
*/
class QRCode
{
public:
    /**
     * @fn bool QRCode::at(uint16_t x, uint16_t y);
     *
     * @brief Get the qr code value at a particular coordinate
     *
     * @param x x coordinate
     * @param y y coordinate
     *
     * @return The value of the qr code at the supplied coordinate
     */
    bool at(uint16_t x, uint16_t y) const;

    /**
     * @fn uint16_t QRCode::getWidth();
     *
     * @brief Get the width of the qr code
     *
     * @return The width
     */
    uint16_t getWidth() const;

    /**
     * @fn uint16_t QRCode::getHeight();
     *
     * @brief Get the height of the qr code
     *
     * @return The height
     */
    uint16_t getHeight() const;
};

#endif