
//-----------------------------------------------------------------------------
// String.h
//
// class String - STL ������ Ŭ���� 
//	1. �����̳��� ���ҷ� ����Ѵ�
//  2. char�� �����ϴ� STL �����̳ʰ� �ǵ��� �ڵ��� ���ư���
//  
// 2020. 4.	Programmed by Wulong
//-----------------------------------------------------------------------------
#pragma once


class String_Iterator {
	char* p{ nullptr };
public:
	String_Iterator(char* p) :p{ p } {};

	
	bool operator !=(const String_Iterator& rhs)const {
		return p != rhs.p;
	}


	String_Iterator& operator ++() {
		++p;
		return *this;
	}
	String_Iterator& operator --() {
		--p;
		return *this;
	}
	char& operator*()const
	{
		return *p;
	}
	//char operator*()
	//{
	//	return *p;
	//}
	String_Iterator operator+(int n) {
		return p + n;//���ο� ��ü�� �����Ǵ°� �ƴϾ�?
	}
	String_Iterator operator-(int n) {
		return p - n;//���ο� ��ü�� �����Ǵ°� �ƴϾ�?
	}
	bool operator<(const String_Iterator rhs)const {
		return p < rhs.p;
	}
	bool operator==(const String_Iterator rhs)const {
		return p == rhs.p;
	}
	ptrdiff_t operator-(const String_Iterator rhs)const {
		return p - rhs.p;
	}
	char operator[](size_t n) const {
		return *(p+n);
	}
	char& operator[](size_t n) {
		return *(p + n);
	}
};


template<class T>
class String_Reverse_Iterator {
	T p{ nullptr };
public:
	String_Reverse_Iterator(T p) :p(p) {};

	bool operator!=(const String_Reverse_Iterator& rhs) const
	{
		return p != rhs.p;
	}
	String_Reverse_Iterator& operator++()
	{
		--p;
		return *this;
	}
	char operator*()
	{
		return *(p - 1);//reverse_iterator�� *������ �ϸ� ����Ű�� �ִ� ������ ���� ���Ұ��� �����Ѵ�.
	}
};

template <>
struct std::iterator_traits<String_Iterator> {
	using iterator_category = random_access_iterator_tag;
	using value_type = char;//??
	using difference_type = ptrdiff_t;
	using pointer = char*;
	using regerence = char&;
};
class String {
	size_t len{ 0 };
	char* p{ nullptr };

public:
	String();

	String(const char* s);

	virtual ~String();

	String(const String& other);

	String& operator=(const String& rhs);

	String(String&& other) noexcept;

	String& operator=(String&& rhs) noexcept;

	char& operator[](size_t idx);

	char operator[](size_t idx) const;

	size_t size() const;
	char& get()
	{
		return *p;
	}
	std::string getString() const;

	// �񱳿�����
	// 2020. 4. 18 �߰�
	bool operator==(const String& rhs) const noexcept;

	// 2020.5. 4 �߰�
	bool operator<(const String& rhs) const;


	// �ݺ��ڸ� ���� ���
	// 2020. 4. 25 �߰�


	using iterator = String_Iterator;
	using reverse_iterator = String_Reverse_Iterator<char*>;
	iterator begin();
	iterator end();

	reverse_iterator rbegin();
	reverse_iterator rend();

	friend std::ostream& operator<<(std::ostream& os, const String& s);
};