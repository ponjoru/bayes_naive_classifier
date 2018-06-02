/**
\file
\brief Файл с объявлением класса Text, используемого для считывания данных из файла

*/
#ifndef READ_DATA_H
#define READ_DATA_H

#include "Headers.h"
#include <algorithm>
#define DELIMITERS L"!?.,;:/*-+\n\t 1234567890'><=_)([]{}\"«»" ///<Строка с разделителями
#define LANGUAGE "russian" ///<Язык, с которым работает программа
#define EMPTY_STRING L"" ///<Пустая строка

/**
Enum. Перечисление режимов считывания данных из текста
*/
enum mode 
{
TRAINING_MODE, ///<Текст с обучающими данными
EXECUTION_MODE, ///<Текст для классификации
};
using namespace std;

/**
\brief Класс Парсер Текста
Класс реализующий методы чтения тренировочных и входных текстовых данных
*/
class Text 
{
private:
	const wchar_t* separators = DELIMITERS; ///<Массив разделителей текста
	wstring classname; ///<Имя класса текста для обработки
	vector<wstring> data; ///<Список слов из текста 
public:
	/**
	Обновляет список слов словами из строки
	\param line строка
	*/
	void updateData(wstring line);
public:

	/**
	Обрабатывает данные из текстового файла
	\param filename имя файла
	\param classname имя класса, к которому принадлежит текст
	\return true если метод сработал безошибочно, иначе false
	*/
	bool loadData(wstring filename, wstring& classname);

	/**
	Возвращает имя класса
	\return имя класса
	*/
	wstring getClassName(void);

	/**
	Возвращает вектор слов
	\return вектор слов
	*/
	vector<wstring> getData(void);
};

#pragma once

#endif // TEXT_H