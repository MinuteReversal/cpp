#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char const **argv)
{
  ios state(nullptr);

  cout << "The answer in decimal is: " << 42 << endl;

  state.copyfmt(cout); // save current formatting
  cout << "In hex: 0x" // now load up a bunch of formatting modifiers
       << hex
       << uppercase
       << setw(8)
       << setfill('0')
       << 42 // the actual value we wanted to print out
       << endl;
  cout.copyfmt(state);
  return 0;
}