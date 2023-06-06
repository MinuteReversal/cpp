#include <Windows.h>
#include <Shlwapi.h>
#include <iostream>

#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "Shlwapi.lib")

int main() {
	// create the output file
	const char* filename = "output.txt";
	HANDLE hFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
							  FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		std::cerr << "Failed to create file." << std::endl;
		return 1;
	}

	// create the stream object on the file
	IStream* pStream = NULL;
	HRESULT hr =
		SHCreateStreamOnFile(filename, STGM_WRITE | STGM_CREATE, &pStream);
	if (FAILED(hr)) {
		CloseHandle(hFile);
		std::cerr << "Failed to create stream." << std::endl;
		return 1;
	}

	// write some text to the stream
	const wchar_t* text = L"Hello, world!";
	ULONG bytesWritten = 0;
	hr = pStream->Write(text, wcslen(text) * sizeof(wchar_t), &bytesWritten);
	if (FAILED(hr) || bytesWritten != wcslen(text) * sizeof(wchar_t)) {
		pStream->Release();
		CloseHandle(hFile);
		std::cerr << "Failed to write text to stream." << std::endl;
		return 1;
	}

	// cleanup
	pStream->Release();
	CloseHandle(hFile);

	return 0;
}
