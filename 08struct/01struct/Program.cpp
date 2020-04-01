#include <iostream>

using namespace std;

struct Point
{
    int X;
    int Y;
};

int main(int argc, char **argv)
{
    Point p = {100, 200};
    Point p2 = Point(p); //copy constructor
    cout << "x:" << p.X << ",y:" << p.Y << endl;
    cout << "x:" << p2.X << ",y:" << p2.Y << endl;
    return 0;
}
