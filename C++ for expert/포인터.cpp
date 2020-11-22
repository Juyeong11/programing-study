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
			int i = 7; // �ڵ� ���� ���ÿ� ����-> ���α׷��� ���� �帧�� �� ������ ����� ������ ����� �޸𸮰� �ڵ����� 

			int* ptr = new int;// ptr������ ������ ���ÿ� ������, �� ������ ����Ű�� ���� ���� �ִ�. ������ ���� ������ �����̱� ������ �����̳� ���� ����
			delete ptr;
			ptr = nullptr;

			int** handle = nullptr;//
			handle = new int*;
			*handle = new int;// ������(����!!!)�� ���ð� ���� ���ÿ� �����ϴ� ����̴�.

			delete* handle;
			*handle = nullptr;
			delete handle;
			handle = nullptr;
		}
		
		{//malloc
			Foo* myFoo = (Foo*)malloc(sizeof(Foo));//��ü ũ�⸸ŭ�� �޸𸮰����� Ȯ���Ѵ�.-> �޸𸮰����� ���� �� ��ü��� �� �� ����.
			Foo* myOtherFoo = new Foo();//��ü�� ũ�⸸ŭ �޸𸮰����� Ȯ���ϰ� ��ü�� �����ڵ� ȣ�����ش�.

			free(myFoo);//���� ����ϴ�.
			myFoo = nullptr;
			delete myOtherFoo;
			myOtherFoo = nullptr;
		}
		{//�޸� �Ҵ翡 �����Ѱ��-> �޸𸮰� �����Ѱ�츸 new�� �����Ѵ�. �̷���� ���α׷��� ����ǵ��� �ϴ� ����� �ִ�(14��)
			int* ptr = new(nothrow) int;//���ܸ� �߻� ��Ű�� �ʰ� nullptr�� ��ȯ�Ѵ�.
			delete ptr;
			ptr = nullptr;
		}
		
	}

	{//�迭
		{
			int myArray[5];//���ÿ� ���� -> ������ �ð��� ũ�Ⱑ �����ȴ�.
			int* myArrayptr = new int[5];//���� ����-> ����ð��� ũ�⸦ ���� �� �ִٴ� ������ �ִ� || �̰��� �Ҵ�ǰ� ���� ũ�Ⱑ ������ �ʱ� ������ ���� �迭�� �ƴϴ�( �������� �Ҵ�� �迭�̴�.)
			delete[] myArrayptr;
			myArrayptr = nullptr;
			/*
			C++�� relloc()�̶�� �Լ��� �����Ѵ�
			�� �Լ��� ���� ������ ũ�⿡ �°� �޸� ����� ���� �Ҵ��ϴ� ������� �迭�� ũ�⸦ �������� �����Ѵ�.
			������ C++���� ���� ��ü�� ���� ��Ʈ ���� ���� �۾��� ���� �ʱ� ������ C++������ ���� ������� ����.
			*/
		}
		{//��ü �迭
			Foo* myClassArray = new Foo[5];//�� ��ü���� �����μ�(����Ʈ) �����ڸ� ȣ�����ش�.-> ##����Ʈ�����ڸ� ���Ƴ�����???
			delete[] myClassArray;
			myClassArray = nullptr;
			
			const int size = 4;
			Foo** myClassPtrArray = new Foo * [size];//��ü ������ �迭
			
			for (size_t i = 0; i < size; ++i) { myClassPtrArray[i] = new Foo(); }//�� ��ü �����͸��� ��ü�� ��������� �Ѵ�.

			for (size_t i = 0; i < size; ++i) { delete myClassPtrArray[i]; }//�Ҵ�� ��ü�� ���� ���� �迭�� ���� �����ؾ��Ѵ�.

			delete[] myClassPtrArray;
			myClassArray = nullptr;
		}
	}
	{//������ �ٷ��
		//���� ĳ������ �Ϸ��� �����Ϳ� ĳ���� ����� ���� �����Ͱ� ����Ű�� ��ü�� ���� ��� ���迡 �ִٸ� ������ ������ �߻����� �ʴ´�.
		//��Ӱ��迡 �ִ� ��󳢸� ĳ������ ���� ���� ĳ������ ����ϴ� ���� �� �����ϴ�.
		{
			//�����͸� �Ű������� ����
			size_t arrSize = 4;
			int* heapArray = new int[arrSize] {1, 5, 3, 4};
			doubleInts(heapArray, arrSize);
			delete[] heapArray;
			heapArray = nullptr;

			//�迭�� �Ű������� ����
			int stackArray[] = { 5,7,9,11 };
			arrSize = std::size(stackArray);
			doubleInts(stackArray, arrSize);
			doubleInts(&stackArray[0], arrSize);

			/*
			���ø��� �̿��Ͽ� ���ù迭�� ũ�⸦ �����Ϸ��� �˾Ƴ����� �� ���� �ִ�.
			template<size_t N>
			void doubleInt(int (&theArray)[N])
			������� ������ ����� ���� ����

			��� �迭�� �����ͷ� ���������� ��� �����Ͱ� �迭�� �ƴϴ�.
			*/

			//�迭 �������� ������ �迭�� �����ͷε� ������ �� �ִ�. �����Ϸ��� �Լ��� �����ϴ� �迭�� �׻� �����ͷ� ����Ѵ�.
		}
		{//�ο췹�� �޸𸮿���
			int* myArray = new int[8];
			*(myArray + 2) = 33;//myArray[2] = 33;
			delete[] myArray;

			const wchar_t* mystring = L"Hello, World";//��Ʈ�����ͷ��� L�� �ٿ��ָ� ���̵� ��Ƽ�� ���ͷ�
			*(mystring + 7); // �Լ��� �����Ҷ� �Ϻκ� ���� ���ޤ� �� �� �ִ�.
		}
		{//����Ʈ������
			/*
			unique_ptr->; ���� ������ ������
			shared_ptr->; �ٸ���̵� ���¸� ���۷��� ī�������� ������ ���� ������ ������
			*/
			/*unique*/
			std::unique_ptr<Foo> mySimplePtr = make_unique<Foo>();// make_unique<Foo>(������ �μ��ڸ�)�̷��� ����Ѵ�.
			std::unique_ptr<Foo> mySimpleptr(new Foo());//���ſ��� Foo�����ڿ��� �ͼ����� �߻��ϸ� �޸𸮰� ������ ������ �־����� ���� �ذ��� ������ �������� �����ؼ� make_unique�Լ��� �������

			mySimplePtr.get();// Foo* �� ��ȯ �ȴ�
			mySimpleptr.reset();//���������� ����
			
			Foo* foo = mySimplePtr.release();//�������� �Ѱ��ش� ������ �����ؾߵ�
			delete foo;
			foo = nullptr;
			//std::move()�� �ٸ� ������ �̵��� �� �ִ�.
			//unique_ptr<int, decltype(free)*> myInt(malloc_int, free); decltype(free)* delete ���� free�� �����ϵ��� ��������

			/*shared_ptr*/
			//release�� �������� �ʴ´�. �����ϴ� ptr������ use_count�� �� �� �ִ�.
			
			//���α׷��� ���� �� �ִ� ���ҽ��� �����Ѵٰ� �ؼ� ��ü �ϳ��� shared_ptr �� ���� ����Ű������ ���纻�� ����� ����ؾ��Ѵ�. -> ���� �̰�
			Foo* fooptr = new Foo();
			shared_ptr<Foo> smartptr1(fooptr);
			shared_ptr<Foo> smartptr2(fooptr);
			
			auto smartPtr1 = make_shared<Foo>();
			shared_ptr<Foo> smartPtr2(smartPtr1);

			//�ٸ����
			//shared_ptr�� ��ü�� ����Ű�� ���ÿ� �� ��ü�� �ɹ��� ����Ű�� �� �� �ִ�.
			//���⼭ �� ptr�� ��� ������ ���� Foo��ü�� �����ȴ�.
			auto foo1 = make_shared<Foo>(42);
			auto aliasing = shared_ptr<int>(foo1, &foo->mdata);

			{/*weak_ptr*/
				//shared_ptr�� ����Ű�� ���ҽ��� ���۷����� �����ϴ� �� ���ȴ�.
				//��ȯ���� �߻� ���ɼ� ����
				auto sharedFoo = make_shared<Foo>();
				weak_ptr<Foo> weakFoo(sharedFoo);
			}
			//ǥ�� ����Ʈ �����͵��� �̵� �ǹ̷��� �����Ѵ�. �Լ����� ����Ʈ �����͸� �����ϴ� ������ �ſ� ȿ�������� ó���� �� �ִٴ� ��
			
			/*
			�ͽ��� Ŭ������ std::enable_shared_from_this�� �̿��ϸ� ��ü�� �޼��忡�� �����͸� �����ϰ� ������ �� �ִ�.
			class Foo: public enable_shared_from_this<Foo>{
				public:
					shared_ptr<Foo> getPointer(){
						return shared_from_this();-> ��ü�� �������� �����ϴ� shared_ptr�� �����Ѵ�
						 or
						 weak_from_this()->��ü�� �������� �����ϴ� weak_ptr�� �����Ѵ�.
					}
			}

			auto ptr�� ���������ϱ� �������� ǥ�������̳ʾȿ��� ����� �۵����Ѵ�.
			*/
		}
	}
}