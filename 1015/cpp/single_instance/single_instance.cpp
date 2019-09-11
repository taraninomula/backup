#include<iostream>
using namespace std;

class Single
{
	private:
		/* Here will be the instance stored. */
		static Single *instance;
		Single()
		{
		}
	public:
		/* Static access method. */
		static Single* getInstance()
		{
			if (instance == 0)
			{
				instance = new Single();
			}
			return instance;
		}
};

Single* Single::instance=0;

int main()
{
	Single *s = Single::getInstance();
	Single *r = Single::getInstance();
	Single *q = Single::getInstance();
	
	/* The addresses will be the same.*/
	std::cout << s << std::endl;
	std::cout << r << std::endl;
	std::cout << q << std::endl;
}

