#include<iostream>
#include<random>
#include<fstream>
 
using namespace std;

int main()
{
	default_random_engine dre;
	uniform_int_distribution uid;

	ifstream in("정수1000개.txt");
	/*
	숫자를 일반 문자로 인식하는듯 1글자에 1바이트 하고 각 글자당1바이트 추가 공간 그리고 줄바꿈 1바이트
	그냥 저장할 경우 3자리->5바이트 4자리->6바이트...
	ios::binary로 저장할 경우 3자리->4바이트 4자리->5바이트...

	숫자를 int로 메모장에 저장하는 법은?

	어떻게 out때는 int로 하는 거지??
	ifstream 
	*/
	char n{  };

	while (in >> n)
		cout << n << endl;
}