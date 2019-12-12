#include <iostream>

using namespace std;

class Point
{
  public:
    int X = 0;
    int Y = 0;

    Point(int x, int y) : X(x), Y(y)
    {
    }

    void Print()
    {
        cout << "x:" << X << "y:" << Y << endl;
    }
};

int main(int argc, char *argv)
{
    Point *point = new Point(10, 20);
    point->Print();
    delete point;

    return 0;
}