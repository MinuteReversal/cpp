//https://www.programming-techniques.com/2011/11/index-operator-which-is-normally-used.html
#include <iostream>

using namespace std;
const int MAX = 10;
class sArray
{

private:
  int arr[MAX];

public:
  int &operator[](int index)
  {

    if (index < 0 || index >= MAX)
    {
      cout << "\n Array index out of bound\n";
      exit(1);
    }
    return arr[index];
  }
};

int main(int argc, char **argv)
{
  sArray sa;
  for (int i = 0; i < MAX; i++)
  {
    sa[i] = i + 2;
  }
  for (int i = 0; i < MAX; i++)
  {

    cout << sa[i] << "\t";
  }
  sa[MAX] = 55; //array index out of bound

  cout << sa[MAX + 1]; //array index out of bound
  return 0;
}