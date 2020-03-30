#include <iostream>
#include <string>
using namespace std;
int main(){
	cout <<"input your name" <<endl;
	string name = "";
	getline(cin,name);
	cout << "good evening " << name <<endl;
	return 0;
}
