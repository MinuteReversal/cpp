#include <iostream>

using namespace std;

class Car
{
  private:
    char *Color;

  protected:
    char *Brand;

  public:
    Car()
    {
    }
    Car(char *brand)
    {
        this->Brand = brand;
    }
    void SetColor(char *Color)
    {
        this->Color = Color;
    }
    char *GetColor()
    {
        return this->Color;
    }
    void Run()
    {
        cout << "a " << this->Brand << " brand " << this->Color << " color "
             << " Car are going." << endl;
    }
    ~Car()
    {
        cout << "The car" << this->Brand << " are releaseed" << endl;
    }
};

int main(int argc, char *argv)
{
    //reference type
    Car *car = new Car("BMW");
    car->SetColor("red");
    car->Run();
    delete car; //hand release

    //value type
    Car car2("WL");
    car2.SetColor("White");
    car2.Run();

    return 0;
}