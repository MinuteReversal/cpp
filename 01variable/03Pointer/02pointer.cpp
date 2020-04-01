#include <iostream>

using namespace std;

int main()
{
	int coin = 1;
	int* pcoin = &coin;
	cout << "value of coin = " << coin  
	     << " address of coin = " << &coin << endl;
	cout << "value of pcoin = " << *pcoin
	     << " address of pcoin = " << pcoin << endl;
	return 0;
}