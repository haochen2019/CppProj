#include "Vector.h"
#include <iostream>
using namespace std;

class Func
{
public:
	void operator()(const int& i)
	{
		std::cout << i << std::endl;
	}
};

int main()
{
	Vector<int> a(10,10,5);

	a.traverse(Func());

	system("pause");
}