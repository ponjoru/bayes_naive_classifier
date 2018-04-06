#ifndef DATA_PROCESS_H
#define DATA_PROCESS__H
#include "Headers.h"

#define STOP_WORDS_FILE_NAME_RUS "StopWords.txt"

using namespace std;

class DataProcess
{
public:
	DataProcess();
	DataProcess(wstring data);
	bool InitStopWords(string filename);
	vector<wstring> GetData(void);
	wstring Stemmer(wstring word);
	void Tokeniaztion(wstring line);
	void DeleteStopWords(void);
private:
	multimap<wchar_t, wstring> stop_words;
	vector<wstring> data;

};
#pragma once
#endif