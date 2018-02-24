#ifndef SVG_TURTLE_HH_
#define SVG_TURTLE_HH_

#include "turtle.hh"

class SVGTurtle: public Turtle {
    std::ostream& out_;

public:
    SVGTurtle(double width, double height, std::ostream& out);
    virtual ~SVGTurtle();
    virtual Turtle& setup();
    virtual Turtle& moveto(const Point& p);
};


#endif