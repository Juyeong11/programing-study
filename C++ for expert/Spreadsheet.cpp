#include<stdexcept>
#include "Spreadsheet.h"

Spreadsheet::Spreadsheet(size_t width, size_t height):
	Id(sCounter++), mWidth(std::min(width, kMaxWidth)), mHeight(std::min(height,kMaxHeight))
{
	mCells = new SpreadsheetCell * [mWidth];
	for (size_t i = 0; i < mWidth; ++i) {
		mCells[i] = new SpreadsheetCell[mHeight];
	}
}

Spreadsheet::~Spreadsheet()
{
	cleanup();
}

Spreadsheet::Spreadsheet(const Spreadsheet& src):
	Spreadsheet(src.mWidth,src.mHeight)//���ӻ�����
{
	for (size_t i = 0; i < mWidth; ++i) {
		for (size_t j = 0; j < mHeight; ++i) {
			mCells[i][j] = src.mCells[i][j];
		}
	}
}

Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
	if (this == &rhs)
		return *this;
	//�̷��� �ϸ� �߰��� �ͼ����� �߻��ص� ��ü�� ������ �ʴ´�
	Spreadsheet temp(rhs);
	swap(*this, temp);
	return *this;
}

Spreadsheet::Spreadsheet(Spreadsheet&& src) noexcept
	:Spreadsheet()
{
	swap(*this, src);
}

Spreadsheet& Spreadsheet::operator=(Spreadsheet&& rhs) noexcept
{
	if (this == &rhs) return *this;

	Spreadsheet temp(std::move(rhs));
	swap(*this, temp);
	return *this;
}

void Spreadsheet::setCellAt(size_t x, size_t y, const SpreadsheetCell& cell)
{
	verifyCoordinate(x, y);
	mCells[x][y] = cell;
}

SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y)
{
	verifyCoordinate(x, y);
	return mCells[x][y];
}

void Spreadsheet::cleanup() noexcept
{
	for (size_t i = 0; i < mWidth; ++i)
		delete[] mCells[i];

	delete[] mCells;
	mCells = nullptr;
	mWidth = mHeight = 0;
}

const SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y) const
{
	verifyCoordinate(x, y);
	return mCells[x][y];
}
SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y)
{
	return const_cast<SpreadsheetCell&>(std::as_const(*this).getCellAt(x, y));
}

void Spreadsheet::verifyCoordinate(size_t x, size_t y) const
{
	if (x >= mWidth || y > mHeight)
		throw std::out_of_range("");
}
void swap(Spreadsheet& first, Spreadsheet& second)noexcept
{
	using std::swap;

	swap(first.mWidth, second.mWidth);
	swap(first.mHeight, second.mHeight);
	swap(first.mCells, second.mCells);
}