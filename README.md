# <img src="http://touchgfx.com/static/touchgfx_logo_open_rep_small.png" width="500" height="135">

TouchGFX is framework, written in C++, that allows you to create modern, graphical user interfaces on limited-resource embedded systems and allows smartphone-like look and feel on hardware platforms an order of magnitude less powerful than smartphones, e.g. ARM Cortex M3/M4 48-204 MHz.

This repository, the *TouchGFX Open Repository*, contains numerous examples of, and ideas for, graphical components such as widgets, containers and mixins that are not part of the core framework. They can be used as a source of inspiration for your applications free of charge; The components are all generalized to some extend but probably needs some sort of fine tuning to match your specific needs. PLease not that none of the components are guaranteed to be maintained across new versions of TouchGFX. 

This repository would greatly benefit from TouchGFX developers around the world sharing some of their work. Having a solid community that shares complex ideas for TouchGFX widgets is something that can help reduce development time greatly. If you would like to contribute to this repository you can fork and follow the guide below. When done, open a pull request to your branch. Each contribution should conform to the following standards:

 1. Create a suitable folder inside widgets/ for your contribution
 2. Supply at least source- and headerfiles, example code welcome but not necessary.
 2. Supply one or more screenshot of the widget in action. Graphical components that make up the widget are also welcome for clarity.
 3. Create a *README.md* containing, in markdown:
   - Purpose of the widget - Any screenshots you may have could be shown here.
   - Version(s) of TouchGFX you've tested your code on
   - Functional description of the widget and it's configuration. Code can be verbatim formatted in .md by indenting with 4 spaces.

On the TouchGFX website you can request a full evaluation version of the framework as well as order commercial licenses. Read more about the concept of widgets, containers and mixins in  in the TouchGFX [documentation](http://touchgfx.com/documentation/html/index.html).

# Table of Components

In the following table you can see the name, associated TouchGFX version, and preview of each of the TouchGFX graphical components in this repository. 

The associated TouchGFX version is the version that the component has been tested on. Components will most likely also work on later versions of TouchGFX. 

<table style="width:100%">
  <tr>
    <td>LinearGauge <br>TouchGFX 4.1.1<br><img src="widgets/LinearGauge/LinearGaugeThumbnail.png" height="100"></td>
    <td>ExtendedZoomAnimationImage <br>TouchGFX 4.1.1<br> </td> 
    <td>Carousel <br>TouchGFX 4.1.1<br><img src="widgets/Carousel/screenshots/carouselThumbnail.bmp" height="100"></td>
  </tr>
  <tr>
    <td>DotIndicator <br>TouchGFX 4.1.1<br><img src="widgets/DotIndicator/screenshots/img00.bmp" height="100"></td>
    <td>SwipeContainer <br>TouchGFX 4.1.1<br><img src="widgets/SwipeContainer/screenshots/img01.bmp" height="100"></td> 
    <td>Gauge <br>TouchGFX 4.2<br><img src="widgets/Gauge/GaugePressure.png" height="100"></td>
  </tr>
  <tr>
    <td>WheelSelector <br>TouchGFX 4.2<br><img src="widgets/WheelSelector/days_fade_in.png" height="100"></td>
    <td>CircularProgress <br>TouchGFX 4.2<br><img src="widgets/CircularProgress/example.png" height="100"> </td> 
    <td></td>
  </tr>
</table>
 
# Links

* [Website] (http://touchgfx.com)
* [Documentation] (http://touchgfx.com/documentation/html/index.html)

# Videos

* [TouchGFX Demo on STM32F429 Evaluation Board 4.3"](http://www.youtube.com/watch?v=QcKX_Pc6ldU)
* [TouchGFX Demo on STM32F429 Discovery Board 2.4"](http://www.youtube.com/watch?v=j-fgE1hOlbo)
* [TouchGFX Demo on Embedded Artists LPC4088 Display Module 4.3"](https://www.youtube.com/watch?v=g_GjiUXrIc8)
* [TouchGFX Demo on Embedded Artists LPC4357 DevKit 4.3"](http://www.youtube.com/watch?v=OzRpGLfjh1c)
* [TouchGFX Demo on TouchGFX Demo Board NXP 4357 4.3"](http://www.youtube.com/watch?v=dvSK0oXQqfA)

# Screenshots

<img align="left" src="http://touchgfx.com/static/touchgfx_demos.png">

# Licensing

All widgets, containers and mixins found in this repository are free software for both commercial and non-commericial use. You may use, copy, redistribute and modify the files as needed. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY.

# Ownership

The TouchGFX framework is a Draupner Graphics product.

<img align="left" width="150" height="118" src="http://touchgfx.com/static/draupner_vlogo.png">
