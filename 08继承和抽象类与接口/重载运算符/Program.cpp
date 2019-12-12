#include <iostream>

using namespace std;

class Box
{
  public:
    int Width;
    int Height;
    Box(int w, int h) : Width(w), Height(h) {}
    Box operator+(Box a)
    {
        return Box(this->Width + a.Width, this->Height + a.Height);
    }
};

int main(int argc, char *argv)
{
    Box a(10, 20);
    Box b(30, 40);
    Box c = a + b;
    cout << "width:" << c.Width << "width:" << c.Height << endl;
    return 0;
}