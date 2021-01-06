#pragma once
#include"SpreadsheetCell.h"

class StringSpreadsheetCell : public SpreadsheetCell
{
public:
	virtual void set(std::string_view inString) override;
	virtual std::string getString()const override;
private:
	std::optional<std::string> mValue;
};