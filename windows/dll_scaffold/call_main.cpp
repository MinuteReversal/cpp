#include <iostream>
#include <windows.h>

#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "dll_main.lib")

typedef void (*FN1)();
typedef void (*FN2)(int);
typedef int (*FN3)();
typedef int (*FN4)(int);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					 LPSTR pCmdLine, int nCmdShow) {

	HMODULE hLibModule = LoadLibrary("dll_main.dll");

	if (hLibModule == NULL) {
		MessageBox(NULL, "沒有找到DLL", "標題", MB_OK);
		return FALSE;
	}

	FN1 fn1 = (FN1)GetProcAddress(hLibModule, "fn1");
	FN2 fn2 = (FN2)GetProcAddress(hLibModule, "fn2");
	FN3 fn3 = (FN3)GetProcAddress(hLibModule, "fn3");
	FN4 fn4 = (FN4)GetProcAddress(hLibModule, "fn4");

	fn1();
	fn2(2);
	std::cout << fn3() << std::endl;
	std::cout << fn4(4) << std::endl;

	FreeLibrary(hLibModule);

	return EXIT_SUCCESS;
}