#include<iostream>
#include<fstream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<string>
using namespace std;

int main()
{
	ifstream in("STL Wiki.txt");
	if (!in)
		return 0;

	//islower(), tolower()
		//ofstream out("STL Wiki소문자.txt");
	/*
	vector<char> str;
	int a;
	while ((a = in.get())!= EOF)
		str.push_back(tolower(a));
		
	vector<int>::const_reverse_iterator i = str.crbegin();//역방향 반복자
	*/
	vector<char> v{ istreambuf_iterator<char>(in), istreambuf_iterator<char>() };
	vector<char> non_white_space{ istream_iterator<char>(in), istream_iterator<char>() };

	//v.erase(remove(v.begin(), v.end(), 'E'), v.end());

	//ofstream out("STL Wiki문자.txt");
	//copy(cbegin(v), cend(v), ostream_iterator<char>(out));

	//XXXXXcout << count(v.begin(), v.end(), ' ') + 1<<endl;


	bool word = false;
	int numOfword = 0;
	vector<char>::iterator start;
	vector<string> str;

	for (vector<char>::iterator iter = v.begin();iter<v.end();++iter)
	{
		if (!word && ' ' !=(*iter))
		{
			word = true;
			start = iter;
		}
		if (word) {
			if (*iter == ' ')
			{
				word = false;
				string a;
				for (start; start < iter; ++start)
					a.push_back(*start);
				str.push_back(a);
			}
		}
	}
	sort(str.begin(), str.end(), [](const string& a, const string& b) {
		return a.size() < b.size();
		});
	for(auto s:str)
	cout << s<<" ";
	cout << endl;
	cout << endl;
	for (char c : v)
		cout << c;
	
	cout << endl;

}