#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    //http://forum.codecall.net/topic/72818-cgi-programming-in-c/
    cout << "Content-type:text/html;\r\n\r\n";
    string line;
    while (getline(cin,line))
    {
        /* code */
    }
    
    return 0;
}