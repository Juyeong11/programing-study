#include"save.h"

using namespace std;


void save(const char* fileName)
{
	ifstream in(fileName);

	ofstream out("��������.txt", ios::app);

	int c;

	while ((c = in.get()) != EOF)
		out << (char)c;

	cout << fileName <<"�� ��������.txt�� �����Ͽ����ϴ�." << endl;
}