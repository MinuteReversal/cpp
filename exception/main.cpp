#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

int main(int argc, char const **argv)
{
  try
  {
    throw invalid_argument("abc");
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}