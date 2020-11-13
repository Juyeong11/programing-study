#include<iostream>
#include<fstream>
#include<iomanip>// 출력형식 조작 https://docs.microsoft.com/ko-kr/cpp/standard-library/iomanip-functions?view=msvc-160

#include<algorithm>
#include<array>

#include<random>
using namespace std;

array<int, 10'000'000> mydata;
array<int, 10'000'000> mydata1;

int main()
{
	//
	//ifstream in("정수1000개.txt", ios::binary);
	//
	//array<int,1000> data;
	//
	//in.read( (char*)&data, sizeof(int) * 1000);
	//
	///*
	////메모리가 연속이라면 어떤 자료라도 정렬가능
	//qsort(data, 1000, sizeof(int), [](const void* a, const void* b) {//stl은 람다를 이용하여 알고리즘의 기능을 원하는 대로 바꿀 수 있다.
	//	int num1 = *static_cast<int const*> (a);
	//	int num2 = *static_cast<int const*> (b);
	//	if (num1 < num2)
	//		return -1;
	//	else
	//		return 1;
	//});
	//*/
	//
	//sort(data.begin(), data.end(), [](int a, int b) {
	//	return a > b;
	//});
	//
	//for (int n : data)
	//	cout << setw(20) << left << n;
	//*/
	//

	//문제 정수1000만개를 저장하고 정렬하고 그 결과를 다시 정렬하라
//	default_random_engine dre;
//	uniform_int_distribution uid(0, numeric_limits<int>::max());
//
//	ofstream out("정수1000만개.data", ios::binary);
//
//	int n;
//	for (int i = 0; i < 10'000'000; ++i) {
//		n = uid(dre);
//		out.write(reinterpret_cast<char*> (&n), sizeof(n));
//	}

	ifstream in("정수1000만개.data", ios::binary);


	in.read((char*)&mydata, sizeof(int) * 10'000'000);

	sort(mydata.begin(), mydata.end(), [](int a, int b) {
		return a > b;
	});

	ofstream out("정수1000만개정렬.data", ios::binary);

	for (int i : mydata) {
		out.write(reinterpret_cast<char*> (&i), sizeof(int));
	}
		
	
}