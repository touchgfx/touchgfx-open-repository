###############################################################################
#
# @brief     This file is part of the TouchGFX 4.4.1 evaluation distribution.
#
# @author    Draupner Graphics A/S <http://www.touchgfx.com>
#
###############################################################################
#
# @section Copyright
# 
# This file is free software and is provided for example purposes. You may 
# use, copy, and modify within the terms and conditions of the license
# agreement. 
#
# This is licensed software for evaluation use, any use must strictly comply
# with the evaluation license agreement provided with delivery of the
# TouchGFX software.
#
# The evaluation license agreement can be seen on www.touchgfx.com
#
# @section Disclaimer
#
# DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Draupner Graphics A/S has
# no obligation to support this software. Draupner Graphics A/S is providing
# the software "AS IS", with no express or implied warranties of any kind,
# including, but not limited to, any implied warranties of merchantability
# or fitness for any particular purpose or warranties against infringement
# of any proprietary rights of a third party.
#
# Draupner Graphics A/S can not be held liable for any consequential,
# incidental, or special damages, or any other relief, or for any claim by
# any third party, arising from your use of this software.
#
###############################################################################
# Relative location of the TouchGFX framework from root of application
touchgfx_path := ../../../touchgfx

# Optional additional compiler flags
user_cflags :=

# Settings for image converter output format
alpha_dither := yes
opaque_image_format := RGB565
non_opaque_image_format := RGB565

# Settings for image converter screen orientation (empty string = default value, -rotate90 rotates the image 90 degrees)
screen_orientation :=

#Settings for Hardware accelerated text rendering on ST32F4 devices. Must correspond to value of bitsPerPixel for font to have any effect.
#If A4 blitcap is enabled for target specific HAL the fontconverter must generate compliant data format, otherwise resulting in a DMA Controller Configuration Error.
text_data_format :=
