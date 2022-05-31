#include <iostream>

using namespace std;

class TestMember
{
public:
	int fn() const
	{
		return 255;
	}
};

int main(int argc, char const **argv)
{
	const TestMember *t = new TestMember();
	const int c = t->fn();
	cout << c << endl;
	delete t;
	return 0;
}