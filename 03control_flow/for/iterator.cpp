//https://docs.microsoft.com/en-us/cpp/standard-library/iterators?view=msvc-160#:~:text=An%20iterator%20is%20an%20object%20that%20can%20iterate,type%20of%20container%20the%20elements%20are%20stored%20in.
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

  for (auto it = l.begin(); it != l.end(); it++)
  {
    cout << *it;
  }

  return 0;
}