//https://docs.microsoft.com/en-us/cpp/cpp/event-handling-in-native-cpp?view=vs-2017
#include <iostream>

using namespace std;
class Listeners
{
  public:
    void ListenerA(char *message)
    {
    }
};

class BroadcastingRoom
{
  public:
    __event void MyEvent(char *message);

    void Subscribe(Listeners ls, void (Listeners::*listener)(char *))
    {
        __hook(&BroadcastingRoom::MyEvent, this, (ls*listener));
    }

    void BroadCast(char *message)
    {
        __raise MyEvent(message);
    }
};

int main(int argc, char **argv)
{
    BroadcastingRoom br;
    Listeners ls;
    br.Subscribe(ls, &Listeners::ListenerA);
    br.BroadCast("happy new year");
    return 0;
}
