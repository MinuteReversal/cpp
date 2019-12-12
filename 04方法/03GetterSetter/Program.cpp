#include <iostream>

using namespace std;

class Point
{
private:
    int _x;
    int _y;

public:
    Point(int x = 0, int y = 0)
    {
        _x = x;
        _y = y;
    }
    void setX(int value)
    {
        _x = value;
    }
    int getX()
    {
        return _x;
    }
    void setY(int value)
    {
        _y = value;
    }
    int getY()
    {
        return _y;
    }
    void print()
    {
        cout << "x:" << _x << ","
             << "y:" << _y << endl;
    }
};

int main(int argc, char *argv[], char *envp[])
{
    Point point = Point();
    point.print();
    point.setX(100);
    point.setY(100);
    point.print();
    return 0;
}