#include<iostream>
#include<string>
#include<charconv>
#include<string_view>

/*
strlen�� �޸��� ���̰� �ƴ� ���ڿ��� ���̸� ����Ѵ�.

��Ʈ�� ���ͷ��� ���������� �޸��� �б� ���� ������ ����ȴ�.

char* ptr = "hello"; ��Ʈ�� ���ͷ�
char ptr[]="hello"; ���ڹ迭

���� ��Ʈ�� ���ͷ��� ������ ������ ������ ����� ���۷����� �����Ѵ�.
�� ��Ʈ�� ���ͷ��� �����ٿ� ���� �ۼ��� ��Ʈ�� ���ͷ��̸� �̽������� �������� �Ϲ� �ؽ�Ʈ�� ����Ѵ�. -> \t, \n �̽������� ������

auto string1 = "Hello World";	const char* Ÿ��
auto string2 = "Hello World"s;	string Ÿ��
auto string3 = "Hello World"sv;	string_view Ÿ��

c_str() �޼��带 ����� c�� ���� ȣȯ���� ������ �� �ִ�.-> data()�� ���� c_str�� ���� �� ���� ���ڿ��� �ٲ� ��ȯ���ش�.
*/
int main()
{
	//���ڿ����� ���� ã�Ƽ� ���ڷ� ��ȯ
	const std::string toParse = " 123USD";
	size_t index = 0;//���ڿ����� ���ڰ� �ƴ� �κ� �������� �ε����� ������ ������ ��� 4;
	int value = std::stoi(toParse, &index);
	std::cout << "Index value: " << index << std::endl;
	std::cout << "Parsed value: " << value << std::endl;
	std::cout << "First non-parsed character: '" << toParse[index] << "'" << std::endl;

	//���� ���ڿ� ��ȯ
	double d = 3.14L;
	std::string s = std::to_string(d);

	std::cout << s[1] << std::endl;

	//�ο췹�� ���� ��ȯ
	std::string out(10, ' ');//���� 12345�� ���� ���ڿ� 
	auto result = std::to_chars(out.data(), out.data() + out.size(), 12345);
	if (result.ec == std::errc()) {//������ ������ value_to_large
		std::cout << out << std::endl;
	}

	//string_view Ŭ���� ->�б� ���� ��Ʈ���� �޴� �Լ��� �Ű����� Ÿ���� ������ �� �ְ� ���شٴµ� ������ �𸣰ڴ�  const string&��� ����� �� �ִ�.
	//string_view �� ��κ� ������ �����Ѵ�. ��Ʈ���� ���� �����Ϳ� ���̸� ���� �־ 
	std::string str = "Hello";
	std::string_view sv = "world";

	//auto result = str + sv; -> ���� ���� ������ �� ����.
	auto result1 = str + sv.data();

	std::string fileName = R"(c:\temp\my file.ext)";
	//??std::cout << "C++string: " << extractExtension(fileName) << std::endl;

	return 0;
}