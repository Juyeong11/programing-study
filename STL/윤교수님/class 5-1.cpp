#include <iostream>
#include "string.h"
using namespace std;

int main()
{
	String s{ "asdfasdf" };
	cout << "s�� ũ��: " << sizeof(s) << "����Ʈ" << endl;
	cout << "s�� ����: " << &s << endl;

	int n{ 2020 };
	cout << "n�� ����: " << &n << endl;

	cout << endl;
	cout << "s�� �Ҵ��� �޸��� ����: " << static_cast<void*>(&s[0]) << endl;
	int* p = new int{ 777 };
	cout << "Heap�� ����: " << p << endl;
	cout << "p�� ����: " << &p << endl;
}