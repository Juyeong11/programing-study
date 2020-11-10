#include<iostream>
#include<random>
#include<fstream>
#include<string>
using namespace std;

int main()
{
	{
		default_random_engine dre;
		uniform_int_distribution uid;

		ifstream in("정수1000개.txt", ios::binary);
		/*
		숫자를 일반 문자로 인식하는듯 1글자에 1바이트 하고 각 글자당1바이트 추가 공간 그리고 줄바꿈 1바이트
		그냥 저장할 경우 3자리 숫자 한 개 ->5바이트 4자리->6바이트...
		ios::binary로 저장할 경우 3자리->4바이트 4자리->5바이트...

		숫자를 int로 메모장에 저장하는 법은?

		어떻게 out때는 int로 형변환을 하는 거지??
		char변수로도 받아지고  int 변수로도 받아진다.
		ifstream
		*/
		int n;
		int max{ numeric_limits<int>::min() };
		for (int i = 0; i < 1000; ++i) {
			n = uid(dre);
			in.read(reinterpret_cast<char*>(&n), sizeof(n));
			if (max < n)
				max = n;
		}
		cout << max << endl;
	}

	/*
	{
		int num = 0B0111'1111'1111'1111'1111;
		cout << "num의 메모리 크기는 " << sizeof(num) << "바이트" << endl;
		cout << "num의 저장된 값은 " << num << endl;

		string s{ to_string(num) };
		cout << "num을 글자로 저장하려면 " << size(s) << "바이트가 필요합니다." << endl;
	}
	*/
}
/*
4자리수 보다 더 크면 실제 보다 더 많은 공간을 차지하게 된다??->char의 경우 크기가 1바이트기 때문에 4자리 이상이 되면 한 숫자당 4바이트 이상이 되서 크기가 커진다.

사람이 읽을 필요가 없다면 bit값을 그대로 저장하는 것이 가장 좋습니다.

바이너리 파일은 데이터의 저장과 처리를 목적으로 0과 1의 이진 형식으로 인코딩된 파일을 가리킵니다.
프로그램이 이 파일의 데이터를 읽거나 쓸 때는 데이터의 어떠한 변환도 일어나지 않습니다.

텍스트 파일은 사람이 알아볼 수 있는 문자열로 이루어진 파일을 가리킵니다.
프로그램이 이 파일의 데이터를 읽거나 쓸 때는 포맷 형식에 따라 데이터의 변환이 일어납니다.
*/