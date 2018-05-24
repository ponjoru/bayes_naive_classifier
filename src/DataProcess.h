/**
\file
\brief Заголовочный файл с описанием класса

Данный файл содержит определение класса, используемого
для предобработки исходного текста, который представлен как vector<wstring>. <br> 
Предобработка текста включает в себя удаление стоп - слов и лемматизацию 
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
@brief Предобработка слов исходного текста.
*/
/**
\class DataProcess
\details Класс для предобработки слов исходного текста.<br>
Предобработка текста включает в себя удаление стоп - слов и лемматизацию <br>
Содержит два поля данных, конструктор по умолчанию и один метод
*/
class DataProcess
{
public:
	/** Конструктор по умолчанию 
	*/
	DataProcess();
	/** Метод, в котором происходит предобработка слов. <br>
	В результате работы метода, из words удаляются все стоп-слова, и все слова приведены к нормальной форме.<br>
	В методе последовательно вызываются методы StopWords::removeWord(vector<wstring>* words) и stemming::russian_stem stem()
	\param[in, out] words указатель на вектор слов 
	*/
	void processingWords(vector <wstring>* words);
private:
	StopWords stopWords;///<Экземпляр класса StopWords
	stemming::russian_stem <wstring> stem;///<Экземпляр класса stemming::russian_stem
};
#endif