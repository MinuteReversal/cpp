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

class BatchRename
{
private:
  string path;                                                     //路径
  const regex reg = regex("(@\\dx)", regex_constants::ECMAScript); //尺寸文件名
  /**
   * 检查路径是否存在 
   */
  bool isPathExist(const std::string &s)
  {
    struct stat buffer;
    return (stat(s.c_str(), &buffer) == 0);
  }
  /**
   * 路径检查 
   */
  void pathCheck(string p)
  {
    path = p;
    if (path == "")
    {
      cout << "请输入要转换的路径(回车结束输入)" << endl;
      cin >> path;
    }

    if (path == "")
    {
      throw new invalid_argument("path is empty string");
    }

    //不是以\结尾
    if (path[path.length() - 1] != '\\')
    {
      path.append("\\"); //加一个
    }
  }
  /**
   * 跳过文件
   */
  bool skipFile(string fileName)
  {
    //跳过上级文件夹..
    if (regex_search(fileName, regex("^[.]+")))
    {

      return true;
    }
    //跳过没有尺寸的文件
    else if (!regex_search(fileName, reg))
    {

      return true;
    }
    else
    {
      return false;
    }
  }
  /**
   * 缩放尺寸
   */
  string scaleSize(string fileName)
  {
    //匹配到的名字
    cmatch cm;
    regex_search(fileName.c_str(), cm, regex("(\\d)(?=x.)", regex_constants::ECMAScript));
    const string size = string(cm[0].first, cm[0].second);
    return size;
  }
  void createFolder(string path)
  {
    //文件夹路径
    if (!isPathExist(path))
    {
      mkdir(path.c_str());
    }
  }
  void moveFile(string from, string to)
  {
    cout << from << " => " << to << endl;
    rename(from.c_str(), to.c_str());
  }

public:
  /**
   * 批量修改名称
   */
  BatchRename() {}
  ~BatchRename() {}
  /**
   * 执行修改名字 
   */
  void execute(string p)
  {
    //路径检查
    pathCheck(p);

    DIR *dir = opendir(path.c_str());

    struct dirent *entry;

    //文件逐个拿出来
    while ((entry = readdir(dir)) != NULL)
    {
      if (skipFile(entry->d_name))
      {
        continue;
      }

      auto name = regex_replace(entry->d_name, reg, "");
      auto size = scaleSize(entry->d_name);
      auto folderPath = path + size + ".0x" + "\\";
      auto from = path + (entry->d_name);
      auto to = folderPath + name;

      //创建文件夹
      createFolder(folderPath);
      moveFile(from, to);
    }
    delete entry;
    closedir(dir);
    cout << "complete" << endl;
  }
};

int main(int argc, char const **argv)
{
  string path = "C:\\Users\\Administrator\\Desktop\\后补图标\\后补图标";
  // if (argc > 1)
  // {
  //   path = argv[1];
  // }

  BatchRename *br = new BatchRename();
  br->execute(path);
  delete br;

  return 0;
}