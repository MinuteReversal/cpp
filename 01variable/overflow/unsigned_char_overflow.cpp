#include <iostream>

using namespace std;

int main(int argc, char const **argv)
{
	unsigned char c = 255;
	cout << (int)c << endl;
	c = c + 1;
	cout << (int)c << endl;
	return 0;
}