#include "BayesClassifier.h"

/**
Точка входа программы. Инициализация класса BayesClassifier. Вычисление результатов. Печать результатов.
*/
int main(void)
{
	//std::locale::global(std::locale(""));
	std::ios::sync_with_stdio(false);
	
	BayesClassifier b_cl;
	b_cl.run();
	vector<double> results = b_cl.getResults();
	wcout << L"Результаты:" << endl;
	for (auto it : results)
		cout << it << " ";
	cout << endl;
	int k;
	wcin >> k;
	return 0;
}