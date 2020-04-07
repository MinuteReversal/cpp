#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  const int i = 1;
  cout << i << endl;

  int const *x = &i;
  cout << *x << endl;
  return 0;
}