#include "BayesClassifier.h"

// 1. ���������� ���� result � ����� ������� ������������� => ����� getResult
// 2. ��������� � ��������� ����� ����������� ������������ (�� ��������� ������ � �����) => ����� �������� ��� ���� � ��������� ����� ������ � ���������� �� � ����� ����������� �� ������
// 3. updateExeMap ��� �����?
// 4. ������������ ������� wcout � cout
// 5. training_map[classname][data[i]]++ �������� ���? ��� ���������
int main(void)
{
	std::locale::global(std::locale(""));
	std::ios::sync_with_stdio(false);
	BayesClassifier b_cl;
	b_cl.run();
	return 0;
}