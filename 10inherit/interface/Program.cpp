/*
*
* https://stackoverflow.com/questions/9756893/how-to-implement-interfaces-in-c
*/
#include <iostream>
#include <string>

using namespace std;

class IFly
{
  public:
    IFly() {}
    virtual ~IFly() {}
    virtual void Fly() = 0;
};

class ABird : public IFly
{
  public:
    virtual void Eat() = 0;
};

class Eagle : public ABird
{
  public:
    void Fly() override
    {
        cout << "eagle can fly" << endl;
    }
    void Eat() override
    {
        cout << "eagle like eat meat" << endl;
    }
};

class Penguin : public ABird
{
  private:
    string Name = "";

  public:
    void SetName(string name)
    {
        Name = name;
    }
    void Fly() override
    {
        cout << "Pengui cant fly" << endl;
    }
    void Eat() override
    {
        cout << "Pengui like eat fish" << endl;
    }
};

class APlane : public IFly
{
  public:
    virtual void Refuel() = 0;
};

class F22 : public APlane
{
  public:
    void Refuel() override
    {
        cout << "F22 can refuel oil" << endl;
    }
    void Fly() override
    {
        cout << "F22 fly very fast" << endl;
    }
};

class ToyPlane : public APlane
{
  public:
    void Refuel() override
    {
        cout << "ToyPlane cant not refuel" << endl;
    }
    void Fly() override
    {
        cout << "ToyPlane may be can fly" << endl;
    }
};

int main(int argc, char *argv[], char *envp[])
{
    IFly *ifly = new Eagle();
    ifly->Fly();
    delete ifly;
    ifly = new Penguin();
    ifly->Fly();
    delete ifly;
    ifly = new F22();
    ifly->Fly();
    delete ifly;
    ifly = new ToyPlane();
    ifly->Fly();
    delete ifly;

    ABird *bird = new Eagle();
    bird->Eat();
    bird->Fly();
    delete bird;
    bird = new Penguin();
    bird->Eat();
    bird->Fly();
    delete bird;

    APlane *aplane = new F22();
    aplane->Refuel();
    aplane->Fly();
    delete aplane;
    aplane = new ToyPlane();
    aplane->Refuel();
    aplane->Fly();
    delete aplane;

    return 0;
}