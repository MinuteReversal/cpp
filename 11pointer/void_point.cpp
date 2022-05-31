#include <iostream>

using namespace std;

int main(int argc, char const **argv)
{
	void *p;
	p = malloc(sizeof (char));
	*((char *)p) = 65;
	cout << *(char *)p << endl;
	free(p);
	return 0;
}