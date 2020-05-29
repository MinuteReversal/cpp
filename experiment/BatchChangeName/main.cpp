#include <iostream>
#include <string>
#include <dirent.h>
#include <regex>

using namespace std;

int main(int argc, char const **argv)
{
  string path = "C:\\Users\\Administrator\\Desktop\\iconv1\\iconv1\\3x\\";
  DIR *dir = opendir(path.c_str());

  struct dirent *entry;

  auto reg = regex("(@\\dx)", regex_constants::ECMAScript);

  while ((entry = readdir(dir)) != NULL)
  {
    if (regex_search(entry->d_name, regex("^[.]+")))
      continue;

    auto name = regex_replace(entry->d_name, reg, "");
    cout << entry->d_name << "=>"
         << name << endl;

    auto fromName = path + (entry->d_name);
    auto toName = path + name;
    rename(fromName.c_str(), toName.c_str());
  }

  closedir(dir);
  return 0;
}