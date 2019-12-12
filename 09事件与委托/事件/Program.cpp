/*
* https://docs.microsoft.com/en-us/cpp/cpp/event-handling-in-native-cpp?view=vs-2017
*/
#include <iostream>

using namespace std;

[event_source(native)] class CSource
{
public:
    __event void MyEvent(int nValue);
};

[event_receiver(native)] class CReceiver
{
public:
    void MyHandler1(int nValue)
    {
        cout << "MyHandler1 was called with value " << nValue << endl;
    }
    void MyHandler2(int nValue)
    {
        cout << "MyHandler2 was called with value " << nValue << endl;
    }
    void hookEvent(CSource *pSource)
    {
        __hook(&CSource::MyEvent, pSource, &CReceiver::MyHandler1);
        __hook(&CSource::MyEvent, pSource, &CReceiver::MyHandler2);
    }
    void unhookEvent(CSource *pSource)
    {
        __unhook(&CSource::MyEvent, pSource, &CReceiver::MyHandler1);
        __unhook(&CSource::MyEvent, pSource, &CReceiver::MyHandler2);
    }
};

int main(int argc, char *argv)
{
    CSource source;
    CReceiver receiver;

    receiver.hookEvent(&source);
    __raise source.MyEvent(123);
    receiver.unhookEvent(&source);
    return 0;
}
