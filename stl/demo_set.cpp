#include <iostream>
#include <set>

using namespace std;

int main(int argc, char const **argv)
{
  set<int> *s = new set<int>();
  s->insert(10);
  s->insert(20);
  s->insert(30);
  while (!s->empty())
  {
    cout << *s->begin() << endl;
    s->erase(s->begin());
  }

  delete s;
  return 0;
}