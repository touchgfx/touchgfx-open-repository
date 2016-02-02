#include <touchgfx/hal/Types.hpp>
#include <touchgfx/Bitmap.hpp>
#include <gui/common/fileinput.hpp>
using namespace touchgfx;

namespace touchgfx
{ 
class JPEGFileLoader
{
public:
    /**
     * @fn static void getJPEGDimensions(fileinput::FileHdl fileHandle, uint16_t& width, uint16_t& height);
     *
     * @brief Reads width and height of JPEG image in a file
     *
     * Reads width and height of JPEG image in a file. The file must
     * be open. The function will call fileinput::seekFile and
     * fileinput::readFile.
     */
    static void getJPEGDimensions(fileinput::FileHdl fileHandle, uint16_t& width, uint16_t& height);
    /**
     * @fn static void readJPEGFile(Bitmap bitmap, fileinput::FileHdl fileHandle, uint8_t* lineBuffer);
     *
     * @brief Reads JPEG image from a file to a dynamic bitmap.
     *
     * Reads JPEG image from a file to a dynamic bitmap. The file must
     * be open. The function will call fileinput::seekFile and
     * fileinput::readFile.
     */
    static void readJPEGFile(Bitmap bitmap, fileinput::FileHdl fileHandle, uint8_t* lineBuffer);
};

}
