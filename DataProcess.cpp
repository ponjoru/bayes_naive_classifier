/**
\file
\brief ‘айл с реализацией методов класса

ƒанный файл содержит определение класса, используемого
дл€ предобработки исходного текста. <br>
*/
//#include "stdafx.h"
#include "DataProcess.h"

DataProcess::DataProcess()
{
}

void DataProcess::processingWords(vector <wstring>* words)
{
	// удал€ем стоп слова
	stopWords.removeWord(words);
	uint16_t i = 0;
	// приводим все слова к нормальной форме
	for (i = 0; i < words->size(); i++)
		stem(words->at(i));

}