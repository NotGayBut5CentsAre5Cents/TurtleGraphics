#include "svgturtle.hh"
#include <cmath>

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
