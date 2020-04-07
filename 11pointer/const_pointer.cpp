//https://docs.microsoft.com/en-us/cpp/cpp/const-and-volatile-pointers?view=vs-2019
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  int gorp = 16;
  int chips = 12;
  int *const p_snack = &gorp;
  *p_snack = 20;
  return 0;
}