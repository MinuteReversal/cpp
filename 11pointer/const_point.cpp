//https://docs.microsoft.com/en-us/cpp/cpp/const-and-volatile-pointers?view=vs-2019
#include <iostream>

using namespace std;

class Date
{
public:
  Date(int mn, int dy, int yr);
  int getMonth() const;  // A read-only function
  void setMonth(int mn); // A write function; can't be const
private:
  int month;
};

Date::Date(int mn, int dy, int yr)
{
}
int Date::getMonth() const
{
  return month; // Doesn't modify anything
}
void Date::setMonth(int mn)
{
  month = mn; // Modifies data member
}

int main(int argc, char **argv)
{
  const Date *date = new Date(4, 6, 1985);
  date->setMonth(5);
  return 0;
}