#include <iostream>
using namespace std;
class A{
	public:
	void print(char* c){
		cout<<c<<endl;
	}
};
class B{
	private:
	 void (A::*delegate)(char*);
	public:
	 void AddEventListener(void(A::*pFn)(char*)){
	 	delegate=pFn;
	 }
	 void DispatchEvent(A a){
	    char s[]="hello";
	 	(a.*delegate)(s);
	 }
};

int main(){
	A a;
	B b;
	b.AddEventListener(&A::print);
	b.DispatchEvent(a);
	return 0;
}