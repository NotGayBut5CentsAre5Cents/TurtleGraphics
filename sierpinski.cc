//--------------------------------------------
// NAME: Telerik Arsov
// CLASS: XIb
// NUMBER: 26
// PROBLEM: Sierpinski
// FILE NAME: sierpinski.cc
// FILE PURPOSE: To draw sierpinski curves from different orders
// mainly from 1 to 7 order. 
//---------------------------------------------
#include "turtle.cc"
#include "svgturtle.cc"
#include <cmath>
#include <sstream>
#include <fstream>

Turtle* turtle = NULL;
/*
The code is adapted from this program for Logo
-> https://ipfs.io/ipfs/QmXoypizjW3WknFiJnKLwHCnL72vedxjQkDDP1mXWo6uco/wiki/Sierpinski_curve.html
*/
class Sierpinski {
    Turtle* turtle_;
public:
    Sierpinski(Turtle* turtle);
    ~Sierpinski();
    void sierpinski_half(double big_length, double small_length, int depth);
    void draw(double big_length, double small_length, int depth);
};

Sierpinski::Sierpinski(Turtle* turtle) :
    turtle_(turtle) {}
Sierpinski::~Sierpinski() {
    delete turtle_;    
}


//--------------------------------------------
// FUNCTION: sierpinski_half
// Draw half segments which combined always present half the whole curve 
// PARAMETERS:
// big_length == pretty self-explanatory
// small_length == ^^^^^^ (the length of the side of those little pointy thingys)
// depth is the same as the order
//----------------------------------------------
void Sierpinski::sierpinski_half(double big_length, double small_length, int depth) {
    assert(depth >= 0);
    if(depth == 0) {
        turtle->forward(small_length);
        return;
    }
    sierpinski_half(big_length, small_length, depth - 1);
    turtle->right(45).forward(big_length).right(45);
    
    sierpinski_half(big_length, small_length, depth - 1);
    turtle->left(90).forward(small_length).left(90);
    
    sierpinski_half(big_length, small_length, depth - 1);
    turtle->right(45).forward(big_length).right(45);
    
    sierpinski_half(big_length, small_length, depth - 1);
}
//--------------------------------------------
// FUNCTION: draw
// draws the curve by drawing 2 half ofthe whole thing
// PARAMETERS:
// big_length == pretty self-explanatory
// small_length == ^^^^^^ (the length of the side of those little pointy thingys)
// depth is the same as the order
//----------------------------------------------
void Sierpinski::draw(double big_length, double small_length, int depth) {
    assert(depth >= 0);
    if(!turtle_->is_setup())
        turtle_->setup();
    if(!turtle_->is_pendown())
        turtle_->pendown();

    sierpinski_half(big_length, small_length, depth);
    turtle->left(90).forward(small_length).left(90);
    
    sierpinski_half(big_length, small_length, depth);
    turtle->left(90).forward(small_length).left(90);
}

int main(int argc, char* argv[])
{
    istringstream ss(argv[2]);
    int depth;
    if(!(ss >> depth)) {
        cout << "invalid depth";
    }
    std::string format = argv[1];
    if(format == "eps")
        turtle = new PSTurtle(2048, 2048, cout);
    else if(format == "svg")
        turtle = new SVGTurtle(2048, 2048, cout);

    assert(turtle != NULL);
    double big_lenght = turtle->get_height() / pow(2, depth + 1);
    double small_length = big_lenght / 2;
    turtle->setup()
    .pendown()
    .set_heading(45)
    .pensize(0.5)
    .set_pos(Point(small_length, 1));
    Sierpinski sierpinski(turtle);
    sierpinski.draw(big_lenght, small_length, depth);
}

