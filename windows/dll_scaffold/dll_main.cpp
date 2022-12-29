#include <basetsd.h>
#include <iostream>
#include <string.h>
#include <string>
#include <windows.h>
#define DllExport __declspec(dllexport)

BOOL WINAPI DllMain(HINSTANCE hinstDLL, // handle to DLL module
					DWORD fdwReason,    // reason for calling function
					LPVOID lpvReserved) // reserved
{
	// Perform actions based on the reason for calling.
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			// Initialize once for each new process.
			// Return FALSE to fail DLL load.
			break;

		case DLL_THREAD_ATTACH:
			// Do thread-specific initialization.
			break;

		case DLL_THREAD_DETACH:
			// Do thread-specific cleanup.
			break;

		case DLL_PROCESS_DETACH:

			if (lpvReserved != nullptr) {
				break; // do not do cleanup if process termination scenario
			}

			// Perform any necessary cleanup.
			break;
	}
	return TRUE; // Successful DLL_PROCESS_ATTACH.
}

extern "C" DllExport void fn1() { std::cout << "call fn1" << std::endl; }

extern "C" DllExport void fn2(int x) {
	std::cout << "call fn2 " << x << std::endl;
}

extern "C" DllExport int fn3() {
	std::cout << "call fn3" << std::endl;
	return 3;
}

extern "C" DllExport int fn4(int x) {
	std::cout << "call fn4" << std::endl;
	return x;
}

extern "C" DllExport void CreateColorImage(uint8_t* data, char* color,
										   const int width = 256,
										   const int height = 256) {
	std::cout << color << std::endl;
	/// |0|1|2|3|4|5|6|7|
	/// |r|g|b|a|r|g|b|a|
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			auto index = x + y * width;
			*(data + index * 4 + 0) =
				strcmp(color, "red") == 0 ? 255 : 0; // red
			*(data + index * 4 + 1) =
				strcmp(color, "green") == 0 ? 255 : 0; // green
			*(data + index * 4 + 2) =
				strcmp(color, "blue") == 0 ? 255 : 0; // blue
			*(data + index * 4 + 3) = 255;            // alpha
		}
	}
}

// https://learn.microsoft.com/en-us/cpp/cpp/using-dllimport-and-dllexport-in-cpp-classes?view=msvc-170
class DllExport Car {
	public:
		std::string color = "red";
		void go() {
			std::cout << this->color << " car are going." << std::endl;
		}
		static void repair(Car car) {
			std::cout << car.color << " car are in repair factory" << std::endl;
		}
};

extern "C" DllExport Car* createCar() { return new Car(); }

struct DllExport Coordinate {
		double latitude;
		double longitude;
};

struct DllExport Place {
		char* name;
		struct Coordinate coordinate;
};

extern "C" struct Coordinate createCoordinate(double latitude,
											  double longitude) {
	return {latitude, longitude};
}

extern "C" struct Place createPlace(char* name, double latitude,
									double longitude) {
	return {name, {longitude, latitude}};
}