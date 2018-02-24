//--------------------------------------------
// NAME: Telerik Arsov
// CLASS: XIb
// NUMBER: 26
// PROBLEM: Svg turtle implementation
// FILE NAME: svgturtle.cc
// FILE PURPOSE: Implementation of the svg turtle class
// pretty self-explanatory
//---------------------------------------------

#include "svgturtle.hh"
#include <cmath>

using namespace std;

SVGTurtle::SVGTurtle(double width, double height, std::ostream& out) :
		Turtle(width, height), out_(out) {
}

Turtle& SVGTurtle::setup() {
    out_ << "<html>" << endl;
    out_ << "<body>" << endl;
    out_ << "<h1>SVG Turtle Graphics</h1>" << endl;
    out_ << "<svg width=\"" << get_width()
         << "\" height=\"" << get_height() << "\">" << endl;

    Turtle::setup();
}

SVGTurtle::~SVGTurtle() {
	out_ << "</svg>" << endl;
	out_ << "</body>" << endl;
	out_ << "</html>" << endl;
}

//--------------------------------------------
// FUNCTION: moveto
// moves the turtle to a point with given cordinates and leaves a trail
// if the pen is down
// PARAMETERS:
// next_pos = the next position for the turtle
//----------------------------------------------

Turtle& SVGTurtle::moveto(const Point& next_pos) {
    assert(is_setup());
    assert(inside(next_pos));

    if(is_pendown()) {
        out_ << "<line x1=\"" << get_pos().get_x() << "\" "
             << "y1=\"" << get_pos().get_y() << "\" "
             << "x2=\"" << next_pos.get_x() << "\" "
             << "y2=\"" << next_pos.get_y() << "\" " << endl;
        out_ << "\t style=\"stroke:rgb(" << get_color().red() * 255 << ","
             << get_color().green() * 255 << "," << get_color().blue() * 255 << ");"
             << "stroke-width:" << get_pensize() << "\" />" << endl;
    }else {
        out_ << "<path d=\"M" << next_pos << "\" />" <<endl;
    }


    Turtle::moveto(next_pos);
	return *this;
}
