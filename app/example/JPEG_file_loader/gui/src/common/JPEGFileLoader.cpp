#include <gui/common/JPEGFileLoader.hpp>
#include <touchgfx/Color.hpp>

#include "jinclude.h"
#include "jpeglib.h"

namespace
{
    struct RGB
    {
        uint8_t R;
        uint8_t G;
        uint8_t B;
    };
}

void JPEGFileLoader::getJPEGDimensions(fileinput::FileHdl fileHandle, uint16_t& width, uint16_t& height)
{
    fileinput::seekFile(fileHandle, 0);
    
    /* This struct contains the JPEG decompression parameters */
    struct jpeg_decompress_struct cinfo;
    /* This struct represents a JPEG error handler */
    struct jpeg_error_mgr jerr;
    
    /* Step 1: allocate and initialize JPEG decompression object */
    cinfo.err = jpeg_std_error(&jerr);
    
    /* Initialize the JPEG decompression object */  
    jpeg_create_decompress(&cinfo);
    
    // setup to read from file
    jpeg_stdio_src(&cinfo, (FILE*)fileHandle);
    
    /* Step 3: read image parameters with jpeg_read_header() */
    jpeg_read_header(&cinfo, TRUE);

    /* Copy dimensions */
    width = cinfo.image_width;
    height = cinfo.image_height;

    /* Step 7: Release JPEG decompression object */
    jpeg_destroy_decompress(&cinfo);
}

void JPEGFileLoader::readJPEGFile(Bitmap bitmap, fileinput::FileHdl fileHandle, uint8_t* lineBuffer)
{
    /* This struct contains the JPEG decompression parameters */
    struct jpeg_decompress_struct cinfo;
    /* This struct represents a JPEG error handler */
    struct jpeg_error_mgr jerr;
    
    JSAMPROW lines[2] = {lineBuffer, 0}; /* Output row buffer */

    /* Step 0: Seek to start of file */
    fileinput::seekFile(fileHandle, 0);
    
    /* Step 1: allocate and initialize JPEG decompression object */
    cinfo.err = jpeg_std_error(&jerr);
    
    /* Initialize the JPEG decompression object */  
    jpeg_create_decompress(&cinfo);
    
    // setup to read from file
    jpeg_stdio_src(&cinfo, fileHandle);
    
    /* Step 3: read image parameters with jpeg_read_header() */
    jpeg_read_header(&cinfo, TRUE);
    
    /* Step 4: set parameters for decompression */
    cinfo.dct_method = JDCT_FLOAT;
    
    /* Step 5: start decompressor */
    jpeg_start_decompress(&cinfo);
    
    const uint32_t bitmap_width = bitmap.getWidth();
    const uint32_t bitmap_height = bitmap.getHeight();
    const uint32_t output_width = MIN(bitmap_width, cinfo.image_width);
    const uint32_t output_height = MIN(bitmap_height, cinfo.output_height);

    const Bitmap::BitmapFormat format = bitmap.getFormat();
    uint8_t* const  buffer8  = Bitmap::dynamicBitmapGetAddress(bitmap.getId());
    uint16_t* const buffer16 = (uint16_t*)buffer8;

    switch (format)
    {
    case Bitmap::RGB565:
    {
        uint16_t *lineptr = buffer16;
        while (cinfo.output_scanline < output_height)
        {
            (void) jpeg_read_scanlines(&cinfo, lines, 1);
            RGB* RGB_matrix = (RGB*)lineBuffer;
            //loop row
            for(uint32_t counter = 0; counter < output_width; counter++)
            {
                const uint16_t pix = ((RGB_matrix[counter].R&0xF8) << 8) | ((RGB_matrix[counter].G&0xFC) << 3) | ((RGB_matrix[counter].B&0xF7)>>3);
                *(lineptr + counter) = pix;
            }  
            lineptr += bitmap_width; //move to next line
        }
        break;
    }
    case Bitmap::RGB888:
    {
        uint8_t* lineptr = buffer8;
        while (cinfo.output_scanline < output_height)
        {
            (void) jpeg_read_scanlines(&cinfo, lines, 1);
            RGB* RGB_matrix = (RGB*)lineBuffer;
            //loop row
            for(uint32_t counter = 0; counter < output_width; counter++)
            {
                *lineptr++ = RGB_matrix[counter].B;
                *lineptr++ = RGB_matrix[counter].G;
                *lineptr++ = RGB_matrix[counter].R;
            }
            //advance to next row in bitmap
            if (output_width < bitmap_width)
            {
                lineptr += (bitmap_width - output_width)*3;
            }
        }
        break;
    }
    default:
        assert(!"Unsupported bitmap format in JPEGFileLoader!");
    }

    /* Step 6: Finish decompression */
    jpeg_finish_decompress(&cinfo);
    
    /* Step 7: Release JPEG decompression object */
    jpeg_destroy_decompress(&cinfo);
}
