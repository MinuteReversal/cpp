ren https://blogs.msdn.microsoft.com/vcblog/2016/10/24/building-your-c-application-with-visual-studio-code/
@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvars64.bat"    
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:a.exe
cl.exe %compilerflags% Program.cpp /link %linkerflags%