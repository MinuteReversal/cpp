#include <iostream>
#include <deque>
using namespace std;

int main(int argc, char const *argv[])
{
  deque<int> *d = new deque<int>();

  for (size_t i = 0; i < 10; i++)
  {
    d->push_back(i);
  }

  for (auto &&i : *d)
  {
    cout << i << endl;
  }

  delete d;

  return 0;
}
