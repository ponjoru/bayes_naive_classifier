/*!
 \file
 \brief ������������ ���� � ��������� �������

 ������ ���� �������� � ���� ����������� ��������
 �������, ������������ � ���������������� ���������
 */
#ifndef BAYES_CLASSIFIER_H
#define BAYES_CLASSIFIER_H

#include "Headers.h"
#include "Text.h"
#include "DataProcess.h"
using namespace std;

/**
Enum.����� ������ ��������� 
*/
enum exe_mode 
{
	SINGLE, /**< ����� - �������� �������������� ������ ������ */
	EXTENDED, /**< ����� - �������� �������������� ���� ��������� ������� */
};

#define DEBUG true  ///<���� ��� ������ ����� ����������

#define DEFAULT_CLASSES_AMOUNT 4 ///<����� ������� ������������ � ���������
#define TRAINING_TEXTS_AMOUNT 30 ///<����� ������� ����������� � ������� ������

#define DEFAULT_BORDER 4 ///<��������, ��� ���������� ���������� ��������� ������

#define FILE_EXTENSION L".txt" ///<���������� ��������� ������ ��������� �������
#define FILE_TO_CHECK L"test.txt" ///<���� ��������� �������������
#define FOLDER_WITH_TEXTS L"res_test/" ///<��� ����� � ������� ��������� ����� � �������� ��������� �������
//#define FOLDER_WITH_TEXTS L"res/"
//#define FOLDER_WITH_TEXTS L"test/"

#define CLASSIFIER_PATH L"Classifier/" ///<��� �����, ��� ��������� ����������� �������������
//#define CLASSIFIER_NAME L"EasyTest.txt"
#define CLASSIFIER_NAME L"Classifier.txt" ///<��� ����� ��������������
//#define FILE_TO_CHECK L"test1.txt"
#define EMPTY_STRING L"" ///<������ ������


#define ALFA 1  ///<�������� ����������� ��� ���������� ������������


/**
 \brief ����� ������� ����������� �������������
 ������� ����� ���������, ����������� ���������� ����������� �������������� ������ � ������� ������� ������ � ������ ��� ���������� ������� �� ������� ���������
 */
class BayesClassifier
{
private:
	vector<wstring> classes; ///<������ ���� ������� ������������ � ���������
	map<wstring, classmap> training_map;	///<������� ���������� ����� �������, ������ ���� ��������������� ������� ������ � ������� ������������� ���� � ��������� �������
	classmap exe_map; ///<������� ���������� ������ ������������ ���� � �� ��������, ������������� � ������� ������
	map<wstring, int> class_metha;	///<������� ���������� ��� ������ � ����� ������� ��������� ������� ����������� � ����� ������
	DataProcess data_processor; ///<����� � �������� ��� ��������� ������ (������� + �������� ���� ����)
	vector<double> results; ///<������ �����������
	int texts_amount = 0; ///<����� ������� ��������� �������
	exe_mode mode_ = SINGLE; ///<����� ���������� ��������� 
	bool saved_classifier = false; ///<���� ���������� �� ���� �������� ������������� ���� �������� ������ ��������������
	wstring classname_to_check; ///<��� ������, �������������� � �������� ����� ���������
	wstring file_to_check; ///<��� ����� ������� ����� ���������
public:
	/**
	����������� ������. �������������� ������ ���� �������, �������������� � ���������
	*/
	BayesClassifier();
	
	/**
	������� ����� � ������ ��������
	\param border ��������� �������, ����� � ������� ������� ��������� �������
	*/
	void modifyTrainingMap(int border);

	/**
	��������� �������������
	\param clsf_filename ���� �� ��������������
	\return true � ������ �������� ��������, false �����
	*/
	bool loadClassifier(wstring clsf_filename);

	/**
	��������� ������������� � ����� Classifier
	*/
	void saveClassifier(wstring& name);

	/**
	����� �����. �������� ����� ���������
	*/
	void run(void);

	/**
	�������� � ����� � ������� ������� (����� + �������)
	\param elem ��������� �� �������
	\param stream ����� ������
	*/
	void printClassmap(classmap* elem, wostream& stream);

	/**
	�������� � ������� ������� ������������ ����� ��������
	*/
	void printTrainingMap(void);
	
	/**
	������ �����������
	\return ������ �����������
	*/
	vector<double> getResults();
private:

	/**
	��������� ���������� ��������� ������������. ���� ����������� �������������� ��� ����������� ���������� ���������
	\return true � ������ ������, false �����
	*/
	bool setMethaInfo(void);

	/**
	��������� ������������� �� ��������� ������ ���������� �� ��������� �������
	*/
	void train(void);

	/**
	��������� ����� �� ������� ���� � ������� � �������������� ������� � ������ � ��������������� ������ ������
	\param data ������ ����, ������� ����� ��������
	\param classname ��� ������, ���� �� ������� ���� ���������� � �������
	*/
	void updateTrainingMap(word_arr data, wstring classname);

	/**
	��������� ����� �� ������� ���� � ������� ���� �������� ������
	\param data ������ ����, ������� ����� ��������
	*/
	void updateExeMap(word_arr data);

	/**
	�������������� ������� ����� �� ��������� ������ �� ��������� �������
	\param filename ��� ���������� �����, � ������� ���������� ����� ��������� �������������
	*/
	void execute(wstring filename);

	/**
	��������� ����������� �������������� ��������� ������ � ��������� ������� � ���������� �� ���������������� ���������� �������� setMethaInfo()
	*/
	void evaluateProbability();

	/**
	������� ���������� ���� ���������� � ������ �� ��������� ������ 
	\param word �����
	\param classname ��� ������
	\return ������� �����
	*/
	int count(wstring word, wstring classname);

	/**
	����� ����������� ���������� ������ ��� ����������� �����
	\param word �����
	\param classname ��� ������
	\param class_size ���������� ���� ���� ���������� � ������
	\param unic_words ����� ���������� ���� � ������������� ������
	\return ����������� �������������� ����� ������
	*/
	double probability(wstring word, wstring classname, int class_size, int unic_words);
	
	/**
	���������� ����������� �������������� �������� ������ � ����������� ������
	\param classname ��� ������
	\param unic_words ����� ���������� ���� � ������������� ������
	\return ����������� �������������� ������ ������
	*/
	double p(wstring classname, int unic_words);

	/**
	���������� ���������� ���� ����������� � ������
	\param classname ��� ������
	\return ���������� ���� ���� ���������� � ������
	*/
	int classSize(wstring classname);

	/**
	������� ���������� ���������� ���� � ������������� ������
	\return ����������� ���������� ����
	*/
	int countUnicWords(void);
};


#pragma once

#endif // BAYES_CLASSIFIER_H
