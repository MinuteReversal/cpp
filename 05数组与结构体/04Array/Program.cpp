#include <iostream>
#include <array>

using namespace std;

int main(int argc, char *argv[], char *envp[])
{
    array<int, 10> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    cout << arr[0] << endl;
    cout << arr.size() << endl;

    for (auto i = arr.begin(); i < arr.end(); i++)
    {
        cout << *i << endl;
    }

    return 0;
}