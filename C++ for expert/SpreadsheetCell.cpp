#include"SpreadsheetCell.h"
using namespace std;

//SpreadsheetCell myCell();-> 잘못된 문장이다 기본생성자를 호출하는 것이 아니고 함수를 선언한다고 여겨 에러는 나지 않지만 객체생성은 

SpreadsheetCell::SpreadsheetCell(double initialValue)
	:mValue(initialValue)//클래스 정의에 작성한 순서대로 초기화된다.
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
	// TODO: 여기에 return 문을 삽입합니다.
}
//SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& src)
//	:m1(src.m1),m2(src.m2).... -> 기본 복제 생성자는 이렇게 인자를 복사해준다.
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