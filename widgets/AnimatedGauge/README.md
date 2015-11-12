![example](screenshots/AnimatedGauge-large.gif "This is what LiquidContainer widgets look like. Only silky smooth, of course. (I'm even worse at building animated GIFs than I am at programming. Thank goodness I do neither for a living.)")
#Purpose
Tired of plain old linear gauges? Then soup up your interface with animated ones. Rather than showing your data statically, the AnimatedGauge widget sports a scrolling level image. Use it add a little pizazz to your interface with waves, dynamic gradients, or whatever strikes your fancy.

The animated gauge uses two images, one for the gauge housing (which is static) and one for the linear gauge inside (which is animated). The housing must have a transparent section. This serves as a viewport through which the scrolling  image is shown. The animated image should be at least the size of the viewport and have matching left and right sides for smooth wrapping around when scrolling.

For demonstration purposes, the AnimatedGauge contains a text displaying the current value numerically. Also, it supports level adjustment by clicking (top half to increase, bottom half to decrease, in user-specified increments). Feel free to change or disable as you see fit.

Caveat: The AnimatedGauge represents my first forays into TouchGFX programming. As you can tell, my C++ coding skills are somewhat rusty. But hey, the code compiles and the widget seems to work, so I thought I might as well share it. Enjoy!

#TouchGFX Version
This widget was created and tested using TouchGFX version 4.4.1.

#Functional description
The initialization function for the AnimatedGauge widget takes more parameters than you can shake a stick at. But don't despair. Once your widget is up and running, it is completely maintenance free, providing you with years of uninterrupted, carefree animation. Play around with the values in the examples below to see how they affect the behavior. Soon, you will be deploying AnimatedGauge widgets like a pro.

	// show beaker
	ClickListener<AnimatedGauge> beaker;
	beaker.init(BITMAP_BEAKER_ID, BITMAP_ACID_ID, 20, 250, 3, T_MILLILITERS, 39, 138, 150, 50, 0, 250, 90, 5);
	beaker.setXY(20, 20); 
	add(beaker);

	// show test tube
	ClickListener<AnimatedGauge> tube;
	tube.init(BITMAP_TESTTUBE_ID, BITMAP_WATER_ID, 25, 194, -1, T_PERCENT, 5, 159, 50, 50, 0, 100, 75, 1);
	tube.setXY(282, 55);
	add(tube);

	// show oil gauge
	ClickListener<AnimatedGauge> gauge;
	gauge.init(BITMAP_GAUGE_ID, BITMAP_OIL_ID, 35, 135, 1, T_DEGREES, 0, 60, 200, 50, 90, 150, 105, 5);
	gauge.setXY(375, 60);
	add(gauge);
