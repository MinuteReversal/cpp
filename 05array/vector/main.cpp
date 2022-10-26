#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const **argv) {
  vector<int> list = {1, 2, 3, 4, 5};

  for (auto it : list) {
    cout << it << endl;
  }

  cout << list[0] << endl;

  vector<char> *list2 = new vector<char>({'a', 'b', 'c', 'd', 'e'});
  for (auto it = list2->begin(); it != list2->end(); it++) {
    cout << *it;
  }
  cout << endl;

  cout << list2->at(0) << endl;
  delete list2;
  return 0;
}