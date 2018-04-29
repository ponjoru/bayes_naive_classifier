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
enum exe_mode 
{
	SINGLE,
	EXTENDED,
};

/**
 \brief ����� ������� ����������� �������������
 ������� ����� ���������, ����������� ���������� ����������� �������������� ������ � ������� ������� ������ � ������ ��� ���������� ������� �� ������� ���������
 */
class BayesClassifier
{
private:
	map<wstring, classmap> training_map;	///<������� ���������� ����� �������, ������ ���� ��������������� ������� ������ � ������� ������������� ���� � ��������� �������
	classmap exe_map; ///<������� ���������� ������ ������������ ���� � �� ��������, ������������� � ������� ������
	map<wstring, int> class_metha;	///<������� ���������� ��� ������ � ����� ������� ��������� ������� ����������� � ����� ������
	DataProcess data_processor; ///<����� � �������� ��� ��������� ������ (������� + �������� ���� ����)
	vector<double> results; ///<������ �����������
	int texts_amount = 0; ///<����� ������� ��������� �������
	exe_mode mode_; ///<����� ���������� ��������� 
	wstring classname = NULL; ///<��� ������, �������������� � �������� ����� ���������, �� ������� NULL
public:
	/**
	����� �����. �������� ����� ���������
	*/
	void run(void);

	/**
	�������� � ������� ������� (����� + �������)
	\param elem ��������� �� �������
	*/
	void printClassmap(classmap* elem);

	/**
	�������� � ������� ������� ������������ ����� ��������
	*/
	void printTrainingMap(void);

private:

	/**
	��������� ���������� ��������� ������������. ���� ����������� �������������� ��� ����������� ���������� ���������
	\return true � ������ ������, false �����
	*/
	bool getMethaInfo(void);

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
	\param mode_ ����� ���������� ����������� (��������� �������������� � ������ ������ ��� �� ���� ��������� �������)
	*/
	void execute(string filename, exe_mode mode_);

	void evaluateProbability(exe_mode mode_, wstring classname);

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
