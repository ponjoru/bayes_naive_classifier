// stopwords.cpp: определяет точку входа для консольного приложения.
#include "stdafx.h"
#include"stopwords.h"
#define STOP_WORDS_FILE_NAME_RUS "stopwords.txt"

StopWords::StopWords()
{
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

void StopWords::removeWord(word_list* words)
{
	word_list::iterator it; //объявляю итератор it

	bool checkWord;
	int ind = 0;
	do
	{
		checkWord = findWord((*words).at(ind));
		if (checkWord)
			(*words).erase((*words).begin() + ind);
		else ind++;
	} while (ind != words->size());
	
}