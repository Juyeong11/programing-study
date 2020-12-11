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
/*	cout << "����" << endl;

	using namespace std::chrono;
	auto start = steady_clock::now();

	ifstream in("����1000����.data", ios::binary);
	//���� �ð�6832 -> �� �񱳸��� �Լ� �����͸� ���� ���� ȣ���� �����ϱ� ������ ����ȭ�� �����
	//���� �ð�	12 -> c++�� ���ø��� Ư�� ���������� �� �Լ��� ���� ����ȭ�� �ڵ带 �����Ѵ�.
	in.read((char*)&mydata, sizeof(int) * 10'0000);

	qsort(mydata, 100000, sizeof(int) ,[](const void* a, const void* b) {
		int num1 = *static_cast<int const*> (a);
		int num2 = *static_cast<int const*> (b);
		if (num1 < num2)
			return -1;
		else
			return 1;
	});

	ofstream out("����1000��������.data", ios::binary);

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

