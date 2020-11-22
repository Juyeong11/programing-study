#include<iostream>
#include<string>
#include<charconv>
#include<string_view>

/*
strlen은 메모리의 길이가 아닌 문자열의 길이를 출력한다.

스트링 리터럴은 내부적으로 메모리의 읽기 전용 영역에 저장된다.

char* ptr = "hello"; 스트링 리터럴
char ptr[]="hello"; 문자배열

같은 스트링 리터럴이 여러번 나오면 기존에 사용한 레퍼런스를 재사용한다.
로 스트링 리터럴은 여러줄에 걸쳐 작성한 스트링 리터럴이며 이스케이프 시퀸스를 일반 텍스트로 취급한다. -> \t, \n 이스케이프 시퀸스

auto string1 = "Hello World";	const char* 타입
auto string2 = "Hello World"s;	string 타입
auto string3 = "Hello World"sv;	string_view 타입

c_str() 메서드를 사용해 c언어에 대한 호환성을 보장할 수 있다.-> data()와 유사 c_str의 경우는 널 종료 문자열로 바꿔 반환해준다.
*/
int main()
{
	//문자열에서 숫자 찾아서 숫자로 변환
	const std::string toParse = " 123USD";
	size_t index = 0;//문자열에서 숫자가 아닌 부분 전까지의 인덱스를 구해줌 예제의 경우 4;
	int value = std::stoi(toParse, &index);
	std::cout << "Index value: " << index << std::endl;
	std::cout << "Parsed value: " << value << std::endl;
	std::cout << "First non-parsed character: '" << toParse[index] << "'" << std::endl;

	//숫자 문자열 변환
	double d = 3.14L;
	std::string s = std::to_string(d);

	std::cout << s[1] << std::endl;

	//로우레벨 숫자 변환
	std::string out(10, ' ');//정수 12345를 담을 문자열 
	auto result = std::to_chars(out.data(), out.data() + out.size(), 12345);
	if (result.ec == std::errc()) {//오류가 없으면 value_to_large
		std::cout << out << std::endl;
	}

	//string_view 클래스 ->읽기 전용 스트링을 받는 함수의 매개변수 타입을 결정할 수 있게 해준다는데 아직은 모르겠다  const string&대신 사용할 수 있다.
	//string_view 는 대부분 값으로 전달한다. 스트링에 대한 포인터와 길이만 갖고 있어서 
	std::string str = "Hello";
	std::string_view sv = "world";

	//auto result = str + sv; -> 서로 연결 결합할 수 없다.
	auto result1 = str + sv.data();

	std::string fileName = R"(c:\temp\my file.ext)";
	//??std::cout << "C++string: " << extractExtension(fileName) << std::endl;

	return 0;
}