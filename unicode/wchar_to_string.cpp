//https://www.cnblogs.com/chouxianyu/p/11249810.html
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const **argv)
{
  auto txt = L"你好世界";
  wstring wx = txt;

  string str = string(wx.begin(), wx.end());
  cout << str << endl;
  return 0;
}