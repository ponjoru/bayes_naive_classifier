﻿#include "BayesClassifier.h"
#include <iostream>
#include <locale>
#include <Windows.h>
/**
Точка входа программы. Инициализация класса BayesClassifier. Вычисление результатов. Печать результатов.
*/
int main(void)
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::ios::sync_with_stdio(false);
	
	BayesClassifier b_cl;
	b_cl.run();
	vector<double> results = b_cl.getResults();
	wcout << L"Результаты:" << endl;
	int k = 0;
	for (auto it : results)
	{
		wcout << b_cl.classes[k] << L" - " << it << endl;
		k++;
	}
	cout << endl;
	
	wcin >> k;
	return 0;
}