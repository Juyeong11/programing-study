#include"StringSpreadsheetCell.h"

using namespace std;

void StringSpreadsheetCell::set(string_view inString)
{
	mValue = inString;
}
string StringSpreadsheetCell::getString()const
{
	return mValue.value_or("");
}