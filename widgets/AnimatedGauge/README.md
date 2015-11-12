![example](screenshots/LiquidContainer.gif "This is what LiquidContainer widgets look like. Only silky smooth, of course. (I'm even worse at building animated GIFs than I am at programming. Thank goodness I do neither for a living.)")
#Purpose
Tired of plain old linear gauges? Then add a little pizzaz with a liquid container. Rather than showing your data statically, this widget sports a scrolling level image. Use it to soup up your interface with waves, dynamic gradients, or whatever strikes your fancy.

The liquid container uses two images, one for the container (which is static) and one for the liquid within (which is animated). The container image must have a transparent section. This serves as a viewport through which the liquid image is shown. The liquid image should be at least the size of the viewport and have matching left and right sides for smooth wrapping around when scrolling.

For demonstration purposes, the LiquidContainer contains a text displaying the current value numerically. Also, it supports level adjustment by clicking (top half to increase, bottom half to decrease, in user-specified increments). Feel free to change or disable as you see fit.

Caveat: The LiquidContainer represents my first forays into TouchGFX programming. As you can undoubtedly tell, my C++ coding skills are somewhat rusty. But hey, the code compiles and the widget seems to work, so I thought I might as well share it. Enjoy!

#TouchGFX Version
This widget was created and tested using TouchGFX version 4.4.1.

#Functional description
The initialization function for the LiquidContainer widget takes more parameters than you can shake a stick at. But don't despair. Once your widget is up and running, it is completely maintenance free, providing you with years of uninterrupted, carefree animation. Play around with the values in the examples below to see how they affects the behavior. Soon, you will be deploying LiquidContainer widgets like a pro.

	// show beaker
	ClickListener<LiquidContainer> beaker;
	beaker.init(BITMAP_BEAKER_ID, BITMAP_ACID_ID, 20, 250, 3, T_MILLILITERS, 39, 138, 150, 50, 0, 250, 90, 5);
	beaker.setXY(20, 20); 
	add(beaker);

	// show test tube
	ClickListener<LiquidContainer> tube;
	tube.init(BITMAP_TESTTUBE_ID, BITMAP_WATER_ID, 25, 194, -1, T_PERCENT, 5, 159, 50, 50, 0, 100, 75, 1);
	tube.setXY(282, 55);
	add(tube);

	// show oil gauge
	ClickListener<LiquidContainer> gauge;
	gauge.init(BITMAP_GAUGE_ID, BITMAP_OIL_ID, 35, 135, 1, T_DEGREES, 0, 60, 200, 50, 90, 150, 105, 5);
	gauge.setXY(375, 60);
	add(gauge);
