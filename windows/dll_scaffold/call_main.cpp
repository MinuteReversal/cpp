#include <iostream>
#include <stdint.h>
#include <string>
#include <windows.h>

#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "user32.lib")

class Car {
	public:
		std::string Color;
		void go();
};

typedef void (*FN1)();
typedef void (*FN2)(int);
typedef int (*FN3)();
typedef int (*FN4)(int);
typedef void (*CreateColorImage)(uint8_t*, char*, int, int);
typedef Car* (*FNCreateCar)();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					 LPSTR pCmdLine, int nCmdShow) {

	HMODULE hLibModule = LoadLibrary("dll_main.dll");

	if (hLibModule == NULL) {
		MessageBox(NULL, "沒有找到DLL", "标题", MB_OK);
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

	CreateColorImage fnCreateColorImage =
		(CreateColorImage)GetProcAddress(hLibModule, "CreateColorImage");

	uint8_t list[256 * 256 * 4];
	fnCreateColorImage(list, (char*)"red", 256, 256);
	std::cout << "color:" << (int)list[0] << std::endl;

	FNCreateCar createCar =
		(FNCreateCar)GetProcAddress(hLibModule, "createCar");
	Car* car = createCar();
	car->go();

	delete car;

	FreeLibrary(hLibModule);

	return EXIT_SUCCESS;
}