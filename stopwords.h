/**
\file
\brief ���� � ����������� ������ StopWords

������ ���� �������� ���������� ������, �������������
��� ������������� ��������� ������, � ������ �������� ���� ����.
*/
#ifndef STOP_WORDS_H
#define STOP_WORDS_H
#include "Headers.h"
/**
\brief ��� �����, � ������� �������� ���� - �����
*/
#define STOP_WORDS_FILE_NAME_RUS "stopwords.txt"
using namespace std;
/**
@brief �������� ���� - ���� �� ��������� ������.
*/
/**
\class StopWords
����� ��� �������� ���� - ���� �� ������� ���� ��������� ������.<br>
�������� ���� ���� ������, ����������� �� ��������� � ��� ������.
*/
class StopWords
{
private:
	multimap<wchar_t, wstring> mapWords;///< ������ ������� <������ ������ ���� - �����, ���� - �����>.<br>��� �������� ������ �����
public:
		/** ����������� �� ���������. <br>������ ��������� ���������� ���� - ����*/
		StopWords();
		
		/**  ����� ��� ��������� ���� - ����� �� ����� � ������� mapWords
		\return True, ���� ���������� ��������� �������, ����� False
		*/
		bool readFile();

		/** ����� ��� ������ ����� �� ��������� ������ � ������� ���� - ���� mapWords
		\param[in] word ����� �� ��������� ������
		\return True, ���� word �������� ���� - ������, ����� False
		*/
		bool findWord(wstring word);

		/** ����� ��� �������� ���� ���� - ����, ������� ����������� � �������� ������.<br>
		������ ������ ���������� findWord(wstring word).<br> ���� �� ������ true, �� ����� ��������� �� ������� ���� ����, ����� ������ �������� ������������
		\param[in,out] words - ��������� �� ������ ���� ���� �� ��������� ������
		*/
		void removeWord(vector<wstring>* words);
};
#pragma once
#endif // STOP_WORDS_H