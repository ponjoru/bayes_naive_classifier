/*!
 \file
 \brief Заголовочный файл с описанием классов

 Данный файл содержит в себе определения основных
 классов, используемых в демонстрационной программе
 */
#ifndef BAYES_CLASSIFIER_H
#define BAYES_CLASSIFIER_H

#include "Headers.h"
#include "Text.h"
#include "DataProcess.h"
using namespace std;

/**
Enum.Режим работы программы 
*/
enum exe_mode 
{
	SINGLE, /**< режим - проверка принадлежности одному классу */
	EXTENDED, /**< режим - проверка принадлежности всем имеющимся классам */
};

#define DEBUG true  ///<Флаг для вывода дебаг информации

#define DEFAULT_CLASSES_AMOUNT 4 ///<Число классов используемых в программе
#define TRAINING_TEXTS_AMOUNT 30 ///<Число текстов относящихся к каждому классу

#define DEFAULT_BORDER 4 ///<Параметр, для сокращения флуктуации обучающих данных

#define FILE_EXTENSION L".txt" ///<Расширение текстовых файлов обучающей выборки
#define FILE_TO_CHECK L"test.txt" ///<Файл требующий классификации
#define FOLDER_WITH_TEXTS L"res_test/" ///<Имя папки в которой находятся папки с текстами обучающей выборки
//#define FOLDER_WITH_TEXTS L"res/"
//#define FOLDER_WITH_TEXTS L"test/"

#define CLASSIFIER_PATH L"Classifier/" ///<Имя папки, где находится сохраненный классификатор
//#define CLASSIFIER_NAME L"EasyTest.txt"
#define CLASSIFIER_NAME L"Classifier.txt" ///<Имя файла классификатора
//#define FILE_TO_CHECK L"test1.txt"
#define EMPTY_STRING L"" ///<Пустая строка


#define ALFA 1  ///<параметр сглаживания для вычисления вероятностей


/**
 \brief Класс Наивная Байесовская Классификация
 Базовый класс программы, реализующий вычисление вероятности принадлежности текста с помощью теоремы Байеса к одному или нескольким классов из перечня доступных
 */
class BayesClassifier
{
private:
	vector<wstring> classes; ///<Вектор имен классов используемых в программе
	map<wstring, classmap> training_map;	///<Таблица содержащая имена классов, список слов соответствующих каждому классу и частоту встретившихся слов в обучающей выборке
	classmap exe_map; ///<Таблица содержащая список обработанных слов с их частотой, встретившихся в входном тексте
	map<wstring, int> class_metha;	///<Таблица содержащая имя класса и число текстов обучающей выборки относящихся к этому классу
	DataProcess data_processor; ///<Класс с методами для обработки текста (стеммер + удаление стоп слов)
	vector<double> results; ///<Список результатов
	int texts_amount = 0; ///<Число текстов обучающей выборки
	exe_mode mode_ = SINGLE; ///<Режим выполнения программы 
	bool saved_classifier = false; ///<Поле отвечающее за либо загрузку существующего либо обучение нового классификатора
	wstring classname_to_check; ///<Имя класса, принадлежность к которому хотим проверять
	wstring file_to_check; ///<Имя файла которое хотим проверить
public:
	/**
	Конструктор класса. Инициализирует вектор имен классов, представленных в программе
	*/
	BayesClassifier();
	
	/**
	Убирает слова с редкой частотой
	\param border граничная частота, слова с меньшей которой требуется удалить
	*/
	void modifyTrainingMap(int border);

	/**
	Загружает классификатор
	\param clsf_filename путь до классификатора
	\return true в случае успешной загрузки, false иначе
	*/
	bool loadClassifier(wstring clsf_filename);

	/**
	Сохраняет классификатор в папку Classifier
	*/
	void saveClassifier(wstring& name);

	/**
	Точка входа. Основной метод программы
	*/
	void run(void);

	/**
	Печатает в поток в консоль таблицу (слово + частота)
	\param elem указатель на таблицу
	\param stream поток вывода
	*/
	void printClassmap(classmap* elem, wostream& stream);

	/**
	Печатает в консоль таблицу составленную после обучения
	*/
	void printTrainingMap(void);
	
	/**
	Геттер результатов
	\return вектор результатов
	*/
	vector<double> getResults();
private:

	/**
	Реализует консольный интерфейс пользователя. Ввод необходимой метаинформации для дальнейшего выполнения программы
	\return true в случае успеха, false иначе
	*/
	bool setMethaInfo(void);

	/**
	Тренирует классификатор на основании данных полученных из обучающей выборки
	*/
	void train(void);

	/**
	Добавляет слова из массива слов в таблицу с тренировочными данными в ячейку с соответствующим именем класса
	\param data массив слов, которые нужно добавить
	\param classname имя класса, ключ по которму идет добавление в таблицу
	*/
	void updateTrainingMap(word_arr data, wstring classname);

	/**
	Добавляет слова из массива слов в таблицу слов входного текста
	\param data массив слов, которые нужно добавить
	*/
	void updateExeMap(word_arr data);

	/**
	Классифицирует входной текст на основании данных из обучающей выборки
	\param filename имя текстового файла, в котором содержится текст требующий классификации
	*/
	void execute(wstring filename);

	/**
	Вычисляет вероятность принадлежности входящего текста к имеющимся классам в зависимоти от предопределенных параметров функцией setMethaInfo()
	*/
	void evaluateProbability();

	/**
	Подсчет количества слов отнесенных к классу на обучающих данных 
	\param word слово
	\param classname имя класса
	\return частота слова
	*/
	int count(wstring word, wstring classname);

	/**
	Поиск вероятности присвоения класса для конкретного слова
	\param word слово
	\param classname имя класса
	\param class_size количество всех слов отнесенных к классу
	\param unic_words число уникальных слов в тренировочных данных
	\return вероятность принадлежности слова классу
	*/
	double probability(wstring word, wstring classname, int class_size, int unic_words);
	
	/**
	Вычисление вероятности принадлежности входного текста к конкретному классу
	\param classname имя класса
	\param unic_words число уникальных слов в тренировочных данных
	\return вероятность принадлежности текста классу
	*/
	double p(wstring classname, int unic_words);

	/**
	Вычисление количества слов относящихся к классу
	\param classname имя класса
	\return количество всех слов отнесенных к классу
	*/
	int classSize(wstring classname);

	/**
	Подсчет количества уникальных слов в тренировочных данных
	\return кколичества уникальных слов
	*/
	int countUnicWords(void);
};


#pragma once

#endif // BAYES_CLASSIFIER_H
