#include<iostream>
#include<array>
#include<algorithm>
#include<vector>
#include"C:\Users\user\source\repos\c++\c++\String.h"

using namespace std;
int main()
{
	array<String, 5> words{ "corona","virus","world","crisis","pandemic" };

	cout << "- �����ϱ� �� array<String,5>�� ���� -" << endl;
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
	cout << "- ������ �� array<String,5>�� ���� -" << endl;
	for (int i = 0; i < words.size(); ++i)
		cout << words[i] << " ";
	cout << endl;

	vector<String> v;
	v.reserve(2);

	v.emplace_back("zz");//������ ���ο��� �ؼ� ������ȣ���� �ٿ��شٰ� �մϴ�.
	/*
	������ ũ�Ⱑ ���� ������ �߰��� ���Ҹ� ���� ũ�⸦ ������ vector�� �̵���Ų�� -> ������ �߰��� ���Ҹ��� �̵������ڰ� ȣ��ȴ�
	*/
}