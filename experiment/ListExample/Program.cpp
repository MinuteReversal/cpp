#include <iostream>
#include <list>
#include <string>
#include "showlist.h"

using namespace std;

int main(int argc, char **argv)
{
    const auto mylist = new list<string>();
    for (auto i = 0; i < 10; i++)
    {
        mylist->push_back("i:" + to_string(i));
    }
    showList(mylist);

    auto it1 = mylist->begin();
    advance(it1, 3);
    mylist->erase(it1);

    showList(mylist);

    mylist->clear();

    mylist->push_back("A");
    mylist->push_back("B");
    mylist->push_back("C");

    showList(mylist);
    mylist->pop_back();
    showList(mylist);
    mylist->pop_back();
    showList(mylist);
    mylist->pop_back();
    showList(mylist);

    delete mylist;
    return 0;
}

void showList(list<string> *list)
{
    cout << "-------------" << endl;
    for (auto iterator = list->begin(); iterator != list->end(); ++iterator)
    {
        cout << *iterator << endl;
    }
}