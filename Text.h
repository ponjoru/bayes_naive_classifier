#ifndef READ_DATA_H
#define READ_DATA_H

#include "Headers.h"

#define DELIMITERS L"!?.,;/*-+\n\t "
#define LANGUAGE "russian"
#define EMPTY_STRING L""

///������������ ������� ���������� ������ �� ������
enum mode 
{
TRAINING_MODE, ///<����� � ���������� �������
EXECUTION_MODE, ///<����� ��� �������������
};
using namespace std;

/**
\brief ����� ������ ������
����� ����������� ������ ������ ������������� � ������� ��������� ������
*/
class Text 
{
private:
	const wchar_t *separators = DELIMITERS; ///<������ ������������ ������
	wstring classname; ///<��� ������ ������ ��� ���������
	vector<wstring> data; ///<������ ���� �� ������ 
private:
	/**
	��������� ������ ���� ������� �� ������
	\param line ������
	*/
	void updateData(wstring line);
public:
	/**
	������������ ������ �� ���������� �����
	\param filename ��� �����
	\param mode_ ����� ������ (��������� ����� ��� ����� ��� �������������)
	\return true ���� ����� �������� �����������, ����� false
	*/
	bool loadData(string filename, mode mode_);

	/**
	���������� ��� ������
	\return ��� ������
	*/
	wstring getClassName(void);

	/**
	���������� ������ ����
	\return ������ ����
	*/
	vector<wstring> getData(void);
};

#pragma once

#endif 