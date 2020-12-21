#pragma once
#include<cstddef>
#include"SpreadsheetCell.h"

class SpreadsheetApplication;//포워드 선언 /순환참조 방지?

class Spreadsheet
{
public:
	class Cell;
	static const size_t kMaxHeight = 100;
	static const size_t kMaxWidth = 100;

	 //기본 매개변수는 오른쪽 부터 채워 나가야 된다.
	//Spreadsheet(size_t width = kMaxWidth, size_t height = kMaxHeight,const SpreadsheetApplication& theApp);//둘다 디폴트 인수가 있으면 기본생성자와 구분이 안가 컴파일 오류발생
	Spreadsheet(size_t width, size_t height ,const SpreadsheetApplication& theApp);//둘다 디폴트 인수가 있으면 기본생성자와 구분이 안가 컴파일 오류발생

	//Spreadsheet(const Spreadsheet& src) = delete;
	~Spreadsheet();
	Spreadsheet(const Spreadsheet& src);
	Spreadsheet& operator=(const Spreadsheet& rhs);
	friend void swap(Spreadsheet& first, Spreadsheet& second)noexcept;//클래스 멤버로 만들어되 되지만 표준라이브러리 알고리즘에서 활용할 수 있게 비멤버로 만든다.

	Spreadsheet(Spreadsheet&& src)noexcept;
	Spreadsheet& operator=(Spreadsheet&& rhs)noexcept;

	void setCellAt(size_t x, size_t y, const SpreadsheetCell& cell);
	SpreadsheetCell& getCellAt(size_t x, size_t y);

	SpreadsheetCell& getCellAt(size_t x, size_t y);//const의 여부에 따라 오버로딩 할 수 있다.
	const SpreadsheetCell& getCellAt(size_t x, size_t y)const;//구현코드가 비슷한경우는 const_cast패턴으로 코드 중복을 피할 수 있다.


private:
	//static size_t sCounter = 0;// 오류난다 소스파일에서 값을 초기화 해야한다(기본적으로는 0, nullptr로 초기화된다.//Spreadsheet::를 사용해주어야 한다, 함수나 메서드에 속하지 않기 때문
	static inline size_t sCounter = 0;//inline붙이면 가능
	size_t Id = 0;

	const SpreadsheetApplication& mTheApp;

	Spreadsheet() = default;
	void cleanup()noexcept;
	//void moveFrom(Spreadsheet& src)noexcept;

	void verifyCoordinate(size_t x, size_t y) const;
	size_t mWidth = 0;
	size_t mHeight = 0;
	SpreadsheetCell** mCells = nullptr;
};
class Spreadsheet::Cell
{//중첩클래스
public:
	Cell() = default;
};