# cpp

cpp program

[http://www.mingw.org/](http://www.mingw.org/)
[google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)  
[MSYS2](https://www.msys2.org/)  
[mingw-w64](http://mingw-w64.org/doku.php)  
[clang](https://releases.llvm.org/download.html)  
[blog](https://zh4ui.net/post/2019-01-08-clang-on-windows/)
[https://docs.microsoft.com/en-us/cpp/?view=vs-2019](https://docs.microsoft.com/en-us/cpp/?view=vs-2019)  
[g++ download](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z/download)


`tasks.json`
```json
{
  "version": "2.0.0",
  "windows": {
    "options": {
      "shell": {
        "executable": "cmd.exe",
        "args": [
          "/C",
          // The path to VsDevCmd.bat depends on the version of Visual Studio you have installed.
          "\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/Tools/VsDevCmd.bat\"",
          "&&"
        ]
      }
    }
  },
  "tasks": [
    {
      "type": "shell",
      "label": "cl.exe build active file",
      "command": "cl.exe",
      "args": [
        "/Zi",
        "/EHsc",
        "/Fe:",
        "${fileDirname}\\${fileBasenameNoExtension}.exe",
        "${file}"
      ],
      "problemMatcher": ["$msCompile"],
      "group": {
        "kind": "build",
        "isDefault": true
      }
    }
  ]
}
```