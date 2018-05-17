/**
\file
\brief Файл с объявлением класса StopWords

Данный файл содержит объявление класса, используемого
для предобработки исходного текста, а именно удаление стоп слов.
*/
#ifndef STOP_WORDS_H
#define STOP_WORDS_H
#include "Headers.h"
/**
\brief Имя файла, в котором хранятся стоп - слова
*/
#define STOP_WORDS_FILE_NAME_RUS "stopwords.txt"
using namespace std;
/**
@brief Удаления стоп - слов из исходного текста.
*/
/**
\class StopWords
Класс для удаления стоп - слов из вектора слов исходного текста.<br>
Содержит одно поле данных, конструктор по умолчанию и три метода.
*/
class StopWords
{
private:
	multimap<wchar_t, wstring> mapWords;///< Хранит таблицу <первый символ стоп - слова, стоп - слово>.<br>Для быстрого поиска слова
public:
		/** Конструктор по умолчанию. <br>Внутри происхдит считывание стоп - слов*/
		StopWords();
		
		/**  Метод для считвания стоп - слова из файла в таблицу mapWords
		\return True, если считывание произошло успешно, иначе False
		*/
		bool readFile();

		/** Метод для поиска слова из исходного текста в таблице стоп - слов mapWords
		\param[in] word слово из исходного текста
		\return True, если word является стоп - словом, иначе False
		*/
		bool findWord(wstring word);

		/** Метод для удаления всех стоп - слов, которые встречаются в исходном тексте.<br>
		Внутри метода вызывается findWord(wstring word).<br> Если он вернет true, то слово удаляется из вектора всех слов, иначе вектор остается неизмененным
		\param[in,out] words - указатель на вектор всех слов из исходного текста
		*/
		void removeWord(vector<wstring>* words);
};
#pragma once
#endif // STOP_WORDS_H