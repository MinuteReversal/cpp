#include <iostream>

using namespace std;

class Car {
private:
  char *color;

protected:
  char *brand;

public:
  Car() {}
  Car(char *brand) { this->brand = brand; }
  void SetColor(char *Color) { this->color = Color; }
  char *GetColor() { return this->color; }
  void Run() {
    cout << "a " << this->brand << " brand " << this->color << " color "
         << " Car are going." << endl;
  }
  ~Car() { cout << "The car" << this->brand << " are releaseed" << endl; }
};

int main(int argc, char **argv) {
  // reference type
  Car *car = new Car((char *)"BMW");
  car->SetColor(const_cast<char *>("red"));
  car->Run();
  delete car; // hand release

  // value type
  Car car2((char *)"WL");
  car2.SetColor((char *)"White");
  car2.Run();

  return 0;
}