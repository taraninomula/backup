#include<iostream>
using namespace std;
class Name
{
	public:
	string name;
	void print()
	{
		cout << "name is " << name;
	}
};
int main()
{
	Name obj;
	obj.name="Tarani";
	obj.print();
}
