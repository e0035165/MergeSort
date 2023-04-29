#include <iostream>
using namespace std;

void buildArray()
{
	int* p;
	int value = 0;
	int size = 0;
	int a = 0;
	p = &a;
	while (value != -1)
	{
		cout << "Input value: ";
		cin >> value;
		*p = value;
		p += sizeof(int);
	}
}