#include <iostream>

using namespace std;

class Cat
{
  public:
    void Walk()
    {
        cout << "cat is walking" << endl;
    }
};

int main(int argc, char *argv)
{
    void (Cat::*pCat)();
    pCat = &Cat::Walk;

    Cat *cat = new Cat();
    (cat->*pCat)();
    delete cat;

    Cat bigCat;
    (bigCat.*pCat)();
    return 0;
}