#include<string>
#include<string_view>
#include<optional>
//���ڿ� Ÿ�� string�� ��ȯ�ϴ� �Լ�
//std::string f();
//
//std::string_view s1 = f();
//NG: �Լ� ��ȯ ��(�ӽ� ���ڿ� ������Ʈ)�� �ı� �Ǳ� ����
//    �� �������� s1�� ���۸� �䰡 �ȴ�
//
//auto&& s2 = f();
//OK: �Լ� ��ȯ ��(�ӽ� ���ڿ� ������Ʈ) ���� �� ���� Ÿ������ �ѱ��
//    �� ���� �Ⱓ�� ���� s2�� �������� ���� ������ ���� �ȴ�.
/*
class SpreadsheetCell {
public:
	

	SpreadsheetCell() = default;//�̷��� ���ָ� ���� ����Ʈ �����ڸ� �ۼ����� �ʾƵ� �ȴ�
	//SpreadsheetCell() = delete;//��������� �������ټ� �� �ִ�.
	SpreadsheetCell(double initialValue);
	explicit SpreadsheetCell(std::string_view initialValue);
	//SpreadsheetCell(const SpreadsheetCell& src);
	SpreadsheetCell& operator=(const SpreadsheetCell& rhs);

	enum class Color { Red = 1, Green, Blue, Yellow };
 

	void set(double inValue);
	void set(std::string_view inString);
	
	SpreadsheetCell& operator+=(const SpreadsheetCell& rhs);

	double getValue()const //�ζ����Լ�
	{
		mNumAccesses++;
		return mValue;
	}
	std::string getString() const
	{
		mNumAccesses++;
		return doubleToString(mValue);
	}
private:
	std::string doubleToString(double inValue)const;
	double stringToDouble(std::string_view inString) const;
	double mValue = 0;
	mutable size_t mNumAccesses = 0;

	Color mColor = Color::Red;
};
SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
*/

class SpreadsheetCell
{
public:
	virtual ~SpreadsheetCell() = default;
	virtual void set(std::string_view inString)=0;//���� ����޼���
	virtual std::string getString() const=0;
};