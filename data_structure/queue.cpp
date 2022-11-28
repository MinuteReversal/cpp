#include <iostream>
#include <ostream>
#include <queue>

using namespace std;

int main(int argc, char const **argv) {
  queue<int> *q = new queue<int>();
  for (size_t i = 0; i < 10; i++) {
    q->push(i);
  }
  cout << q->size() << endl;

  for (size_t i = 0; i < 10; i++) {
    cout << q->front() << endl;
    q->pop();
  }
  cout << q->size() << endl;

  return 0;
}