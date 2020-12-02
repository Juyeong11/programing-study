#include<iostream>
#include<array>
#include<algorithm>
#include<vector>
#include"C:\Users\user\source\repos\c++\c++\String.h"

using namespace std;
int main()
{
	array<String, 5> words{ "corona","virus","world","crisis","pandemic" };

	cout << "- 정렬하기 전 array<String,5>의 내용 -" << endl;
	for (int i = 0; i < words.size(); ++i)
		cout << words[i] << " ";
	cout << endl;
	cout << endl;

	for (String& a : words)
	{
		string tmp = a.getString();
		sort(tmp.begin(), tmp.end());
		a = String(tmp.c_str());
	}
	cout << "- 정렬한 후 array<String,5>의 내용 -" << endl;
	for (int i = 0; i < words.size(); ++i)
		cout << words[i] << " ";
	cout << endl;

	vector<String> v;
	v.reserve(2);

	v.emplace_back("zz");//생성을 내부에서 해서 생성자호출을 줄여준다고 합니다.
	/*
	벡테의 크기가 변해 이전에 추가한 원소를 새로 크기를 조정한 vector로 이동시킨다 -> 이전에 추가한 원소마다 이동생성자가 호출된다
	*/
}