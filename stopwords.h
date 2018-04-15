#pragma once
#include <vector>
#include "stdafx.h"
#include "Headers.h"

#define DEFAULT_CLASSES_AMOUNT 5
#define FILE_EXTENSION ".txt"

using namespace std;
typedef vector<wstring>  word_list;
class StopWords
{
private:
	multimap<wchar_t, wstring> mapWords;
public:
		StopWords();
		bool readFile();
		bool findWord(wstring word);
		void removeWord(word_list* words);
};