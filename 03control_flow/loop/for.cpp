#include <iostream>
#include <list>

using namespace std;

int main(int argc, char const **argv)
{
  list<int> l;
  for (size_t i = 0; i < 10; i++)
  {
    l.push_back(i);
  }

  for (auto &&i : l)
  {
    cout << i << ",";
  }

  return 0;
}