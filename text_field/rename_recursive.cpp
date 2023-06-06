#include <iostream>
#include <filesystem>
#include <locale>

namespace fs = std::filesystem;

void recursiveVisit(const fs::path& directory)
{
    std::locale::global(std::locale("zh-cn"));  // Set the global locale to the user's default locale

    for (const auto& entry : fs::directory_iterator(directory))
    {
        if (fs::is_directory(entry))
        {
            std::wcout << L"Directory: " << entry.path().wstring() << std::endl;
            recursiveVisit(entry.path());  // Recursively visit subdirectories
        }
        else if (fs::is_regular_file(entry))
        {
            std::wcout << L"File: " << entry.path().wstring() << std::endl;            
        }
    }
}

int main()
{
    fs::path directoryPath = u8"D:\\repository\\qing_yun_flutter3_app\\assets\\images";  // Replace with your desired directory path
    recursiveVisit(directoryPath);
    return 0;
}
