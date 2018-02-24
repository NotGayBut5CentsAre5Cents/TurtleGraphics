#include "turtle.cc"
#include "svgturtle.cc"
#include "polygondrawer.cc"
#include <sstream>
#include <fstream>

Turtle* turtle = nullptr;

int main(int argc, char* argv[]) {

    std::string format = argv[1];
    std::ofstream out(argv[3]);

    if(format == "eps")
        turtle = new PSTurtle(1000, 1000, out);
    else if(format == "svg")
        turtle = new SVGTurtle(1000, 1000, out);

    assert(turtle != nullptr);
    turtle->pencolor(Color(0, 1));
    .pensize(2.0);
    PolygonDrawer drawer(6, turtle1);
    drawer.draw_grid(1).draw_polygon(Point(500, 500), 400);
}
