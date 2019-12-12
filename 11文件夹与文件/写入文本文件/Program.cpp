#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv)
{
    ofstream outfile;
    outfile.open("1.txt", ios::out);
    outfile << "hello";
    outfile.close();
    return 0;
}