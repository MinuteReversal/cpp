#include <iostream>

using namespace std;

class Point
{
  public:
    int X = 0;
    int Y = 0;
    void Print()
    {
        cout << "x:" << X << "y:" << Y << endl;
    }
};

int main(int argc, char *argv[], char *envp[])
{
    Point *point1 = new Point();
    point1->X = 99;
    point1->Y = 66;
    point1->Print();

    Point point2((*point1));
    point2.Print();
    delete point1;
    return 0;
}