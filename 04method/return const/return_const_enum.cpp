#include <iostream>
#include "return_const_enum.h"

using namespace std;

ReturnConstEnum::ReturnConstEnum() {}
ReturnConstEnum::~ReturnConstEnum() {}
TestEnum ReturnConstEnum::Fn() const
{
	return TestEnum::A;
}

int main(int argc, char const **argv)
{
	ReturnConstEnum *rce = new ReturnConstEnum();
	const TestEnum e = rce->Fn();
	if (e == TestEnum::A)
	{
		cout << "equl A" << endl;
	}
	return 0;
}