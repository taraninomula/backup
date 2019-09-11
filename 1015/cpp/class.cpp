#include<iostream>
using namespace std;
class Abc
{
     public:
	void display()
	{
		cout<<"inside class\n";
	}
	int add(int a,int b)
	{
		int c=a+b;
		cout<<"c",<<c;
	}
};
int main()
{
	int a=1,b=2;
	Abc obj;
	obj.display();
	obj.add(a,b);
}

