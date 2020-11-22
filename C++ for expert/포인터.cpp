#include<iostream>

using namespace std;

class Foo {
private:
	//Foo() {};
	
public:
	int mdata;
	Foo() {};
	Foo(int i):mdata(i) {};
};
void doubleInts(int* theArray, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		theArray[i] *= 2;
}

int main()
{
	{
		{
			int i = 7; // 자동 변수 스택에 저장-> 프로그램의 실행 흐름이 이 변수가 선언된 범위를 벗어나면 메모리가 자동해제 

			int* ptr = new int;// ptr변수는 여전히 스택에 있지만, 이 변수가 가리키는 값은 힙에 있다. 포인터 역시 일종의 변수이기 때문에 스택이나 힙에 존재
			delete ptr;
			ptr = nullptr;

			int** handle = nullptr;//
			handle = new int*;
			*handle = new int;// 포인터(변수!!!)가 스택과 힙에 동시에 존재하는 경우이다.

			delete* handle;
			*handle = nullptr;
			delete handle;
			handle = nullptr;
		}
		
		{//malloc
			Foo* myFoo = (Foo*)malloc(sizeof(Foo));//객체 크기만큼의 메모리공간을 확보한다.-> 메모리공간만 있을 뿐 객체라고 볼 수 없다.
			Foo* myOtherFoo = new Foo();//객체의 크기만큼 메모리공간을 확보하고 객체의 생성자도 호출해준다.

			free(myFoo);//위와 비슷하다.
			myFoo = nullptr;
			delete myOtherFoo;
			myOtherFoo = nullptr;
		}
		{//메모리 할당에 실패한경우-> 메모리가 부족한경우만 new가 실패한다. 이런경우 프로그램이 실행되도록 하는 방법이 있다(14장)
			int* ptr = new(nothrow) int;//예외를 발생 시키지 않고 nullptr을 반환한다.
			delete ptr;
			ptr = nullptr;
		}
		
	}

	{//배열
		{
			int myArray[5];//스택에 생성 -> 컴파일 시간에 크기가 결정된다.
			int* myArrayptr = new int[5];//힙에 생성-> 실행시간에 크기를 정할 수 있다는 장점이 있다 || 이것은 할당되고 나면 크기가 변하지 않기 때문에 동적 배열이 아니다( 동적으로 할당된 배열이다.)
			delete[] myArrayptr;
			myArrayptr = nullptr;
			/*
			C++는 relloc()이라는 함수도 지원한다
			이 함수는 새로 지정한 크기에 맞게 메모리 블록을 새로 할당하는 방식으로 배열의 크기를 동적으로 조절한다.
			하지만 C++에서 만든 객체의 경우는 비트 단위 복사 작업에 맞지 않기 때문에 C++에서는 절대 사용하지 말자.
			*/
		}
		{//객체 배열
			Foo* myClassArray = new Foo[5];//각 객체마다 제로인수(디폴트) 생성자를 호출해준다.-> ##디폴트생성자를 막아놓으면???
			delete[] myClassArray;
			myClassArray = nullptr;
			
			const int size = 4;
			Foo** myClassPtrArray = new Foo * [size];//객체 포인터 배열
			
			for (size_t i = 0; i < size; ++i) { myClassPtrArray[i] = new Foo(); }//각 객체 포인터마다 객체를 생성해줘야 한다.

			for (size_t i = 0; i < size; ++i) { delete myClassPtrArray[i]; }//할당된 객체를 삭제 하위 배열을 먼저 해제해야한다.

			delete[] myClassPtrArray;
			myClassArray = nullptr;
		}
	}
	{//포인터 다루기
		//정적 캐스팅을 하려는 포인터와 캐스팅 결과에 대한 포인터가 가리키는 객체가 서로 상속 관계에 있다면 컴파일 에러가 발생하지 않는다.
		//상속관계에 있는 대상끼리 캐스팅할 때는 동적 캐스팅을 사용하는 것이 더 안전하다.
		{
			//포인터를 매개변수로 전달
			size_t arrSize = 4;
			int* heapArray = new int[arrSize] {1, 5, 3, 4};
			doubleInts(heapArray, arrSize);
			delete[] heapArray;
			heapArray = nullptr;

			//배열을 매개변수로 전달
			int stackArray[] = { 5,7,9,11 };
			arrSize = std::size(stackArray);
			doubleInts(stackArray, arrSize);
			doubleInts(&stackArray[0], arrSize);

			/*
			템플릿을 이용하여 스택배열의 크기를 컴파일러가 알아내도록 할 수도 있다.
			template<size_t N>
			void doubleInt(int (&theArray)[N])
			깔끔하지 않으니 사용은 하지 말자

			모든 배열은 포인터로 참조되지만 모든 포인터가 배열은 아니다.
			*/

			//배열 문법으로 선언한 배열은 포인터로도 접급할 수 있다. 컴파일러는 함수로 전달하는 배열을 항상 포인터로 취급한다.
		}
		{//로우레벨 메모리연산
			int* myArray = new int[8];
			*(myArray + 2) = 33;//myArray[2] = 33;
			delete[] myArray;

			const wchar_t* mystring = L"Hello, World";//스트링리터럴에 L을 붙여주면 와이드 스티링 리터럴
			*(mystring + 7); // 함수에 전달할때 일부분 만을 전달ㅇ 할 수 있다.
		}
		{//스마트포인터
			/*
			unique_ptr->; 고유 소유권 포인터
			shared_ptr->; 앨리어싱된 상태를 래퍼런스 카운팅으로 구현한 공유 소유권 포인터
			*/
			/*unique*/
			std::unique_ptr<Foo> mySimplePtr = make_unique<Foo>();// make_unique<Foo>(생성자 인수자리)이렇게 사용한다.
			std::unique_ptr<Foo> mySimpleptr(new Foo());//과거에는 Foo생성자에서 익셉션이 발생하면 메모리가 누수될 위험이 있었지만 현재 해결됬다 하지만 가독성을 생각해서 make_unique함수를 사용하자

			mySimplePtr.get();// Foo* 가 반환 된다
			mySimpleptr.reset();//내부포인터 해제
			
			Foo* foo = mySimplePtr.release();//소유권을 넘겨준다 해제도 직접해야됨
			delete foo;
			foo = nullptr;
			//std::move()로 다른 곳으로 이동할 수 있다.
			//unique_ptr<int, decltype(free)*> myInt(malloc_int, free); decltype(free)* delete 말고 free로 해제하도록 설정가능

			/*shared_ptr*/
			//release를 지원하지 않는다. 공유하는 ptr갯수는 use_count로 알 수 있다.
			
			//프로그램이 죽을 수 있다 리소스를 공유한다고 해서 객체 하나를 shared_ptr 두 개로 가르키지말고 복사본을 만들어 사용해야한다. -> 뭔데 이거
			Foo* fooptr = new Foo();
			shared_ptr<Foo> smartptr1(fooptr);
			shared_ptr<Foo> smartptr2(fooptr);
			
			auto smartPtr1 = make_shared<Foo>();
			shared_ptr<Foo> smartPtr2(smartPtr1);

			//앨리어싱
			//shared_ptr이 객체를 가르키는 동시에 그 객체의 맴버도 가리키게 할 수 있다.
			//여기서 두 ptr이 모두 삭제될 때만 Foo객체가 삭제된다.
			auto foo1 = make_shared<Foo>(42);
			auto aliasing = shared_ptr<int>(foo1, &foo->mdata);

			{/*weak_ptr*/
				//shared_ptr가 가르키는 리소스의 레퍼런스를 관리하는 데 사용된다.
				//순환참조 발생 가능성 제거
				auto sharedFoo = make_shared<Foo>();
				weak_ptr<Foo> weakFoo(sharedFoo);
			}
			//표준 스마트 포인터들은 이동 의미론을 지원한다. 함수에서 스마트 포인터를 리턴하는 과정을 매우 효율적으로 처리할 수 있다는 뜻
			
			/*
			믹스인 클래스인 std::enable_shared_from_this를 이용하면 객체의 메서드에서 포인터를 안전하게 리턴할 수 있다.
			class Foo: public enable_shared_from_this<Foo>{
				public:
					shared_ptr<Foo> getPointer(){
						return shared_from_this();-> 객체의 소유권을 공유하는 shared_ptr을 리턴한다
						 or
						 weak_from_this()->객체의 소유권을 추적하는 weak_ptr을 리턴한다.
					}
			}

			auto ptr은 삭제됬으니까 쓰지말자 표준컨테이너안에서 제대로 작동안한다.
			*/
		}
	}
}