#include <iostream>
#include "string.h"
using namespace std;

int main()
{
	String s{ "asdfasdf" };
	cout << "s의 크기: " << sizeof(s) << "바이트" << endl;
	cout << "s의 번지: " << &s << endl;

	int n{ 2020 };
	cout << "n의 번지: " << &n << endl;

	cout << endl;
	cout << "s가 할당한 메모리의 번지: " << static_cast<void*>(&s[0]) << endl;
	int* p = new int{ 777 };
	cout << "Heap의 번지: " << p << endl;
	cout << "p의 번지: " << &p << endl;
}