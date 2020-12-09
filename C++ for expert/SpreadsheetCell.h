#include<string>
#include<string_view>
//문자열 타입 string을 반환하는 함수
//std::string f();
//
//std::string_view s1 = f();
//NG: 함수 반환 값(임시 문자열 오브젝트)는 파괴 되기 때문
//    이 시점에서 s1은 덩글링 뷰가 된다
//
//auto&& s2 = f();
//OK: 함수 반환 값(임시 문자열 오브젝트) 우측 값 참조 타입으로 넘기면
//    이 생존 기간은 변수 s2의 스코프가 끝날 때까지 연장 된다.
class SpreadsheetCell {
public:
	SpreadsheetCell() = default;//이렇게 해주면 따로 디폴트 생성자를 작성하지 않아도 된다
	//SpreadsheetCell() = delete;//명시적으로 삭제해줄수 도 있다.
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(std::string_view initialValue);
	//SpreadsheetCell(const SpreadsheetCell& src);
	SpreadsheetCell& operator=(const SpreadsheetCell& rhs);

	void set(double inValue);
	void set(std::string_view inString);
	
	double getValue()const //인라인함수
	{
		mNumAccesses++;
		return mValue;
	}
	std::string getString() const
	{
		mNumAccesses++;
		return doubleToString(mValue);
	}
private:
	std::string doubleToString(double inValue)const;
	double stringToDouble(std::string_view inString) const;
	double mValue = 0;
	mutable size_t mNumAccesses = 0;
};