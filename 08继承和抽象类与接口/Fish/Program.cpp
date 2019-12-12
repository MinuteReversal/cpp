#include <iostream>

using namespace std;

class Fish
{
  public:
    void virtual Eat()
    {
        cout << "Fish like eat kelp" << endl;
    }
};

class FlyingFish : public Fish
{
    void Eat()
    {
        cout << "FlyingFish like eat shrimp" << endl;
    }
};

class RedFlyingFish : public FlyingFish
{
};

class Shark : public Fish
{
    void Eat() override
    {
        cout << "Shark like eat meat" << endl;
    }
};

class WhiteShark : public Shark
{
};

int main(int argc, char *argv)
{
    Fish *fish = new Fish();
    fish->Eat();
    delete fish;
    fish = new FlyingFish();
    fish->Eat();
    delete fish;
    fish = new Shark();
    fish->Eat();
    delete fish;
    fish = new RedFlyingFish();
    fish->Eat();
    delete fish;
    fish = new WhiteShark();
    fish->Eat();
    delete fish;
    return 0;
}