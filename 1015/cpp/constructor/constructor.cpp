#include<iostream>
using namespace std;
class Id
{
	public:
	int id;
	Id()
	{
		cout << "default constructor called" << endl;
	}
	Id(int x)
	{
		cout << "parameterised constructor called" << endl;
		id=x;
		cout << "id is : " << id << endl;
	}
};
int main()
{
	Id obj;
	obj.id=14;
	cout << "id is : " << obj.id << endl;
	Id obj1(18);
}

