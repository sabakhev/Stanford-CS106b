/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include "simpio.h"
#include "gtypes.h"
#include "gmath.h"

using namespace std;
// Used consntants
const double SINE = sinDegrees(60); 

// This is a recursive void type function that draws zero order triangles at specified points.
void drawTriangle (double length, int order, double x, double y, GWindow & gw){
	if(order == 0){
		GPoint point1(x, y);
		GPoint point2 = gw.drawPolarLine(point1, length, 60);
		GPoint point3 = gw.drawPolarLine(point2, length, 300);
		gw.drawPolarLine(point3, length, 180);
	}
	if(order > 0){
		drawTriangle(length / 2, order - 1, x, y, gw);
		drawTriangle(length/2, order - 1, x + length / 2, y, gw);
		drawTriangle(length / 2, order - 1, x + length / 4, y - ((length/2)*SINE), gw);
	}
}

int main() {
	double length = getReal("Triangle edge size: ");
	int order = getInteger("Fractal order of Sierpinski triangle: ");
	GWindow gw(1400.0, 800.0);
	double x = gw.getWidth()/2 - length/2;
	double y = gw.getHeight()/2 + (SINE * (length)/2);
	pause(200); // Without this, program had trouble to draw the first line
	drawTriangle(length, order, x, y, gw);
    return 0;
}
