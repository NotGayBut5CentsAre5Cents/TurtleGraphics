#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif


#include "polygondrawer.hh"
#include <cmath>


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
