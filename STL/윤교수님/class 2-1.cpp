#include<iostream>
#include<fstream>
#include<iomanip>// ������� ���� https://docs.microsoft.com/ko-kr/cpp/standard-library/iomanip-functions?view=msvc-160

#include<algorithm>
#include<array>

#include<random>
using namespace std;

array<int, 10'000'000> mydata;
array<int, 10'000'000> mydata1;

int main()
{
	//
	//ifstream in("����1000��.txt", ios::binary);
	//
	//array<int,1000> data;
	//
	//in.read( (char*)&data, sizeof(int) * 1000);
	//
	///*
	////�޸𸮰� �����̶�� � �ڷ�� ���İ���
	//qsort(data, 1000, sizeof(int), [](const void* a, const void* b) {//stl�� ���ٸ� �̿��Ͽ� �˰����� ����� ���ϴ� ��� �ٲ� �� �ִ�.
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

	//���� ����1000������ �����ϰ� �����ϰ� �� ����� �ٽ� �����϶�
//	default_random_engine dre;
//	uniform_int_distribution uid(0, numeric_limits<int>::max());
//
//	ofstream out("����1000����.data", ios::binary);
//
//	int n;
//	for (int i = 0; i < 10'000'000; ++i) {
//		n = uid(dre);
//		out.write(reinterpret_cast<char*> (&n), sizeof(n));
//	}

	ifstream in("����1000����.data", ios::binary);


	in.read((char*)&mydata, sizeof(int) * 10'000'000);

	sort(mydata.begin(), mydata.end(), [](int a, int b) {
		return a > b;
	});

	ofstream out("����1000��������.data", ios::binary);

	for (int i : mydata) {
		out.write(reinterpret_cast<char*> (&i), sizeof(int));
	}
		
	
}