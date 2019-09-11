#include<iostream>
using namespace std;
int main()
{
	int n,i;
	cout << "enter a number\n";
	cin >> n;
	for(i=1;i<=n;i++)
	{
		if(n%i == 0)
			cout << "\t" << i;
	}
	cout << "\n";
}

