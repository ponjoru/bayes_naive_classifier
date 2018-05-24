/**
\file
\brief ������������ ���� � ��������� ������

������ ���� �������� ����������� ������, �������������
��� ������������� ��������� ������, ������� ����������� ��� vector<wstring>. <br> 
������������� ������ �������� � ���� �������� ���� - ���� � ������������ 
*/
#pragma once
#ifndef DATA_PROCESS_H
#define DATA_PROCESS_H
#include "Headers.h"
#include "stopwords.h"
#include "stemmer.h"
#include "stemming.h"
using namespace std;
/**
@brief ������������� ���� ��������� ������.
*/
/**
\class DataProcess
\details ����� ��� ������������� ���� ��������� ������.<br>
������������� ������ �������� � ���� �������� ���� - ���� � ������������ <br>
�������� ��� ���� ������, ����������� �� ��������� � ���� �����
*/
class DataProcess
{
public:
	/** ����������� �� ��������� 
	*/
	DataProcess();
	/** �����, � ������� ���������� ������������� ����. <br>
	� ���������� ������ ������, �� words ��������� ��� ����-�����, � ��� ����� ��������� � ���������� �����.<br>
	� ������ ��������������� ���������� ������ StopWords::removeWord(vector<wstring>* words) � stemming::russian_stem stem()
	\param[in, out] words ��������� �� ������ ���� 
	*/
	void processingWords(vector <wstring>* words);
private:
	StopWords stopWords;///<��������� ������ StopWords
	stemming::russian_stem <wstring> stem;///<��������� ������ stemming::russian_stem
};
#endif