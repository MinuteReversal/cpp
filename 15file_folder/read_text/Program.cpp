#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv)
{
    ifstream infile;
    infile.open("1.txt");
    char content[100];
    infile >> content;
    cout << content;
    infile.close();
    return 0;
}