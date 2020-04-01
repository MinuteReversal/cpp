#include <iostream>

using namespace std;

class Cat
{
  public:
    char *Name = "small cat";
    char *Color = "white";
    Cat()
    {
        this->Name = "cat";
    }
    Cat(char *color) : Cat()
    {
        this->Color = color;
    }
    void Run()
    {
        cout << "a " << this->Color << " " << this->Name << " are run." << endl;
    }
};

int main(int argc, char *argv)
{
    //reference
    Cat *cat = new Cat("yellow");
    cat->Run();
    delete cat;

    //value
    Cat cat2;
    cat2.Run();
    return 0;
}