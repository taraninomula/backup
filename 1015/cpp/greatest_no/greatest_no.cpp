#include<iostream>
using namespace std;
int main()
{
	int a,b,c;
	cout << "enter 3 numbers\n";
	cin >> a >> b >> c;
	if(a>b && a>c )
		cout << "greatest : " << a << endl;
	else if(b>a && b>c)
		cout << "greatest : " << b << endl;
	else if(c>a && c>b)
		cout << "greatest : " << c << endl;
}
