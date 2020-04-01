#include <iostream>
#include <direct.h>
#include <io.h>

using namespace std;

int main(int argc, char **argv)
{
    char *folderName = "AAA";
    if (access(folderName, 6) == -1)
    {
        mkdir(folderName);
    }
    return 0;
}