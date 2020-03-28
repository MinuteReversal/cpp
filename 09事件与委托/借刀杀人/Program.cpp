#include <iostream>

using namespace std;

class IObject
{
  public:
    virtual char *ToString() = 0;
};

class CaoCao : public IObject
{
  public:
    char *ToString() override
    {
        return "Caocao";
    }
};

class MaChao
{
  private:
    char *Name;

  public:
    MaChao()
    {
        Name = "Machao";
    }
    void Kill(IObject *target)
    {
        cout << Name << " kill " << target->ToString() << endl;
    }
};

class Zhugeliang
{
  public:
    void (MaChao::*BorrowNife)(IObject *) = NULL;
};

int main(int argc, char **argv)
{
    CaoCao caocao;
    Zhugeliang zhugeliang;
    MaChao maChao;

    zhugeliang.BorrowNife = &MaChao::Kill;
    (maChao.*zhugeliang.BorrowNife)(&caocao);

    return 0;
}