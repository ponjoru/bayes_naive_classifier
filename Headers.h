#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <locale.h>

#define DEFAULT_CLASSES_AMOUNT 5
#define TRAINING_TEXTS_AMOUNT 40
#define FILE_ROOT "res/"
#define FILE_EXTENSION ".txt"
//параметр сглаживания для вычисления вероятностей
#define ALFA 1


typedef std::vector<std::wstring> word_arr;
typedef std::map<std::wstring, int> classmap;
#pragma once
#endif