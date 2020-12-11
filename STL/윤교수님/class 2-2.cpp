#include<iostream>
#include<thread>
#include<chrono>

#include<string>
using namespace std;

template<typename T,size_t s>
class IntArray {
private:
	T* arr{ nullptr };
	size_t size;
public:
	IntArray(size_t s) :size(s), arr(new T[s]) {

	}
	~IntArray()
	{
		delete[] arr;
	}
	T operator [](int i) const
	{
		return arr[i];
	}
	T& operator [](int i) {
		return arr[i];
	}
};
int main()
{
/*	cout << "시작" << endl;

	using namespace std::chrono;
	auto start = steady_clock::now();

	ifstream in("정수1000만개.data", ios::binary);
	//정렬 시간6832 -> 매 비교마다 함수 포인터를 통해 간접 호출을 수행하기 때문에 최적화가 힘들다
	//정렬 시간	12 -> c++의 템플릿이 특정 데이터형과 비교 함수에 대해 최적화된 코드를 생성한다.
	in.read((char*)&mydata, sizeof(int) * 10'0000);

	qsort(mydata, 100000, sizeof(int) ,[](const void* a, const void* b) {
		int num1 = *static_cast<int const*> (a);
		int num2 = *static_cast<int const*> (b);
		if (num1 < num2)
			return -1;
		else
			return 1;
	});

	ofstream out("정수1000만개정렬.data", ios::binary);

	for (int i : mydata) {
		out.write(reinterpret_cast<char*> (&i), sizeof(int));
	}
	auto d = duration_cast<milliseconds>(steady_clock::now() - start);
	cout << d.count() << endl;
	*/

	IntArray<string,10> a{ 10 };

	for (int i = 0; i < 10; ++i)
		a[i] = "string"s+ to_string(i);

	for (int i = 0; i < 10; ++i)
		cout << a[i] << ' ';
	cout << endl;
}

