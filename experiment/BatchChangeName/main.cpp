/*! *****************************************************************************
fileName    : main.cpp 
author      : 114233763@qq.com
date        : 2020-06-18 10:28:06
version     : v1
description : 改名文件并移动到文件夹中3.0x 2.0x
***************************************************************************** */
#include <iostream>
#include <string>
#include <dirent.h>
#include <regex>
#include <sys/stat.h>

using namespace std;

/**
 * 检查路径是否存在 
 */
bool isPathExist(const std::string &s)
{
  struct stat buffer;
  return (stat(s.c_str(), &buffer) == 0);
}

int main(int argc, char const **argv)
{
  string path = "";
  if (argc > 1)
  {
    path = argv[1];
  }
  else
  {
    cout << "请输入要转换的路径(回车结束输入)" << endl;
    cin >> path;
  }

  if (path == "")
  {
    return 0;
  }

  //不是以\结尾
  if (path[path.length() - 1] != '\\')
  {
    path.append("\\"); //加一个
  }

  DIR *dir = opendir(path.c_str());

  struct dirent *entry;

  const regex reg = regex("(@\\dx)", regex_constants::ECMAScript);

  //文件逐个拿出来
  while ((entry = readdir(dir)) != NULL)
  {
    //跳过上级文件夹..
    if (regex_search(entry->d_name, regex("^[.]+")))
      continue;
    //跳过没有尺寸的文件
    if (!regex_search(entry->d_name, reg))
      continue;

    //去掉尺寸的名字
    auto name = regex_replace(entry->d_name, reg, "");

    //匹配到的名字
    cmatch cm;
    regex_search(entry->d_name, cm, regex("(\\d)"));
    const string folderName = string(cm[0].first, cm[0].second);

    //文件夹路径
    const string folderPath = path + "\\" + folderName + ".0x" + "\\";
    if (!isPathExist(folderPath))
    {
      mkdir(folderPath.c_str());
    }

    auto fromName = path + (entry->d_name);
    auto toName = folderPath + name;
    cout << fromName << " => " << toName << endl;
    rename(fromName.c_str(), toName.c_str());
  }
  delete entry;
  closedir(dir);
  cout << "complete" << endl;
  return 0;
}