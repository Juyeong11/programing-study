#pragma once
#include<cstddef>
#include"SpreadsheetCell.h"

class Spreadsheet
{
public:
	Spreadsheet(size_t width, size_t height);
	//Spreadsheet(const Spreadsheet& src) = delete;
	~Spreadsheet();
	Spreadsheet(const Spreadsheet& src);
	Spreadsheet& operator=(const Spreadsheet& rhs);
	friend void swap(Spreadsheet& first, Spreadsheet& second)noexcept;

	Spreadsheet(Spreadsheet&& src)noexcept;
	Spreadsheet& operator=(Spreadsheet&& rhs)noexcept;

	void setCellAt(size_t x, size_t y, const SpreadsheetCell& cell);
	SpreadsheetCell& getCellAt(size_t x, size_t y);
private:
	Spreadsheet() = default;
	void cleanup()noexcept;
	//void moveFrom(Spreadsheet& src)noexcept;

	void verifyCoordinate(size_t x, size_t y) const;
	size_t mWidth = 0;
	size_t mHeight = 0;
	SpreadsheetCell** mCells = nullptr;
};