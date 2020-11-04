#include"save.h"

using namespace std;


void save(const char* fileName)
{
	ifstream in(fileName);

	ofstream out("강의저장.txt", ios::app);

	int c;

	while ((c = in.get()) != EOF)
		out << (char)c;

	cout << fileName <<"을 강의저장.txt에 저장하였습니다." << endl;
}