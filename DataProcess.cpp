/**
\file
\brief ���� � ����������� ������� ������

������ ���� �������� ����������� ������, �������������
��� ������������� ��������� ������. <br>
*/
//#include "stdafx.h"
#include "DataProcess.h"

DataProcess::DataProcess()
{
}

void DataProcess::processingWords(vector <wstring>* words)
{
	// ������� ���� �����
	stopWords.removeWord(words);
	uint16_t i = 0;
	// �������� ��� ����� � ���������� �����
	for (i = 0; i < words->size(); i++)
		stem(words->at(i));

}