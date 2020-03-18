/**
 *https://stackoverflow.com/questions/9040617/how-do-i-write-functions-that-accept-unlimited-arguments
 */
#include <iostream>
#include <string>

void output()
{
    std::cout << std::endl;
}

template <typename First, typename... Strings>
void output(First arg, Strings &... rest)
{
    std::cout << arg << " ";
    output(rest...);
}

int main(int argc, char **argv, char **envp)
{
    output("I", "am", "a", "sentence");
    return EXIT_SUCCESS;
}