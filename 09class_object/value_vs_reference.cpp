#include <iostream>
#include <string>

using namespace std;

class Car
{
public:
	string color = "";
	Car(string color)
	{
		this->color = color;
	}
	void drive() const
	{
		cout << this->color << " car drove away." << endl;
	}
};

int main()
{
	const int i = 0;
	//值类型
	auto car1 = Car("red");
	auto car2 = car1;
	car2.color = "yellow";
	car1.drive();
	car2.drive();

	cout << "========================" << endl;
	//引用类型
	const auto cara = new Car("blue");
	const auto carb = cara;
	carb->color = "purple";
	cara->drive();
	carb->drive();
	delete cara;
	return 0;
}
