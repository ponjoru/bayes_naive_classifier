#ifndef DATA_PROCESS_H
#define DATA_PROCESS__H
#include "Headers.h"
#include "stopwords.h"
#include "stemmer.h"
#include "stemming.h"

#define STOP_WORDS_FILE_NAME_RUS "StopWords.txt"

using namespace std;

class DataProcess
{
public:
	DataProcess();
	vector<wstring> GetData(void);
	void Tokeniaztion(wstring line);
	//void updateMap(vector <wstring> words);
	void processingWords(vector <wstring>* words);
private:
	vector<wstring> data;
	StopWords stopWords;
	stemming::russian_stem <wstring> stem;
};
#pragma once
#endif