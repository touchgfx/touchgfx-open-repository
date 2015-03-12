Purpose
========

![Empty](0_percent.png "0%") ![In Progress](example.png "Example") ![Full](100_percent.png "100%")

The purpose of the CircularProgress widget is to provide an application developer with means to present a progress indicator with nice gradient, circular graphics. For example purposes, the CircularProgress class also accepts touch events to set the progress value.

TouchGFX Version
=================

This widget was created and tested using TouchGFX version 4.2

Functional description
======================

The setup code is embedded in the constructor where the dimentsion of the circle arc is setup to match the bitmap used as background for the circular progress bar.

Ideas for new functionality could be the addition of move animation with a new value is set. This would require the registration of a tick evenet handler, an easing equation, and selecting how many steps to use for the transition.