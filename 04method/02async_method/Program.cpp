/// https://en.cppreference.com/w/cpp/thread/async
#include <exception>
#include <future>
#include <iostream>
#include <string>
#include <system_error>
#include <thread>

using namespace std;

future<void> fn1() {
  promise<void> p;
  cout << "fn1" << endl;
  p.set_value();
  return p.get_future();
}

future<void> fn2(int x) {
  promise<void> p;
  cout << "fn" << x << endl;
  p.set_value();
  return p.get_future();
}

future<int> fn3() {
  promise<int> p;
  cout << "fn3" << endl;
  p.set_value(3);
  return p.get_future();
}

future<int> fn4(int x) {
  promise<int> p;
  cout << "fn" << x << endl;
  p.set_value(x);
  return p.get_future();
}

future<void> fn5() {
  promise<void> p;
  cout << "fn5" << endl;
  // https://cplusplus.com/reference/future/promise/set_exception/
  p.set_exception(
      make_exception_ptr(invalid_argument("hello world")));
  return p.get_future();
}

int main(int argc, char **argv) {
  fn1().wait();
  fn2(2).wait();
  int r1 = fn3().get();
  int r2 = fn4(4).get();
  try {
    fn5().get();
  } catch (const std::invalid_argument &e) {
    cout << e.what() << endl;
  }
  cout << r1 << endl;
  cout << r2 << endl;
  return 0;
}
