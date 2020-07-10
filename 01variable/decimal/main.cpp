#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const **argv)
{
  const string str = "not have decimal type";
  throw str;
  return 0;
}