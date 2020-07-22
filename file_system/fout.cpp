#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const **argv)
{
  ofstream fout;
  const char *fn = "C:\\ep-data.txt";
  fout.open(fn, ios_base::binary);
  if (!fout.is_open())
  {
    cout << "Can't open" << fn << ".Bye.\n";
    exit(EXIT_FAILURE);
  }
  const char *content = "hello world";
  fout << content << endl;
  fout.close();
  return 0;
}