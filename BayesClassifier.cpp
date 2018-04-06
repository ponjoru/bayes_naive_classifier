#include "BayesClassifier.h"

void BayesClassifier::Train(void)
{
	int file_counter = 0;
	for (int i = 1; i <= TRAINING_TEXTS_AMOUNT;i++)
	{
		string file_name_i = to_string(i);
		file_name_i += FILE_EXTENSION;
		ifstream fin(file_name_i);
		map<wstring, int> map;

		if (!fin.is_open())
		{
			cout << "Warning:: File #" + i;
			cout << " with training texts was not found" << endl;
			continue;
		}
		file_counter++;
		//			ProcessFile();
	}

}


int Run(void)
{
	setlocale(LC_ALL, "Russian");
	cout << "Привет" << endl;

	StopWords = InitStopWords(STOP_WORDS_FILE_NAME_RUS);
	//cout << CheckStopWord("я") << endl;
	//cout << CheckStopWord("дерево") << endl;*/

	return 0;
}
map<wstring, double> Evaluate(exe_mode)
{

}
double Probability(wstring word, wstring class_name)
{
	for (int i = 0; i<SCHAR_MAX;i++)

}
void ProcessFile(wifstream fin)
{


}