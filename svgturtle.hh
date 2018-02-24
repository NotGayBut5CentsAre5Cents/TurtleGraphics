//--------------------------------------------
// NAME: Telerik Arsov
// CLASS: XIb
// NUMBER: 26
// PROBLEM: Svg turtle implementation
// FILE NAME: svgturtle.cc
// FILE PURPOSE: the header file for the svg turtle class
//---------------------------------------------
#ifndef SVG_TURTLE_HH_
#define SVG_TURTLE_HH_

#include "turtle.hh"
#include <iostream>
#include <cassert>
#include <string.h>

class SVGTurtle: public Turtle {
    std::ostream& out_;

public:
    SVGTurtle(double width, double height, std::ostream& out);
    virtual ~SVGTurtle();
    virtual Turtle& setup();
    virtual Turtle& moveto(const Point& p);
};


#endif