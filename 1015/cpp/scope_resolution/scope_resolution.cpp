#include<iostream>
using namespace std;
class student
{
	public:
	int rn;
	string name;
	void printrn()
	{
		cout << "roll no is : " << rn;
	}
	void printname();
};
void student :: printname()
{
	cout << "name is : " << name;
}
int main()
{
	student obj;
	obj.rn=12;
	obj.name="nisha";

	obj.printrn();
	cout << endl;
	obj.printname();
	cout << endl;
}

