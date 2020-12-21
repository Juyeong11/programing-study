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
	list<String> words{ "ÀÏ","ÀÌÀÌ","»ï»ï»ï","»ï»ï»ï","»ï»ï»ï","»ï»ï»ï","»ï»ï»ï","»ç","»ç","»ç","»ç","»ï»ï»ï","»ï»ï»ï" };

	list<String>::iterator iter = words.begin();
	//advance(iter, 2);
	//words.remove("»ï»ï»ï");//ÀÌ·¸°Ô µÇ¸é iter°¡ °¡¸£Å°´Â °ªÀÌ »ç¶óÁö°Ô µË´Ï´Ù
	//words.erase(iter);

	//words.erase(remove(words.begin(), words.end(), "»ï»ï»ï"), words.end());
	//for (auto i : words)
	//	cout << i << endl;
	list<int> odd{ 5,1,3,9,7 };
	list<int> even{ 2,6,10,4,8 };
	list<int> num;
	odd.splice(odd.begin(), even, even.begin(), ----even.end());

	//stoi ¼ıÀÚ ¹®ÀÚ¿­·Î º¯È¯
	for (auto i : odd)
		cout << i;
	cout << endl;

	for (auto i : even)
		cout << i;
	cout << endl;

}