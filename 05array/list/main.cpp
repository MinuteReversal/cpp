#include <iostream>
#include <list>

using namespace std;

int main(int argc, char **argv)
{
  list<int> *l = new list<int>({1, 2, 3, 4, 5});

  l->push_back(6);
  l->push_back(7);

  for (int item : *l)
    cout << item << endl;
  delete l;
  return 0;
}