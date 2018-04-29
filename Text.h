#ifndef READ_DATA_H
#define READ_DATA_H

#include "Headers.h"

#define DELIMITERS L"!?.,;/*-+\n\t "
#define LANGUAGE "russian"
#define EMPTY_STRING L""

///перечисление режимов считывания данных из текста
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
	const wchar_t *separators = DELIMITERS; ///<Массив разделителей текста
	wstring classname; ///<Имя класса текста для обработки
	vector<wstring> data; ///<Список слов из текста 
private:
	/**
	Обновляет список слов словами из строки
	\param line строка
	*/
	void updateData(wstring line);
public:
	/**
	Обрабатывает данные из текстового файла
	\param filename имя файла
	\param mode_ режим чтения (обучающий текст или текст для классификации)
	\return true если метод сработал безошибочно, иначе false
	*/
	bool loadData(string filename, mode mode_);

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

#endif 