/*
#include<iostream>
#include<vector>
#include<string>
#include<iterator>
#include<algorithm>

using namespace std;

int main()
{
	cout << "�ܾ �Է� | �������� ctrl-z�Է�" << endl;

	vector<string> v{ istream_iterator<string>(cin), istream_iterator<string>() };//�ܾ ����
	//sort(v.begin(), v.end());
	sort(begin(v), end(v));
	copy(begin(v), end(v), ostream_iterator<string>(cout, "\t"));
}
*/
#include<iostream>
#include<string>
#include<memory>

using namespace std;
class String {
private:
	
	size_t len{ 0 };
	char* p{ nullptr };
public:
	String() = default;
	String(const char* s);

	virtual ~String();

	String(const String& other);
	String& operator=(const String& rhs);

	String(String&& other)noexcept;

	String& operator=(String&& rhs)noexcept;

	char& operator[](size_t idx);
	char operator[](size_t idx) const;

	size_t size() const;
	std::string getString()const;

	friend std::ostream& operator<<(std::ostream& os, const String& s);
};

String::String(const char* s):p(new(char[len])),len(strlen(s)+1)
{
	strcpy_s(p, len,s);
	//std::unique_ptr<char[]> a = std::make_unique<char[]>(len);
	//s = a.get(); //���� ������ ��Ģ�̴� �̷��� �ϸ� �ȵǰڳ׿�
}

String::~String()
{
	if(p)
		delete[] p;
}
size_t String::size() const
{
	return len;
}
string String::getString() const
{
	string ret{ p };
	return ret;
}

String::String(const String& other)
{
	//���� �����ڴ� �ʱ�ȭ�� �����̱� ������ �ڱ������ ó���� �ʿ䰡 ����
	len = strlen(other.p)+1;
	p = new(char[len]);
	strcpy_s(p, len, other.p);
	//���� Ŭ������ ����ϸ� �ٸ� ��ü���� �ش� private����� ���� ������ �����ϴ�
}

String& String::operator=(const String& rhs)
{
	//�ڱ� ���� Ȯ��
	if (this == &rhs) return *this;

	if (p)
		delete[] p;
	len = strlen(rhs.p) + 1;
	p = new(char[len]);
	strcpy_s(p, len, rhs.p);
	cout << "?>?" << endl;
}

String::String(String&& other) noexcept
{
	p = other.p;
	len = other.len;
	other.p = nullptr;
	other.len = 0;
}

String& String::operator=(String&& rhs) noexcept
{
	if (this == &rhs) return *this;
	p = rhs.p;
	len = rhs.len;
	rhs.p = nullptr;
	rhs.len = 0;
	return *this;
}

char& String::operator[](size_t idx)//��ȯ���� Ÿ�Կ� ���󹫽����̰� ����??
{
	cout << "&" << endl;
	if (!p) return p[0];
	if (idx < 0) return p[0];
	if (idx > len) return p[len];
	return p[idx];
}

char String::operator[](size_t idx) const
{
	if (!p) return 0;
	if (idx < 0) return p[0];
	if (idx > len) return p[len];
	return p[idx];
}

std::ostream& operator<<(std::ostream& os, const String& s)
{
	for(int i=0;i<s.len;++i)
		os << s.p[i];
	return os;
}
int main()
{
	String a{"������"};

	auto b = make_unique<String>("asdf");
	*b = a;
	cout << *b << endl;
}