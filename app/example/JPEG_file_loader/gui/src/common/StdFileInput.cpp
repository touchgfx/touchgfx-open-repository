#include <gui/common/FileInput.hpp>

//Implementation of fileinput using standard libc functions

#include <stdio.h>
namespace touchgfx
{
namespace fileinput
{
    int readFile(fileinput::FileHdl hdl, uint8_t* const buffer, uint32_t length)
    {
        uint32_t r = fread(buffer, 1, length, (FILE*)hdl);
        return (int)r;
    }

    void seekFile(FileHdl hdl, uint32_t offset)
    {
        fseek((FILE*)hdl, offset, SEEK_SET);
    }
}
}

