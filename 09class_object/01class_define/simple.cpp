#include <iostream>
#include <string>
using namespace std;

/**
* 汽车
*/
class Car
{
public:
  string brand; //品牌
  string color; //颜色
  void go()
  {
    cout << color << " " << brand << " are go" << endl;
  }
};
typedef Car *PCar;

int main(int argc, char const **argv)
{
  //值类型
  Car bmwCar;
  bmwCar.brand = "bmw";
  bmwCar.color = "red";
  bmwCar.go();

  PCar benzCar = new Car();
  benzCar->brand = "BMW";
  benzCar->color = "white";
  benzCar->go();
  delete benzCar;

  return 0;
}