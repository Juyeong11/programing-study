#pragma once
#include<string>
namespace Records {
	const int kDefaultStartingSalary = 30000;//상수 이름을 정할 때 상수를 의미하는 독일어 Konstant의 첫 글자인 k를 상수 앞에 붙이는 관례를 따른다.

	class Employee
	{
	public:
		Employee() = default;
		Employee(const std::string& firstName, const std::string& lastName);

		void promote(int raiseAmount = 1000);
		void demote(int demeritAmount = 1000);
		void hire();
		void fire();
		void display() const;

		void setFirstName(const std::string& firstName);
		const std::string& getFirstName() const;

		void setLastName(const std::string& lastName);
		const std::string& getLastName()const;

		void setEmployeeNumber(int employeeNumber);
		int getEmployeeNumber()const;

		void setSalary(int newSalary);
		int getSalary()const;
		bool isHired()const;

	private:
		std::string mFirstName;
		std::string mLastName;
		int mEmployeeNamber = -1;
		int mSalary = kDefaultStartingSalary;
		bool mHired = false;
	};

}