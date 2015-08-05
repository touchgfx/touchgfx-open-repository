Purpose
========

![example](screenshots/qr.bmp "Example - a 16x16 QR code scaled to a size of 64x64 pixels")

The purpose of the QRCodeWidget is to provide an example of a simple custom widget. 
The QRCodeWidget displays the QR code data supplied by the QRCode object.

The QRCodeWidget is kept very simple and only handles displaying of data. The implementation is optimized mainly for clarity of reading and not for performance.

In order to use the QRCodeWidget for displaying real QR codes one should supply a real QR code. Libraries for creating QR codes can be found online.

TouchGFX Version
=================

This widget was created and tested using TouchGFX version 4.3.0

Functional description
======================

The QRCodeWidget is set up and added to the view. A QRCode is supplied. A code example is below:

    qrCode.setXY(0,0);
    qrCode.setQRCode(&code);
    qrCode.setScale(4);
    add(qrCode);
