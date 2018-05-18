#include "BayesClassifier.h"

/**
����� ����� ���������. ������������� ������ BayesClassifier. ���������� �����������. ������ �����������.
*/
int main(void)
{
	//std::locale::global(std::locale(""));
	std::ios::sync_with_stdio(false);
	
	BayesClassifier b_cl;
	b_cl.run();
	vector<double> results = b_cl.getResults();
	wcout << L"����������:" << endl;
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