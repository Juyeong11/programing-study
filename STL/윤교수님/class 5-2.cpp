#include<iostream>
#include<fstream>
#include<random>
#include<string>
using namespace std;

void streamout()
{
	ofstream out("정수 만개");

	default_random_engine dre;
	uniform_int_distribution<> uid(0, 100000);

	for (int i = 0; i < 10000; ++i) {
		out << uid(dre) << " ";
		if (i % 10 == 9)
			out << endl;
	}
}

void streamin(vector<int>& data)
{

	
}

int main()
{
	vector<int> mydata;
	mydata.reserve(10000);
	streamin(mydata);
	
}