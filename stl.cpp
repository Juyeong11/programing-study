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
	friend로 선언된 대상에는 public처럼 작용한다.
	연산자 오버로딩시 멤버 함수 인가 전역함 수 인가에 따라 인수가 달라짐
	pos1.operator+(pos2),,,operator+(pos1, pos2)

	*/

	friend ostream& operator<<(ostream& os, const X& dt)//friend 전역함수
	{
		os << dt.x;//X의 friend이기 때문에 private멤버에 접근할 수 있다.
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
cout은 ostream의 객체*/
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