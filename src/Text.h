/**
\file
\brief ���� � ����������� ������ Text, ������������� ��� ���������� ������ �� �����

*/
#ifndef READ_DATA_H
#define READ_DATA_H

#include "Headers.h"
#include <algorithm>
#define DELIMITERS L"!?.,;:/*-+\n\t 1234567890'><=_)([]{}\"��" ///<������ � �������������
#define LANGUAGE "russian" ///<����, � ������� �������� ���������
#define EMPTY_STRING L"" ///<������ ������

/**
Enum. ������������ ������� ���������� ������ �� ������
*/
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
	const wchar_t* separators = DELIMITERS; ///<������ ������������ ������
	wstring classname; ///<��� ������ ������ ��� ���������
	vector<wstring> data; ///<������ ���� �� ������ 
public:
	/**
	��������� ������ ���� ������� �� ������
	\param line ������
	*/
	void updateData(wstring line);
public:

	/**
	������������ ������ �� ���������� �����
	\param filename ��� �����
	\param classname ��� ������, � �������� ����������� �����
	\return true ���� ����� �������� �����������, ����� false
	*/
	bool loadData(wstring filename, wstring& classname);

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

#endif // TEXT_H