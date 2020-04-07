#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    const auto v = new vector<int>();
    for (auto i = 0; i < 10; i++)
    {
        v->push_back(i);
    }
    cout << "vector size " << v->size() << endl;
    return 0;
}