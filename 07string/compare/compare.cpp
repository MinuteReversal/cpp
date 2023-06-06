#include <iostream>

int main(int argc, char const **argv)
{
    std::string str1 = "Hello";
    std::string str2 = "Hello";
    std::string str3 = "World";

    if (str1.compare(str2) == 0)
    {
        std::cout << "str1 and str2 are equal" << std::endl;
    }
    else
    {
        std::cout << "str1 and str2 are not equal" << std::endl;
    }

    if (str1.compare(str3) == 0)
    {
        std::cout << "str1 and str3 are equal" << std::endl;
    }
    else
    {
        std::cout << "str1 and str3 are not equal" << std::endl;
    }
  return 0;
}