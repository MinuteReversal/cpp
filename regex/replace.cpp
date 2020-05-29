#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char const **argv)
{
  auto reg = regex("hello", regex_constants::ECMAScript);
  auto result = regex_replace("hello world!!!!", reg, "");
  cout << result << endl;
  return 0;
}