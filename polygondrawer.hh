//--------------------------------------------
// NAME: Telerik Arsov
// CLASS: XIb
// NUMBER: 26
// PROBLEM: Turtle drawing polygons and stars?
// FILE NAME: polygondrawer.hh
// FILE PURPOSE: header file for the class polygondrawer
//---------------------------------------------

#ifndef POLYGON_DRAWER_HH_
#define POLYGON_DRAWER_HH_

#include "turtle.hh"

class PolygonDrawer {
    Turtle* turtle_;

    double internal_angle_;
    double external_angle_;
    double width_;
    double height_;

    int num_of_sides_;

    void calculate_internal_angle();
    void calculate_external_angle();
public:

    PolygonDrawer& set_num_of_sides(int num_of_sides);
    PolygonDrawer();
    PolygonDrawer(int num_of_sides, Turtle* turtle);
    ~PolygonDrawer();

    int get_num_of_sides() const {
        return num_of_sides_;
    }

    double get_internal_angle() const {
        return internal_angle_;
    }

    double get_external_angle() const {
        return external_angle_;
    }


    PolygonDrawer& draw_grid(int depth);///êîëêî äà å ïîäðîáåí ãðèäà /// num_of_sides çà çâåçäàòà ñå èìà ïðåäâèä íà
    PolygonDrawer& draw_star(Point center, int length);              /// ñòðàíèòå íà regular polygona âïèñàí â íåÿ
    PolygonDrawer& draw_polygon(Point center, int length); ///regular polygon
};

#endif