#include<iostream>
#include<forward_list>
#include<list>
#include"string.h"
using namespace std;

int main()
{
	/*
	forward_list<String> numbers{ "1","22","333" };

	auto bb = numbers.before_begin();
	numbers.insert_after(bb, "0");

	numbers.emplace_front("-1");

	int size = distance(numbers.cbegin(), numbers.cend());
	forward_list<String>::iterator p{ numbers.begin() };
	advance(p, size - 1);

	auto last = numbers.emplace_after(p, "4444");

	last = numbers.emplace_after(last, "55555");
	*/
	list<String> words{ "��","����","����","����","����","����","����","��","��","��","��","����","����" };

	list<String>::iterator iter = words.begin();
	//advance(iter, 2);
	//words.remove("����");//�̷��� �Ǹ� iter�� ����Ű�� ���� ������� �˴ϴ�
	//words.erase(iter);

	//words.erase(remove(words.begin(), words.end(), "����"), words.end());
	//for (auto i : words)
	//	cout << i << endl;
	list<int> odd{ 5,1,3,9,7 };
	list<int> even{ 2,6,10,4,8 };
	list<int> num;
	odd.splice(odd.begin(), even, even.begin(), ----even.end());

	//stoi ���� ���ڿ��� ��ȯ
	for (auto i : odd)
		cout << i;
	cout << endl;

	for (auto i : even)
		cout << i;
	cout << endl;

}