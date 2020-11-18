#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const **argv)
{
  string s1 = "hello world";
  string sub = s1.substr(6, 5);
  cout << sub << endl;

  return 0;
}