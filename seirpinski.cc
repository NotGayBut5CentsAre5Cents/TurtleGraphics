#include "turtle.cc"
#include <cmath>
#include <sstream>
#include <fstream>

Turtle* turtle = nullptr;
void sierpinski_half(double, double, int);
void sierpinski(double, double, int);
/*

Адаптация на Logo кода от тук, за Sierpinski
-> https://ipfs.io/ipfs/QmXoypizjW3WknFiJnKLwHCnL72vedxjQkDDP1mXWo6uco/wiki/Sierpinski_curve.html
*/
int main(int argc, char* argv[])
{
    istringstream ss(argv[2]);
    int depth;
    if(!(ss >> depth)) {
        cout << "invalid depth";
    }
    std::string format = argv[1];
    std::ofstream out(argv[4]);
    if(format == "eps")
        turtle = new PSTurtle(2048, 2048, out);
    else if(format == "svg")
        turtle = new SVGTurtle(2048, 2048, out);

    assert(turtle != nullptr);
    double big_lenght = turtle->get_height() / pow(2, depth + 1);
    double small_length = big_lenght / 2;
    turtle->setup()
    .pendown()
    .set_heading(45)
    .set_pos(Point(small_length, 1));
    sierpinski(big_lenght, small_length, depth);
}


void sierpinksi_half (double big_length, double small_length, int depth) {
    if(depth == 0) {
        turtle->forward(small_length);
        return;
    }
    sierpinksi_half(big_length, small_length, depth - 1);
    turtle->right(45).forward(big_length).right(45);
    sierpinksi_half(big_length, small_length, depth - 1);
    turtle->left(90).forward(small_length).left(90);
    sierpinksi_half(big_length, small_length, depth - 1);
    turtle->right(45).forward(big_length).right(45);
    sierpinksi_half(big_length, small_length, depth - 1);
}
void sierpinski(double big_length, double small_length, int depth) {
    sierpinksi_half(big_length, small_length, depth);
    turtle->left(90).forward(small_length).left(90);
    sierpinksi_half(big_length, small_length, depth);
    turtle->left(90).forward(small_length).left(90);
}

