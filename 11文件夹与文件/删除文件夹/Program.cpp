#include <iostream>
#include <direct.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv)
{
    char *name = "AAA";
    mkdir(name);
    _sleep(1000);
    rmdir(name);
    return 0;
}