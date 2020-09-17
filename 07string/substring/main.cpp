#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const **argv)
{
  string s = "hello world";
  cout << s.substr(1, 3) << endl;
  return 0;
}