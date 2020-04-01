//https://stackoverflow.com/questions/19850991/operator-overloading-cannot-add-two-pointers
#include <iostream>

using namespace std;

class Box
{
  public:
    int Width;
    int Height;
    Box(int w, int h) : Width(w), Height(h) {}
    Box *operator+(Box *a)
    {
        return new Box(this->Width + a->Width, this->Height + a->Height);
    }
};

int main(int argc, char **argv)
{
    Box *a = new Box(10, 20);
    Box *b = new Box(30, 40);
    Box *c = a->operator+(b);
    cout << "width:" << c->Width << "width:" << c->Height << endl;
    return 0;
}