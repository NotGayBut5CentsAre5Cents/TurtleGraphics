//--------------------------------------------
// NAME: Telerik Arsov
// CLASS: XIb
// NUMBER: 26
// PROBLEM: Turtle drawing polygons and stars?
// FILE NAME: polygondrawer.cc
// FILE PURPOSE: A class that can draw regular polygons
// grids with diffirent level of detail and stars
//---------------------------------------------

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


//--------------------------------------------
// FUNCTION: set_num_of_sides
// Used like a setup fuction for the class
// PARAMETERS:
// num_of_sides = the number of sides for the regular polygon
// or a star(NOTE: the sides for the star mean the sides of the polygon inscrebed into the star)
// example: 6 sides means a hexagon for the polygon and hexagram for the star
//----------------------------------------------
PolygonDrawer& PolygonDrawer::set_num_of_sides(int num_of_sides) {
    assert(num_of_sides > 2);
    num_of_sides_ = num_of_sides;
    calculate_internal_angle();
    calculate_external_angle();
    width_ = turtle_->get_width();
    height_ = turtle_->get_height();
    return *this;
}

//--------------------------------------------
// FUNCTION: draw_polygon
// Draws a regular polygon with the given parameters
// PARAMETERS:
// center = the cordinates of the center of the polygon
// length = the length of one side of the polygon
// the apothem is used to find the distance from the center to a side of the polygon  
//----------------------------------------------
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

//--------------------------------------------
// FUNCTION: draw_star
// Draws a polygram (star)
// PARAMETERS:
// center = the cordinates of the center of the polygram
// length = the length of one side of the polygon that is inscribed inside the polygram
// the apothem is used to find the distance from the center to a side of the polygon
// inscribed inside the polygram  
//----------------------------------------------
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

//--------------------------------------------
// FUNCTION: draw_grid
// Draws a grid
// PARAMETERS:
// the depth means how many segments will the grid have
// e.g. depth = 1  there will be 2 lines deviding the canvas 
// into 4 equal segments
// depth = 2 there will be 6 lines deviding the canvas 
// into 16 equal segments
//----------------------------------------------

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
    ///then for the y axis
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
