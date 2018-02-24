//--------------------------------------------
// NAME: Telerik Arsov
// CLASS: XIb
// NUMBER: 26
// PROBLEM: Red Hexagon
// FILE NAME: hexagon.cc
// FILE PURPOSE: Draw a red hexagon and a simple grid
// this solution uses my custom made class polygon drawer
// that draws either a star, grid or a regular polygon
//---------------------------------------------
#include "turtle.cc"
#include "svgturtle.cc"
#include "polygondrawer.cc"
#include <sstream>
#include <fstream>

Turtle* turtle = NULL;

int main(int argc, char* argv[]) {

    std::string format = argv[1];

    if(format == "eps")
        turtle = new PSTurtle(1000, 1000, cout);
    else if(format == "svg")
        turtle = new SVGTurtle(1000, 1000, cout);

    assert(turtle != NULL);
    turtle->setup()
    .pencolor(Color(1))
    .pensize(2.0);
    PolygonDrawer drawer(6, turtle);
    drawer.draw_grid(1).draw_polygon(Point(500, 500), 400);
}
