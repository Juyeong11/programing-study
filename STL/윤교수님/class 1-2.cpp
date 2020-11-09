#include<iostream>
#include<vector>
using namespace std;

//생성 소멸 복사 복사할당 이동생성 이동할당
int class_count = 1;
class Model {
private:
	char* data;
	size_t size;
	int class_number = class_count;
public:
	Model() :data(nullptr), size(0) {
		class_count++;

		cout << class_number <<": 기본 생성자 호출" << endl;

	};
	Model(size_t Size) :data(new char[Size]), size(Size) {//문자열 길이와 배열의 크기가 다르다??
		class_count++;

		cout << class_number << ": 생성자 호출" << endl;
	};
	~Model()
	{
		cout << class_number << ": 소멸자 호출" << endl;


		if (data)
			delete[] data;
	}
	bool operator==(const Model& t) const
	{
		if (t.data)
			return !strcmp(t.data, this->data);
		else
			return false;
	}
	/*
	복사, 할당(대입)의 차이 -> 선언과 동시에 객체를 할당하는지 이미 존재하는 객체에 새 객체를 복사하는지 차이
	https://woo-dev.tistory.com/78
	*/
	Model(const Model& t)
	{
		cout << class_number << ": 복사생성자 호출" << endl;
		
		data = new char[strlen(t.data)+1];
		strcpy_s(data, strlen(t.data) + 1, t.data);
		size = t.size;
	}
	Model& operator=(Model& t)
	{
		cout << class_number << ": 대입연산사(복사할당) 호출" << endl;


		//**생성자로 객체를 만든다음 그 객체를 반환하면 안되나??
		if (t == *this) return *this;
		
		if (data)
			delete[] data;
		
		
		data = new char[strlen(t.data) + 1];
		strcpy_s(data, strlen(t.data) + 1, t.data);
		size = t.size;
		return *this;
	}
	/*
		이동 생성자와 이동 대입 연산자는 원본 객체에 있는 데이터 멤버를 새 객체로 이동
	*/
	void moveFrom(Model& src) noexcept //넘어오는 객체의 맴버 변수가 객체라면 std::move로 이동 시켜야 한다. 우측값 래퍼런스 매개변수는 타입이 우측값 래퍼선스인거지 매개변수 자체는 이름이 있기 때문
	{
		data = src.data;
		size = src.size;

		src.data = nullptr;
		src.size = 0;
	}
	Model(Model&& src) noexcept//이동 생성자
	{
		class_count++;
		cout << class_number << ": 이동생성자 호출" << endl;

		moveFrom(src);//-> 이렇게 하면 데이터 멤버가 추가 될 경우 수정해야하는 함수가 하나 늘게 되는 것이다.-> 기본 생성자와 swap함수만 구현해서 this와 바꾸는 것을 생각해보자(효율성은 떨어지지만 코드가 줄고 버그 발생확률을 낮출 수 있다.)
	}
	Model& operator=(Model&& rhs) noexcept//이동 대입 생성자
	{
		cout << class_number << ": 이동 대입 연산자 호출" << endl;


		if (this == &rhs)
			return *this;

		delete[] data;
		data = nullptr;                  
		size = 0;
		
		moveFrom(rhs);

		return *this;
	}

};

Model create_Model(int size)
{
	return Model(size);
}
int main()
{
	/*
	Model a{ 1000 };
	Model b = move(a);
	//Model b = static_cast<Model&&>(a) 위 코드는 이와 동일함 -> 좌측값을 우측값으로 바꿔 준다.
	*/
	vector<Model> vec;

	for (int i = 0; i < 2; ++i)
	{
		cout << "생성함 : " << i << endl;
		vec.push_back(Model(1));
		cout << endl;
	}
	
	Model s(2);
	s = create_Model(1);

	Model s2=s;
	//s2 = s;
	return 0;
}

/*
이동 생성자와 이동 대입연산자는 원본 객체에 있는 데이터 멤버를 새 객체로 이동시킨다 -> 객체의 얕은 복사와 비슷하다고 생각하면 된다.

좌측값-> 변수처럼 이름과 주소를 가진 대상 
우측값-> 리터럴, 임시 객체, 값 좌측값이 아닌 대상
다
좌측값에 레퍼런스가 있듯이 우측값에도 레퍼런스가 있다(우측값이 임시 객체일 경우)
-> 우측값 레퍼런스는 임시 객체에 대해 적용할 함수를 컴파일러가 선택하기 위한 용도로 사용한다. 

우측값 레퍼런스로 구현하면 크기가 큰 값을 복사하는 연산이 나오더라도 컴파일러는 이값이 나중에 삭제될 임시 객체라는 점을 이용하여 그 값에 우측값에 대한 포인터를 복사하는 방식으로 실행할 수 있다.

이동의미론 -> c++11 부터 우측값 레퍼런스를 사용할 수 있게 된다
*/