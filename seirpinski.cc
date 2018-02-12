#include "turtle.cc"
#include <cmath>

SVGTurtle turtle = SVGTurtle(1000, 1000, cout);

int sierpinski_segment (double distance, int depth, double scale) {
    if(depth == 0) {
        turtle.forward(distance);
        return 0;
    }
    sierpinski_segment(distance, depth - 1);
    turtle.right(45).forward(distance / sqrt(2 + depth - 1)).right(45);
    sierpinski_segment(distance, depth - 1);
    turtle.left(90).forward(distance).left(90);
    sierpinski_segment(distance, depth - 1);
    turtle.right(45).forward(distance / sqrt(2 + depth - 1)).right(45);
    sierpinski_segment(distance, depth - 1);
}
void sierpinski(double distance, int depth) {
    double scale = turtle.get_height() * turtle.get_width() / (distance * distance) / 10;
    sierpinski_segment(distance, depth, );
    turtle.left(90).forward(distance).left(90);
    sierpinski_segment(distance, depth);
    turtle.left(90).forward(distance).left(90);
}

int main()
{
    double distance;
    int depth;
    cin >> distance >> depth;
    turtle.setup();
    turtle.pendown();
    turtle.set_heading(45);
    turtle.set_pos(Point(distance, distance));
    sierpinski(distance, depth);
}
