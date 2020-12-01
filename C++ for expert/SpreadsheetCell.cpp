#include"SpreadsheetCell.h"
using namespace std;

//SpreadsheetCell myCell();-> �߸��� �����̴� �⺻�����ڸ� ȣ���ϴ� ���� �ƴϰ� �Լ��� �����Ѵٰ� ���� ������ ���� ������ ��ü������ 

SpreadsheetCell::SpreadsheetCell(double initialValue)
	:mValue(initialValue)//Ŭ���� ���ǿ� �ۼ��� ������� �ʱ�ȭ�ȴ�.
{
	
}
SpreadsheetCell::SpreadsheetCell(string_view initialValue)
{
	setString(initialValue);
}
SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
{
	if (this == &rhs) return *this;
	mValue = rhs.mValue;
	return *this;
	// TODO: ���⿡ return ���� �����մϴ�.
}
//SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& src)
//	:m1(src.m1),m2(src.m2).... -> �⺻ ���� �����ڴ� �̷��� ���ڸ� �������ش�.
void SpreadsheetCell::setValue(double inValue)
{
	mValue = inValue;
}
double SpreadsheetCell::getValue() const
{
	return mValue;
}
void SpreadsheetCell::setString(string_view inString)
{
	mValue = stringToDouble(inString);
}
string SpreadsheetCell::getString() const
{
	return doubleToString(mValue);
}
string SpreadsheetCell::doubleToString(double inValue) const
{
	return to_string(inValue);
}
double SpreadsheetCell::stringToDouble(string_view inString) const
{
	return strtod(inString.data(), nullptr);
}