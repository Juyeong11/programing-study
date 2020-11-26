#include<iostream>
#include<cmath>
#include<thread>
using namespace std;

class Dog {
	int n;
public:
	void show()
	{
		cout << "iam Dog" << endl;
	}
};
void f(int n)
{
	cout << "f: " << n << endl;
}

void jump();
void slide();

int main()
{
	/*
	{
		//함수의 이름이 번지이기 때문에 함수 f를 간접참조연산사*를 앞에 붙이면 *f는 이론상 함수의 시작번지가 된다
		//하지만 함수 자체가 시작번지 이기 때문에 f나*f나 차이가 없다.
		f(1);
		(*f)(2);

		void* p = f;
		cout << "함수 f의 주소" << p << endl;

		int n{};
		cout << "스택의 주소: " << &n << endl;

		//p에 저장한 주소를 f(int)함수 주소로 형변환 한것
		(*(void(*)(int))p)(3);
	}
	*/
	/*
	{
		char key;
		bool flag{ false };

		//함수를 호출한다는 것은 함수의 시작번지로 CPU의 프로그램 카운터를 옮기는 것입니다.
		//C++문법으로 호출한다는 것은 어떤 것에 ()를 붙인다는 것이빈다.

		()를 함수 호출 연산자라고 하고 이것을 붙일 수 있는 타입을 호출가능 타입이라고 합니다.

		void(*f)() = jump;
		void(*f1)() = slide;
		while (true) {
			cout << "prass any key: ";
			cin >> key;

			switch (key)
			{
			case'a':
				[[__fallthrough]]
			case'A':
				f();
				break;
			case'd':
				[[__fallthrough]]
			case'D':
				f1();
				break;
			case'c':
				[[__fallthrough]]
			case'C':
			{
				auto temp{ f };
				f = f1;
				f1 = temp;
			}
			break;
			case'q':
				[[__fallthrough]]
			case'Q':
				flag = true;
				break;
			default:
				break;
			}
			if (flag)
				break;
			key = NULL;
		}
	}
	*/
	/*
	{
		void(*callableType)() = []() {
			cout << "Hi im lamda" << endl;
		};
		//분명 차이가 있는데 뭔지 모르겠다.
		auto callableType2 = []() {
			cout << "asdf" << endl;
		};

		//호출가능타입은 ()를 붙일 수 있다.
		callableType();
		cout << typeid(callableType).name() << endl;
	}


	{//std::bind 호출 가능 타입을 반환해줌
		int multiple(int _a, int _b)
		{
			return _a * _b;
		}
		int main()
		{
			int a = 10;
			int b = 20;
			auto fun1 == std::bind(multiple, a, b);//이 함수가 필요한 시점에 호출 할 수 있도록해주는 객체를 만들어 준다.
			auto fun2 == std::bind(multiple, std::cref(a), std::cref(b));//참조를 넘겨주면 중간에 값이 바뀌면 바인딩 된 값도 같이 바뀐다.
		}
	}
	{//std::function
		// 인자와 리턴값의 형식이 같다면 어떤 호출가능 타입이라도 수용함
		// 맴버 함수를 보관할때는 호출한 객체가 무엇인지 알려주어야 한다.
	}
	*/
	auto dog = make_unique<Dog>();
	
	int a = 10;
	auto dogs = make_unique<Dog[]>(a);
	unique_ptr<Dog[]> dogg{ new Dog[a] };//<Dog>로 생성을 하면 첫번째 객체만 가지고 있고 나머지 객체를 가르킬수 없다?
	dogs[1].show();
	dogg[1].show();
	//dogg->show();
}
void jump()
{
	cout << "jump" << endl;
}
void slide()
{
	cout << "slide" << endl;
}