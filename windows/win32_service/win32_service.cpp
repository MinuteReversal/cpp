#include <Windows.h>

char* GetExeFullPath() {
	char* path = new char[MAX_PATH];
	memset(path, 0, MAX_PATH);

	if (GetModuleFileName(NULL, path, MAX_PATH) != 0) {
		return NULL;
	}
	return path;
}

bool TestStartService() {
	SC_HANDLE hScm = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (hScm == NULL) {
		return false;
	}
	SC_HANDLE hService = CreateService(
		hScm, "MyService", "MyService", SERVICE_ALL_ACCESS,
		SERVICE_WIN32_OWN_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,
		GetExeFullPath(), NULL, NULL, "", NULL, "");
	if (hService == NULL) {
		return false;
	}
	if (StartService(hService, 0, NULL) == false) {
		return false;
	}
	CloseServiceHandle(hScm);
	CloseServiceHandle(hService);
	return true;
}


int main(int argc, char const** argv) { return 0; }