#include <iostream>
#include <dirent.h>

using namespace std;

int main(int argc, char const **argv)
{
  DIR *dir = opendir("C:\\");

  struct dirent *ent;
  while ((ent = readdir(dir)) != NULL)
  {
    cout << ent->d_name << endl;
  }

  closedir(dir);
  return 0;
}