#include<iostream>
#include<vector>
using namespace std;

//���� �Ҹ� ���� �����Ҵ� �̵����� �̵��Ҵ�
int class_count = 1;
class Model {
private:
	char* data;
	size_t size;
	int class_number = class_count;
public:
	Model() :data(nullptr), size(0) {
		class_count++;

		cout << class_number <<": �⺻ ������ ȣ��" << endl;

	};
	Model(size_t Size) :data(new char[Size]), size(Size) {//���ڿ� ���̿� �迭�� ũ�Ⱑ �ٸ���??
		class_count++;

		cout << class_number << ": ������ ȣ��" << endl;
	};
	~Model()
	{
		cout << class_number << ": �Ҹ��� ȣ��" << endl;


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
	����, �Ҵ�(����)�� ���� -> ����� ���ÿ� ��ü�� �Ҵ��ϴ��� �̹� �����ϴ� ��ü�� �� ��ü�� �����ϴ��� ����
	https://woo-dev.tistory.com/78
	*/
	Model(const Model& t)
	{
		cout << class_number << ": ��������� ȣ��" << endl;
		
		data = new char[strlen(t.data)+1];
		strcpy_s(data, strlen(t.data) + 1, t.data);
		size = t.size;
	}
	Model& operator=(Model& t)
	{
		cout << class_number << ": ���Կ����(�����Ҵ�) ȣ��" << endl;


		//**�����ڷ� ��ü�� ������� �� ��ü�� ��ȯ�ϸ� �ȵǳ�??
		if (t == *this) return *this;
		
		if (data)
			delete[] data;
		
		
		data = new char[strlen(t.data) + 1];
		strcpy_s(data, strlen(t.data) + 1, t.data);
		size = t.size;
		return *this;
	}
	/*
		�̵� �����ڿ� �̵� ���� �����ڴ� ���� ��ü�� �ִ� ������ ����� �� ��ü�� �̵�
	*/
	void moveFrom(Model& src) noexcept //�Ѿ���� ��ü�� �ɹ� ������ ��ü��� std::move�� �̵� ���Ѿ� �Ѵ�. ������ ���۷��� �Ű������� Ÿ���� ������ ���ۼ����ΰ��� �Ű����� ��ü�� �̸��� �ֱ� ����
	{
		data = src.data;
		size = src.size;

		src.data = nullptr;
		src.size = 0;
	}
	Model(Model&& src) noexcept//�̵� ������
	{
		class_count++;
		cout << class_number << ": �̵������� ȣ��" << endl;

		moveFrom(src);//-> �̷��� �ϸ� ������ ����� �߰� �� ��� �����ؾ��ϴ� �Լ��� �ϳ� �ð� �Ǵ� ���̴�.-> �⺻ �����ڿ� swap�Լ��� �����ؼ� this�� �ٲٴ� ���� �����غ���(ȿ������ ���������� �ڵ尡 �ٰ� ���� �߻�Ȯ���� ���� �� �ִ�.)
	}
	Model& operator=(Model&& rhs) noexcept//�̵� ���� ������
	{
		cout << class_number << ": �̵� ���� ������ ȣ��" << endl;


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
	//Model b = static_cast<Model&&>(a) �� �ڵ�� �̿� ������ -> �������� ���������� �ٲ� �ش�.
	*/
	vector<Model> vec;

	for (int i = 0; i < 2; ++i)
	{
		cout << "������ : " << i << endl;
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
�̵� �����ڿ� �̵� ���Կ����ڴ� ���� ��ü�� �ִ� ������ ����� �� ��ü�� �̵���Ų�� -> ��ü�� ���� ����� ����ϴٰ� �����ϸ� �ȴ�.

������-> ����ó�� �̸��� �ּҸ� ���� ��� 
������-> ���ͷ�, �ӽ� ��ü, �� �������� �ƴ� ���
��
�������� ���۷����� �ֵ��� ���������� ���۷����� �ִ�(�������� �ӽ� ��ü�� ���)
-> ������ ���۷����� �ӽ� ��ü�� ���� ������ �Լ��� �����Ϸ��� �����ϱ� ���� �뵵�� ����Ѵ�. 

������ ���۷����� �����ϸ� ũ�Ⱑ ū ���� �����ϴ� ������ �������� �����Ϸ��� �̰��� ���߿� ������ �ӽ� ��ü��� ���� �̿��Ͽ� �� ���� �������� ���� �����͸� �����ϴ� ������� ������ �� �ִ�.

�̵��ǹ̷� -> c++11 ���� ������ ���۷����� ����� �� �ְ� �ȴ�
*/