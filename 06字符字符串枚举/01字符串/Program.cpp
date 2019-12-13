#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[], char *envp[])
{
    const string s = "hello world";
    cout << s.length() << endl;
    cout << s << endl;
    string s2 = s + "666";
    cout << s2 << endl;
    cout << (s == "hello world") << endl;

    string s3;
    cin >> s3;
    cout << s3 << endl;

    return 0;
}