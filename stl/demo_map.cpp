#include <iostream>
#include <map>
#include <string>

using namespace std;

int main(int argc, char const **argv)
{
  map<string, string> *m = new map<string, string>();
  (*m)["hello"] = "world";

  cout << (*m)["hello"] << endl;

  delete m;
  return 0;
}