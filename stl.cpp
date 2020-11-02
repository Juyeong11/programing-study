#include<iostream>

using namespace std;


class X {
private:
	int x;
public:
	X(int i) : x(i) {};
	void operator = (const X& y) {
		x = y.x;
	}
	/*
	friend�� ����� ��󿡴� publicó�� �ۿ��Ѵ�.
	������ �����ε��� ��� �Լ� �ΰ� ������ �� �ΰ��� ���� �μ��� �޶���
	pos1.operator+(pos2),,,operator+(pos1, pos2)

	*/

	friend ostream& operator<<(ostream& os, const X& dt)//friend �����Լ�
	{
		os << dt.x;//X�� friend�̱� ������ private����� ������ �� �ִ�.
		return os;
	}

	ostream& operator<<(const X& dt)
	{
		ostream& os = cout;
		os << dt.x;
		return os;
	}
};


/*
cout�� ostream�� ��ü*/
void change(X& x, X& y)
{
	X tmp(x);
	x = y;
	y = tmp;
}
int main()
{
	X a{ 1 };
	X b{ 2 };

	change(a, b);
	a << b;
	//cout << a << "; " << b << endl;
}