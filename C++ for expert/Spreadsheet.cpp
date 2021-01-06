#include<stdexcept>
#include "Spreadsheet.h"

Spreadsheet::Spreadsheet(const SpreadsheetApplication& theApp, size_t width, size_t height)
{
	mImpl = std::make_unique<Impl>(theApp, width, height);
}



Spreadsheet::Spreadsheet(const Spreadsheet& src)
{
	mImpl = std::make_unique<Impl>(*src.mImpl);
}

Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
	*mImpl = *rhs.mImpl;
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
	mImpl->setCellAt(x, y, cell);
}

SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y)const
{
	return mImpl->getCellAt(x, y);
}
/*구현 분리
void Spreadsheet::cleanup() noexcept
{
	for (size_t i = 0; i < mWidth; ++i)
		delete[] mCells[i];

	delete[] mCells;
	mCells = nullptr;
	mWidth = mHeight = 0;
}
*/
/*
const SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y) const
{
	verifyCoordinate(x, y);
	return mCells[x][y];
}
*/
/*
SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y)
{
	return const_cast<SpreadsheetCell&>(std::as_const(*this).getCellAt(x, y));
}
*/
/*구현부분 분리
void Spreadsheet::verifyCoordinate(size_t x, size_t y) const
{
	if (x >= mWidth || y > mHeight)
		throw std::out_of_range("");
}
*/

void swap(Spreadsheet& first, Spreadsheet& second)noexcept
{
	using std::swap;

	swap(first.mImpl, second.mImpl);
}
/// <summary>
/// /////////////////////////////////////////
/// </summary>
/// <param name="Impl"></param>
/// <returns></returns>

void Spreadsheet::Impl::swap(Impl& other)noexcept
{
	using std::swap;
	swap(mWidth, other.mWidth);
	swap(mHeight, other.mHeight);
	swap(mCells, other.mCells);
}
void Spreadsheet::Impl::verifyCoordinate(size_t x, size_t y)const
{
	if (x >= mWidth || y > mHeight)
		throw std::out_of_range("");
}
Spreadsheet::Impl::Impl(const SpreadsheetApplication& theApp, size_t width, size_t height):
	mTheApp(theApp),mWidth(width),mHeight(height)
{
	mCells = new SpreadsheetCell * [mWidth];
	for (size_t i = 0; i < mWidth; ++i) {
		mCells[i] = new SpreadsheetCell[mHeight];
	}
}
Spreadsheet::Impl::Impl(const Impl& src):
	Impl(src.mTheApp,src.mWidth,src.mHeight)
{
	for (size_t i = 0; i < mWidth; ++i) {
		for (size_t j = 0; j < mHeight; ++i) {
			mCells[i][j] = src.mCells[i][j];
		}
	}
}
Spreadsheet::Impl& Spreadsheet::Impl::operator=(const Impl& rhs)
{
	if (this == &rhs)
		return *this;
	//이렇게 하면 중간에 익셉션이 발생해도 객체는 변하지 않는다

	Impl temp(rhs);
	swap(temp);
	return *this;
}
void Spreadsheet::Impl::setCellAt(size_t x, size_t y, const SpreadsheetCell& cell)
{
	verifyCoordinate(x, y);
	mCells[x][y] = cell;
}
SpreadsheetCell& Spreadsheet::Impl::getCellAt(size_t x, size_t y)
{
	verifyCoordinate(x, y);
	return mCells[x][y];
}