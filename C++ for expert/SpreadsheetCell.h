#include<string>
#include<string_view>
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
class SpreadsheetCell {
public:
	SpreadsheetCell() = default;//�̷��� ���ָ� ���� ����Ʈ �����ڸ� �ۼ����� �ʾƵ� �ȴ�
	//SpreadsheetCell() = delete;//���������� �������ټ� �� �ִ�.
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(std::string_view initialValue);
	//SpreadsheetCell(const SpreadsheetCell& src);
	SpreadsheetCell& operator=(const SpreadsheetCell& rhs);

	void setValue(double inValue);
	double getValue()const;

	void setString(std::string_view inString);
	std::string getString() const;
private:
	std::string doubleToString(double inValue)const;
	double stringToDouble(std::string_view inString) const;
	double mValue = 0;
};