#include <iostream>
#include <string>
using namespace std;

class Car {
  public:
   string color="red";
   Car(string color){
     this->color=color;
   }
   void drive()
   {
     cout<<this->color<<" car drove away."<<endl;
   }
};

int main(){
  auto car1=Car("red");
  car1.drive();
  auto car2=car1;
  car2.color="yellow";
  car1.drive();
  car2.drive();
  
  auto cara=new Car("blue");
  cara->drive();
  auto carb=cara;
  carb->color="orange";
  cara->drive();
  carb->drive();
  delete cara;
  return 0;
}