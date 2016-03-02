#include <gui/common/FileInput.hpp>
#include "jinclude.h"

//link LibJPEG file read operation to touchgfx::fileinput function.
extern "C"
{
    size_t jpeg_read_file (FILE *file, uint8_t *buf, uint32_t sizeofbuf)
    {
        return touchgfx::fileinput::readFile(file, buf, sizeofbuf);
    }
}

