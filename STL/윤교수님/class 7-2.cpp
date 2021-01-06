#include<iostream>
#include<algorithm>
#include<vector>
#include"string.h"
using namespace std;
template<class InIter,class OutIter>
OutIter my_copy(InIter begin, InIter end, OutIter other_b) {
	
	while (begin != end) {
		*other_b = *begin;

		++other_b;
		++begin;
	}

	return other_b;
}
class String_back_insert_iterator {
	String* p;
public:
	String_back_insert_iterator(String& c) :p(&c) {

	}
	String_back_insert_iterator& operator++()
	{
		return *this;
	}
	char& operator*()const
	{
		return p->get();
	}
};
String_back_insert_iterator String_back_inserter(String& c)
{
	return String_back_insert_iterator(c);
}

int main()
{
	string str{ "asdfsasdfweqf fawfcva" };
	String other{"a"};
	//other.resize(str.size());//왜 reserve가 안되지>?????

	my_copy(begin(str), end(str), String_back_inserter(other));

	for (int i = 0; i < str.size(); ++i)
		cout << other[i];
}