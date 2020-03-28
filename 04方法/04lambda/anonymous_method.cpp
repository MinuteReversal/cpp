#include <iostream>
using namespace std;
int main(){
   auto fn1=[](){cout<<"fn1"<<endl;};
   auto fn2=[](int a){cout<<a<<endl;};
   auto fn3=[](){return 3;};
   auto fn4=[](int x){return x;};
   
   fn1();
   fn2(2);
   cout<<fn3()<<endl;
   cout<<fn4(4)<<endl;
}
