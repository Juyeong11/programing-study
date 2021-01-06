/*#include<iostream>
#include<forward_list>
#include<list>
#include<deque>
#include<array>
#include<vector>
#include<iterator>
#include"string.h"
using namespace std;

template <class T>
void showCategory(const T&);

int main()
{
	istream_iterator<char> in_iter;
	ostream_iterator<short> out_iter{ cout };
	forward_list<int>::iterator forward_list_iter;
	list<float*>::iterator list_iter;
	deque<double>::iterator deque_iter;
	array<String*, 0>::iterator array_iter;
	vector<vector<char>>::iterator vector_iter;

	int* a = nullptr;
	showCategory(a);
	showCategory(out_iter);
	showCategory(forward_list_iter);
	showCategory(list_iter);
	showCategory(deque_iter);
	showCategory(array_iter);
	showCategory(vector_iter);

}
template<class T>
void showCategory(const T& t)
{
	cout << typeid(iterator_traits<T>::iterator_category).name() << endl;
}*/

#include<iostream>
#include<algorithm>
#include"string.h"
using namespace std;

int main()
{
	String str{ "The quick brown fox jumps over the lazy dog" };

	//cout << typeid(iterator_traits<String::iterator>::iterator_category).name() << endl;
	sort(str.begin(), str.end());
	
	for (auto a : str)
		cout << a;
	cout << endl;
}