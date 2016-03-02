#ifndef FILE_INPUT_HPP
#define FILE_INPUT_HPP

#include <touchgfx/hal/types.hpp>

namespace touchgfx
{ 
namespace fileinput 
{
    //type used for file handles
    typedef void* FileHdl;

    /**
     * @fn int readFile(FileHdl hdl, uint8_t* const buffer, uint32_t length);
     *
     * @brief Read data from a file
     *
     *        Read data from an open file.
     *
     * @param hdl    Handle to file.
     * @param buffer The buffer to data into.
     * @param length The number of bytes to read.
     *
     * @return Actual number of bytes read.
     */
    int readFile(FileHdl hdl, uint8_t* const buffer, uint32_t length);

    /**
     * @fn void seekFile(FileHdl hdl, uint32_t offset);
     *
     * @brief Seek in a file
     *
     *        Seek in an open file. The offset is from the beginning
     *        of the file.
     *
     * @param hdl    Handle to file.
     * @param offset The offset to seek to.
     */
    void seekFile(FileHdl hdl, uint32_t offset);
}
}

#endif
