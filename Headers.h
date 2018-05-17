/**
\file
\brief Файл с объявлением используемых библиотек

Данный файл содержит определение используемых библиотек и определение кастомных типов данных
*/
#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <locale.h>

typedef std::vector<std::wstring> word_arr; ///<Вектор слов
typedef std::map<std::wstring, int> classmap; ///<Таблица из 2 столбцов: 1 - слово, 2 - частота этого слова в выборке
#pragma once
#endif // HEADER_H