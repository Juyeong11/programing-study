#include"StringSpreadsheetCell.h"
#include"DoubleSpreadsheetCell.h"
using namespace std;

StringSpreadsheetCell::StringSpreadsheetCell(const DoubleSpreadsheetCell& inDoubleCell)
{
	mValue = inDoubleCell.getString();
}
void StringSpreadsheetCell::set(string_view inString)
{
	mValue = inString;
}
string StringSpreadsheetCell::getString()const
{
	return mValue.value_or("");
}

StringSpreadsheetCell operator+(const StringSpreadsheetCell& lhs, const StringSpreadsheetCell& rhs)
{
	StringSpreadsheetCell newCell;
	newCell.set(lhs.getString() + rhs.getString());
	return newCell;
} 