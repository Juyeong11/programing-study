#include<iostream>
#include<random>
#include<fstream>
 
using namespace std;

int main()
{
	default_random_engine dre;
	uniform_int_distribution uid;

	ifstream in("����1000��.txt");
	/*
	���ڸ� �Ϲ� ���ڷ� �ν��ϴµ� 1���ڿ� 1����Ʈ �ϰ� �� ���ڴ�1����Ʈ �߰� ���� �׸��� �ٹٲ� 1����Ʈ
	�׳� ������ ��� 3�ڸ�->5����Ʈ 4�ڸ�->6����Ʈ...
	ios::binary�� ������ ��� 3�ڸ�->4����Ʈ 4�ڸ�->5����Ʈ...

	���ڸ� int�� �޸��忡 �����ϴ� ����?

	��� out���� int�� �ϴ� ����??
	ifstream 
	*/
	char n{  };

	while (in >> n)
		cout << n << endl;
}