#include <fstream>
#include <codecvt>

int main() {
    std::wofstream outputFile("output.txt", std::ios::binary);  // Open the file in binary mode

    // Configure the output file to use UTF-8 encoding
    outputFile.imbue(std::locale(outputFile.getloc(), new std::codecvt_utf8<wchar_t>));

    outputFile << L"str1 and 练习.png are equal" << std::endl;

    outputFile.close();

    return 0;
}
