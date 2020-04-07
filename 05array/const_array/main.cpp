#include <iostream>
#include <array>

using namespace std;

array<int, 4> arr = {1, 2, 3, 4};

void changeArray(const array<int, 4> a[])
{
  for (int item : *a)
  {
    item = 0;
  }
}

int main(int argc, char **argv)
{
  changeArray(&arr);

  for (int item : arr)
  {
    cout << item << endl;
  }
  return 0;
}