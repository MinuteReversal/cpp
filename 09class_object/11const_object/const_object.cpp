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

int Date::getMonth() const
{
  return month; // Doesn't modify anything
}
void Date::setMonth(int mn)
{
  month = mn; // Modifies data member
}

int main()
{
  Date MyDate(7, 4, 1998);
  const Date BirthDate(1, 18, 1953);
  MyDate.setMonth(4);    // Okay
  BirthDate.getMonth();  // Okay
  BirthDate.setMonth(4); // C2662 Error
}