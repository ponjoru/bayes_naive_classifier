#include "stdafx.h"

#include "DataProcess.h"

DataProcess::DataProcess()
{
	stopWords.readFile();
}


vector<wstring> DataProcess::GetData(void)
{
	return this->data;
}


void DataProcess::Tokeniaztion(wstring line)
{
}

void DataProcess::processingWords(vector <wstring>* words)
{
	// удаляем стоп слова
	stopWords.removeWord(words);

	// приводим все слова к нормальной форме
	for (int i = 0; i < words->size(); i++)
		stem(words->at(i));

}