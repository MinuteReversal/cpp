/**
* ```shell
* g++ -std=c++20 -o main 16coroutine/main.cpp
* ./main
* ```
 */

#include <coroutine>
#include <iostream>

struct Task {
  struct promise_type {
    Task get_return_object() { return {}; }
    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
};

Task foo() {
  std::cout << "Hello Coroutine!" << std::endl;
  co_return;
}

int main() {
  foo();
  return 0;
}