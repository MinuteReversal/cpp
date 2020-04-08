#include <iostream>
#include <string>

using namespace std;

string concat1(const string &s1, const string &s2)
{
  return s1 + s2;
}

const string &concat2(string &s1, const string &s2)
{
  s1 = s1 + s2;
  return s1;
}

const string &concat3(const string &s1, const string &s2)
{
  string temp;
  temp = s1 + s2;
  return temp;
}

int main(int argc, char const **argv)
{
  string s1 = "hello";
  string s2 = "world";

  cout << concat1(s1, s2) << endl;
  cout << concat2(s1, s2) << endl;
  cout << concat1(s1, s2) << endl;
  return 0;
}