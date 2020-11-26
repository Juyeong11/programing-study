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
		//�Լ��� �̸��� �����̱� ������ �Լ� f�� �������������*�� �տ� ���̸� *f�� �̷л� �Լ��� ���۹����� �ȴ�
		//������ �Լ� ��ü�� ���۹��� �̱� ������ f��*f�� ���̰� ����.
		f(1);
		(*f)(2);

		void* p = f;
		cout << "�Լ� f�� �ּ�" << p << endl;

		int n{};
		cout << "������ �ּ�: " << &n << endl;

		//p�� ������ �ּҸ� f(int)�Լ� �ּҷ� ����ȯ �Ѱ�
		(*(void(*)(int))p)(3);
	}
	*/
	/*
	{
		char key;
		bool flag{ false };

		//�Լ��� ȣ���Ѵٴ� ���� �Լ��� ���۹����� CPU�� ���α׷� ī���͸� �ű�� ���Դϴ�.
		//C++�������� ȣ���Ѵٴ� ���� � �Ϳ� ()�� ���δٴ� ���̺��.

		()�� �Լ� ȣ�� �����ڶ�� �ϰ� �̰��� ���� �� �ִ� Ÿ���� ȣ�Ⱑ�� Ÿ���̶�� �մϴ�.

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
		//�и� ���̰� �ִµ� ���� �𸣰ڴ�.
		auto callableType2 = []() {
			cout << "asdf" << endl;
		};

		//ȣ�Ⱑ��Ÿ���� ()�� ���� �� �ִ�.
		callableType();
		cout << typeid(callableType).name() << endl;
	}


	{//std::bind ȣ�� ���� Ÿ���� ��ȯ����
		int multiple(int _a, int _b)
		{
			return _a * _b;
		}
		int main()
		{
			int a = 10;
			int b = 20;
			auto fun1 == std::bind(multiple, a, b);//�� �Լ��� �ʿ��� ������ ȣ�� �� �� �ֵ������ִ� ��ü�� ����� �ش�.
			auto fun2 == std::bind(multiple, std::cref(a), std::cref(b));//������ �Ѱ��ָ� �߰��� ���� �ٲ�� ���ε� �� ���� ���� �ٲ��.
		}
	}
	{//std::function
		// ���ڿ� ���ϰ��� ������ ���ٸ� � ȣ�Ⱑ�� Ÿ���̶� ������
		// �ɹ� �Լ��� �����Ҷ��� ȣ���� ��ü�� �������� �˷��־�� �Ѵ�.
	}
	*/
	auto dog = make_unique<Dog>();
	
	int a = 10;
	auto dogs = make_unique<Dog[]>(a);
	unique_ptr<Dog[]> dogg{ new Dog[a] };//<Dog>�� ������ �ϸ� ù��° ��ü�� ������ �ְ� ������ ��ü�� ����ų�� ����?
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