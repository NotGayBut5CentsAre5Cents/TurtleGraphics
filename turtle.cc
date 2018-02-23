/*
 * turtle.cc
 *
 *  Created on: Oct 21, 2017
 *      Author: lubo
 */

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#include "turtle.hh"
#include <cmath>

using namespace std;

Point Point::polar(double angle, double distance) {
	double radians = angle * M_PI / 180.0;

	double x = distance * cos(radians);
	double y = distance * sin(radians);
	return Point(x, y);
}

Point Point::cartesian(double x, double y) {
	return Point(x, y);
}

Point operator+(const Point& p1, const Point& p2) {
	Point result = p1;
	result += p2;
	return result;
}

Point operator-(const Point& p1, const Point& p2) {
	Point result = p1;
	result -= p2;
	return result;
}

ostream& operator<<(ostream& out, const Point& p) {
	out << p.get_x() << ' ' << p.get_y();
	return out;
}

ostream& operator<<(ostream& out, const Color& c) {
	out << c.red() << " "
		<< c.green() << " "
		<< c.blue();
	return out;
}

Turtle::Turtle(double width, double height) :
		width_(width), height_(height),
		pos_(width_ / 2.0, height_ / 2.0),
		heading_(0.0),
		is_pendown_(false),
		pen_size_(1.0),
		setup_(false) {

}

Turtle::~Turtle() {

}

Turtle& Turtle::forward(double distance) {
	assert(setup_);
	assert(distance >= 0);

	Point tr = Point::polar(heading_, distance);
	Point next_pos = pos_ + tr;
	return moveto(next_pos);
}

Turtle& Turtle::backward(double distance) {
	assert(setup_);
	assert(distance >= 0);

	Point tr = Point::polar(heading_ + 180.0, distance);
	Point next_pos = pos_ + tr;
	return moveto(next_pos);
}

Turtle& Turtle::right(double angle) {
	assert(setup_);
	assert(angle >= 0);

	heading_ -= angle;
	return *this;
}

Turtle& Turtle::left(double angle) {
	assert(setup_);
	assert(angle >= 0);

	heading_ += angle;
	return *this;
}

Turtle& Turtle::set_pos(const Point& p) {
	assert(setup_);
	assert(inside(p));

	pos_ = p;
	return *this;
}

Turtle& Turtle::set_heading(double angle) {
	assert(setup_);

	heading_ = angle;
	return *this;
}

Turtle& Turtle::penup() {
	assert(setup_);

	is_pendown_ = false;
	return *this;
}

Turtle& Turtle::pendown() {
	assert(setup_);

	is_pendown_ = true;
	return *this;
}

Turtle& Turtle::pencolor(const Color& c) {
	assert(is_setup());

	color_ = c;
	return *this;
}

Turtle& Turtle::pensize(double width) {
	assert(is_setup());

	pen_size_ = width;
	return *this;
}

Turtle& Turtle::dot(double size) {
// do nothing
	return *this;
}

PSTurtle::PSTurtle(double width, double height, ostream& out) :
        Turtle(width, height), out_(out) {
}

PSTurtle::~PSTurtle() {
	out_ << "stroke" << endl;
	out_ << "showpage" << endl;
	out_ << "%%EOF" << endl;
}

Turtle& PSTurtle::setup() {
	out_ << "%!PS-Adobe-3.0 EPSF-3.0" << endl;
	out_ << "%%Creator: turtle" << endl;
	out_ << "%%DocumentData: Clean7Bit" << endl;
	out_ << "%%Origin: 0 0" << std::endl;
	out_ << "%%BoundingBox: 0 0 "
			<< get_width() << " " << get_height() << endl;
	out_ << "%%LanguageLevel: 2" << endl;
	out_ << "%%Pages: 1" << endl;
	out_ << "%%Page: 1 1" << endl;

	out_ << "newpath" << endl;
	out_ << get_pos() << " moveto" << endl;
	Turtle::setup();

	return *this;
}

Turtle& PSTurtle::moveto(const Point& next_pos) {
	assert(is_setup());
	assert(inside(next_pos));

	out_ << next_pos << ' ';
	if (is_pendown()) {
		out_ << "lineto" << std::endl;
	} else {
		out_ << "moveto" << std::endl;
	}
	Turtle::moveto(next_pos);
	return *this;
}

Turtle& PSTurtle::pencolor(const Color& c) {
	assert(is_setup());

	Turtle::pencolor(c);
	out_ << "stroke" << endl;
	out_ << "newpath" << endl;
	out_ << get_pos() << " moveto" << endl;
	out_ << c << " setrgbcolor" << endl;
	return *this;
}

Turtle& PSTurtle::pensize(double width) {
	assert(is_setup());

	Turtle::pensize(width);
	out_ << "stroke" << endl;
	out_ << "newpath" << endl;
	out_ << get_pos() << " moveto" << endl;
	out_ << width << " setlinewidth" << endl;
	return *this;
}


Turtle& PSTurtle::dot(double size) {
	out_ << "gsave" << endl;
	out_ << "newpath" << endl;
	out_ << get_pos() << " " << size << " "
		 << "0 360 arc closepath fill" << endl;
	out_ << "grestore" << endl;
	return *this;
}

Turtle& PSTurtle::set_pos(const Point& p) {
	out_ << p << " moveto" << endl;
	return Turtle::set_pos(p);
}

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

PolygonDrawer::PolygonDrawer() :
        turtle_(new SVGTurtle(1024, 1024, cout))
        {
            set_num_of_sides(3);
        }
PolygonDrawer::PolygonDrawer(int num_of_sides, Turtle* turtle) :
        turtle_(turtle)
        {
            set_num_of_sides(num_of_sides);
        }
PolygonDrawer::~PolygonDrawer() {
	delete turtle_;
}
void PolygonDrawer::calculate_internal_angle() {
    assert(num_of_sides_ > 2);
    internal_angle_ = 180.0 * (num_of_sides_ - 2) / num_of_sides_;
}

void PolygonDrawer::calculate_external_angle() {
    assert(internal_angle_ >= 0);
    external_angle_ = 180 - internal_angle_;
}

PolygonDrawer& PolygonDrawer::set_num_of_sides(int num_of_sides) {
    assert(num_of_sides > 2);
    num_of_sides_ = num_of_sides;
    calculate_internal_angle();
    calculate_external_angle();
    width_ = turtle_->get_width();
    height_ = turtle_->get_height();
    return *this;
}

PolygonDrawer& PolygonDrawer::draw_polygon(Point center, int length) {
    if(!turtle_->is_setup())
        turtle_->setup();
    if(turtle_->is_pendown())
        turtle_->penup();

    double apothem = abs(length / (2 * tan(180 / num_of_sides_ * M_PI / 180)));

    turtle_->set_heading(90)
    .set_pos(center)
    .forward(apothem)
    .pendown()
    .left(90).forward(length / 2);

    for(int i = 0; i < num_of_sides_ - 1; i++) {
        turtle_->left(external_angle_)
        .forward(length);
    }

    turtle_->left(external_angle_).forward(length / 2)
    .penup();
    return *this;
}



PolygonDrawer& PolygonDrawer::draw_star(Point center, int length) {
    if(!turtle_->is_setup())
        turtle_->setup();
    if(turtle_->is_pendown())
        turtle_->penup();

    double apothem = abs(length / (2 * tan(180 / num_of_sides_ * M_PI / 180)));

    turtle_->set_heading(90)
    .set_pos(center)
    .forward(apothem)
    .left(90).forward(length / 2)
    .pendown();

    for(int i = 0; i < num_of_sides_ + 1; i++) {
        turtle_->forward(length).left(external_angle_ * 2)
        .forward(length).right(external_angle_);
    }
    turtle_->penup();
    return *this;
}

PolygonDrawer& PolygonDrawer::draw_grid(int depth) {
    assert(depth >= 1);
    if(!turtle_->is_setup())
        turtle_->setup();
    if(!turtle_->is_pendown())
        turtle_->pendown();
    Color original_color = turtle_->get_color();
    double original_pensize = turtle_->get_pensize();
    turtle_->pencolor(Color(0, 0, 0))
    .pensize(0.5);

    int twoPowD = pow(2, depth);
    double width_delimiter  = (double)width_ / twoPowD; /// distance between each line on the x axis for the grid
    double height_delimiter  = (double)height_ / twoPowD; /// distance between each line on the y axis for the grid
    ///drawing the lines on the x axis first
    turtle_->set_pos(Point(0, 0))
    .set_heading(90);
    for(int i = 0; i < twoPowD - 1; i++) {
        turtle_->set_pos(Point(width_delimiter * (i + 1), 0))
        .forward(height_);
    }
    turtle_->set_pos(Point(0, 0))
    .set_heading(0);
    for(int i = 0; i < twoPowD - 1; i++) {
        turtle_->set_pos(Point(0, height_delimiter * (i + 1)))
        .forward(width_);
    }

    turtle_->pencolor(original_color)
    .pensize(original_pensize)
    .penup();
    return *this;
}
