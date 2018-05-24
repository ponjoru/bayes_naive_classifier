// stopwords.cpp: определяет точку входа для консольного приложения.
/**
\file
\brief Файл с реализацией методов класса

Данный файл содержит определение класса, используемого
для удаления стоп - слов из вектора, состоящего из слов исходного текста
*/
//#include "stdafx.h"
#include"stopwords.h"

StopWords::StopWords()
{
	readFile();
}

bool StopWords::readFile()
{
	setlocale(LC_ALL, "rus");

	wifstream stream(STOP_WORDS_FILE_NAME_RUS);
	
	if (!stream.is_open())
	{
		cout << "Error:: File with stop words not found";
		return false;
	}

	wstring word;

	stream.imbue(locale("russian"));

	while (getline(stream, word))
	{
		mapWords.insert(pair<wchar_t, wstring>(word[0], word));
		word.clear();
	}
	return true;
}

bool StopWords::findWord(wstring word)
{
	wchar_t firstSymb = word[0];

	wstring stopWord;
	wstring::size_type n;

	pair <multimap<wchar_t, wstring>::iterator, multimap<wchar_t, wstring>::iterator> ret;
	ret = mapWords.equal_range(firstSymb);

	for (multimap<wchar_t, wstring>::iterator it = ret.first; it != ret.second; ++it)
	{
		stopWord = it->second;
		if (word.size() == stopWord.size())
		{
			n = stopWord.find(word);
			if (n == wstring::npos)
				continue;
			else return true;
		}
	}
	return false;
}

void StopWords::removeWord(vector<wstring>* words)
{
	size_t ind = 0;
	do
	{
		bool checkWord = findWord((*words).at(ind));
		if (checkWord)
			(*words).erase((*words).begin() + ind);
		else ind++;
	} while (ind != words->size());
	
}