#include <iostream>
#include <stack>

using namespace std;

int main(int argc, char const **argv)
{
  stack<int> *s = new stack<int>();

  for (size_t i = 0; i < 5; i++)
  {
    s->push(i);
  }

  while (!s->empty())
  {
    cout << s->top() << endl;
    s->pop();
  }
  delete s;
  return 0;
}