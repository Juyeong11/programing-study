#include"DoubleSpreadsheetCell.h"
using namespace std;

void DoubleSpreadsheetCell::set(double inDouble)
{
	mValue = inDouble;
}
void DoubleSpreadsheetCell::set(string_view inString)
{
	mValue = stringToDouble(inString);
}
string DoubleSpreadsheetCell::getString()const
{
	return (mValue.has_value() ? doubleToString(mValue.value()) : "");
}

string DoubleSpreadsheetCell::doubleToString(double inValue)
{
	return to_string(inValue);
}
double DoubleSpreadsheetCell::stringToDouble(string_view inValue)
{
	return strtod(inValue.data(), nullptr);
}