#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const **argv)
{
  vector<int> ratings(5);
  for (int i = 0; i < 5; i++)
  {
    ratings[i] = i;
  }
  vector<int>::iterator pd;
  for (pd = ratings.begin(); pd != ratings.end(); pd++)
  {
    cout << *pd << endl;
  }

  for (auto x : ratings)
  {
    cout << x << endl;
  }
  return 0;
}