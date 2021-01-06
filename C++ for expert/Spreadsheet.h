#pragma once
#include<cstddef>
#include<memory>
#include"SpreadsheetCell.h"

class SpreadsheetApplication;//������ ���� /��ȯ���� ����?

class Spreadsheet
{
public:
	class Cell;
	static const size_t kMaxHeight = 100;
	static const size_t kMaxWidth = 100;

	 //�⺻ �Ű������� ������ ���� ä�� ������ �ȴ�.
	//Spreadsheet(size_t width = kMaxWidth, size_t height = kMaxHeight,const SpreadsheetApplication& theApp);//�Ѵ� ����Ʈ �μ��� ������ �⺻�����ڿ� ������ �Ȱ� ������ �����߻�
	Spreadsheet(const SpreadsheetApplication& theApp , size_t width = kMaxWidth, size_t height = kMaxHeight);//�Ѵ� ����Ʈ �μ��� ������ �⺻�����ڿ� ������ �Ȱ� ������ �����߻�

	//Spreadsheet(const Spreadsheet& src) = delete;
	~Spreadsheet()= default;
	Spreadsheet(const Spreadsheet& src);
	Spreadsheet& operator=(const Spreadsheet& rhs);

	friend void swap(Spreadsheet& first, Spreadsheet& second)noexcept;//Ŭ���� ����� ������ ������ ǥ�ض��̺귯�� �˰��򿡼� Ȱ���� �� �ְ� ������ �����.

	Spreadsheet(Spreadsheet&& src)noexcept;
	Spreadsheet& operator=(Spreadsheet&& rhs)noexcept;

	void setCellAt(size_t x, size_t y, const SpreadsheetCell& cell);
	SpreadsheetCell& getCellAt(size_t x, size_t y)const ;

	//SpreadsheetCell& getCellAt(size_t x, size_t y)const;//const�� ���ο� ���� �����ε� �� �� �ִ�.
	//const SpreadsheetCell& getCellAt(size_t x, size_t y)const;//�����ڵ尡 ����Ѱ��� const_cast�������� �ڵ� �ߺ��� ���� �� �ִ�.


private:
	//static size_t sCounter = 0;// �������� �ҽ����Ͽ��� ���� �ʱ�ȭ �ؾ��Ѵ�(�⺻�����δ� 0, nullptr�� �ʱ�ȭ�ȴ�.//Spreadsheet::�� ������־�� �Ѵ�, �Լ��� �޼��忡 ������ �ʱ� ����
	static inline size_t sCounter = 0;//inline���̸� ����
	size_t Id = 0;

	

	Spreadsheet() = default;
	void cleanup()noexcept;
	//void moveFrom(Spreadsheet& src)noexcept;

	//���� �и�void verifyCoordinate(size_t x, size_t y) const;
	class Impl;
	std::unique_ptr<Impl> mImpl;
};


class Spreadsheet::Impl
{//��øŬ����
	size_t mWidth = 0;
	size_t mHeight = 0;
	SpreadsheetCell** mCells = nullptr;

	const SpreadsheetApplication& mTheApp;

public:
	Impl() = default;
	Impl(const SpreadsheetApplication& theApp, size_t width, size_t height);
	Impl(const Impl& src);
	Impl& operator=(const Impl& rhs);


	void setCellAt(size_t x, size_t y, const SpreadsheetCell& cell);
	SpreadsheetCell& getCellAt(size_t x, size_t y);

	void verifyCoordinate(size_t x, size_t y)const;
	void swap(Impl& other)noexcept;
};