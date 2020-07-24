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

int main(int argc, char **argv)
{
    Fish fish = Fish();
    FlyingFish flyingFish = FlyingFish();
    Shark shark = Shark();
    RedFlyingFish redFlyingFish = RedFlyingFish();
    WhiteShark whiteShark = WhiteShark();

    Fish &rfish = fish;
    fish.Eat();
    fish = flyingFish;
    fish.Eat();
    fish = Shark();
    fish.Eat();
    fish = redFlyingFish;
    fish.Eat();
    fish = whiteShark;
    fish.Eat();
    return 0;
}