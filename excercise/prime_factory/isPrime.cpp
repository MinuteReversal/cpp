#include <iostream>
#include <string>

using namespace std;

bool isPrime(int n)
{
  if (n <= 3)
  {
    return n > 1;
  }
  for (int i = 2; i < n; i++)
  {
    if (n % i == 0)
    {
      return false;
    }
  }
  return true;
}

int main(int argc, char const **argv)
{
  int input = 3;
  string isWord = isPrime(input) ? "" : " not";
  cout << input << " is" << isWord << " prime." << endl;
  return 0;
}