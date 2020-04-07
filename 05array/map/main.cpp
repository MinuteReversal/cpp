#include <iostream>
#include <map>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
  map<string, int> *m = new map<string, int>({{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}});
  (*m)["age"] = 35;
  cout << (*m)["age"] << endl;
  cout << (*m)["b"] << endl;
  delete m;
  return 0;
}