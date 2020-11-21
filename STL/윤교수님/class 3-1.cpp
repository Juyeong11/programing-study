#include<iostream>
#include<fstream>
#include<string>
#include<random>
#include<array>
using namespace std;
int gid{};

default_random_engine dre;
uniform_int_distribution<int> uidAge(1, 12);
uniform_int_distribution<int> uidName('a', 'z');
uniform_int_distribution<int> uidNameLen(3, 15);
//dog의 메모리 크기를 2의 배수로 하라고 지시하는 명령어 alignas
class alignas(64) Dog {
	string name;
	int age;
	int id;
public:
	Dog() : id{ gid++ }
	{
		int len = uidNameLen(dre);
		for (int i = 0; i < len; ++i)
			name += uidName(dre);
		age = uidAge(dre);
	}
	Dog(string n, int a) :name(n), age(a),id(++gid)
	{

	}
	friend ostream& operator<<(ostream& os, const Dog& t);
	string getName()
	{
		return name;
	}
};

ostream& operator<<(ostream& os, const Dog& t)
{
	os<< t.name <<", " << t.age<<", "<<t.id;
	return os;
}
const int dog_data_size = 10000;
array<Dog, dog_data_size> dogs;

int main()
{
	/*
	cout << "Dog 메모리 크기 - " << sizeof(Dog) << endl;
	Dog dog{ "eee",3 };
	cout << dog << endl;
	*/

	//ofstream out("Dog만마리", ios::binary);
	//
	//for (int i = 0; i < dog_data_size; ++i)
	//{
	//	Dog d;
	//	out.write(reinterpret_cast<char*>(&d), sizeof(string));
	//}
	ifstream in("Dog만마리", ios::binary);
	
	for (int i = 0; i < dog_data_size; ++i) {
		
		in.read(reinterpret_cast<char*>(&dogs[i]), sizeof(Dog));
	}
	sort(dogs.begin(), dogs.end(), [](Dog a, Dog b) {
		return a.getName() < b.getName();
	});

	cout << dogs[0] << endl;

	cout << dogs[dog_data_size-1] << endl;
}
//클래스를 write하면 read할때 클래스를 그대로 읽어주네 시부레 이게뭐야 굳이 맴버변수끼리 따로 저장할 필요가 없네 