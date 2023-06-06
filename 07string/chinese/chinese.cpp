#include <iostream>

#include <io.h>
#include <fcntl.h>

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);

    std::wcout << L"str1 and 练习.png are equal" << std::endl;

    return 0;
}