#include "BayesClassifier.h"


void BayesClassifier::run(void)
{
	train();
	execute("test.txt", SINGLE);
}
void BayesClassifier::train(void)
{
	for (int i = 1; i <= TRAINING_TEXTS_AMOUNT;i++)
	{
		string file_name_i = FILE_ROOT;
		file_name_i += to_string(i);
		file_name_i += FILE_EXTENSION;
				
		Text txt;
		
		if (!txt.loadData(file_name_i, TRAINING_MODE))
		{
			cout << "Warning:: File '" << file_name_i << "' with training data not found" << endl;
			continue;
		}
		texts_amount++;
		word_arr data = txt.getData();
		wstring classname = txt.getClassName();
		data_processor.processingWords(&data);
		updateTrainingMap(data, classname);
		class_metha[classname]++;
		printTrainingMap();
	}
	cout << "Info:: " << texts_amount << " files of " << TRAINING_TEXTS_AMOUNT << " were loaded" << endl;
}

void BayesClassifier::printClassmap(classmap* elem)
{
	std::wcout.imbue(locale("russian"));
	for (auto it = elem->begin(); it != elem->end()--; ++it)
	{
		std::wcout << it->first << " : " << it->second << endl;
	}
}
void BayesClassifier::printTrainingMap(void)
{
	wcout << "--------------------begin---------------------------" << endl;
	for (auto it = training_map.begin(); it != training_map.end()--; ++it)
	{
		wcout << it->first << endl << "------------------------------------------------" << endl;
		printClassmap(&(it->second));
	}
	wcout << "---------------------end----------------------------" << endl;
}
void BayesClassifier::updateTrainingMap(word_arr data, wstring classname)
{
	map<wstring,classmap>::iterator map_it = training_map.find(classname);
	classmap tmp_map;
	
	if (map_it != training_map.end())
		tmp_map = training_map[classname];
	else
		training_map.emplace(classname, tmp_map);
	
	for (int i = 0;i < data.size();i++)
	{
		
		/*if (tmp_map.find(data[i]) == tmp_map.end())
		{
			tmp_map.emplace(data[i], 1);
		}
		else*/
			training_map[classname][data[i]]++; 
			// classmap map = training_map[classname];
			// map[data[i]]++;
			//printTrainingMap();
	}
}
void BayesClassifier::updateExeMap(word_arr data)
{
	for (int i = 0;i < data.size();i++)
	{
		exe_map[data[i]]++;
	}
}
void BayesClassifier::execute(string filename, exe_mode mode_)
{
	Text txt;
	if (!txt.loadData(filename, EXECUTION_MODE))
	{
		cout << "Error:: File '" << filename << "' with data to analyze not found" << endl;
	}
	word_arr data = txt.getData();
	wstring classname = txt.getClassName();
	data_processor.processingWords(&data);
	updateExeMap(data);
	//printClassmap(&exe_map);
	int k = count(L"пес", L"собака");
	int m = classSize(L"собака");
	int n = countUnicWords();
	

	evaluateProbability(mode_, NULL);
}

bool BayesClassifier::getMethaInfo()
{
	wcout << L"¬ыберите режим выполнени€ (1 или 2)" << endl;
	wcout << L"1.¬еро€тность принадлежности всем классам\n" << endl;
	wcout << L"2.¬еро€тность принадлежности одному конкретному классу\n" << endl;
	char command;
	cin >> command;
	switch (command)
	{
	case '1':
	{
		mode_ = EXTENDED;
		break;
	}
	case '2':
	{
		mode_ = SINGLE;
		wcout << L"¬ыберете класс из перечн€ и введите им€ класса, к которому вы хотите проверить принадлежность текущего текста" << endl;
		for (auto it : training_map)
			wcout << it.first << endl;
		wcin >> classname;
		break;
	}
	default:
		return false;
	}
	return true;
}
// можно вынести в отдельный класс, но неудобно будет получить доступ к мапам
void BayesClassifier::evaluateProbability(exe_mode mode_, wstring classname)
{
	int unic_words_amount = countUnicWords();
	switch (mode_)
	{
		case SINGLE:
		{
			p(classname, unic_words_amount);
			break;
		}
		case EXTENDED:
		{
			for (int i = 0; i < DEFAULT_CLASSES_AMOUNT;i++)
			{
				p(classname, unic_words_amount);
			}
			break;
		}
		default:
		{
			cout << "Error::Wrong command entered" << endl;
			return;
		}
	}
}

double BayesClassifier::p(wstring classname, int unic_words)
{
	double result = 1;
	int class_size = classSize(classname);
	for (auto it : exe_map)
		result *= probability(it.first, classname, class_size, unic_words);
	result *= (class_metha[classname] / texts_amount);
	return result;
}

double BayesClassifier::probability(wstring word, wstring classname, int class_size, int unic_words)
{
	return (count(word, classname) + ALFA) / (class_size + ALFA * unic_words);
}

int BayesClassifier::count(wstring word, wstring classname)
{
	auto it = training_map.find(classname);
	if (it == training_map.end())
		return -1;
	classmap tmp = training_map[classname];
	auto jt = tmp.find(word);
	if (jt == tmp.end())
		return 0;
	else
		return tmp[word];
}

int BayesClassifier::classSize(wstring classname)
{
	auto it = training_map.find(classname);
	int result = 0;
	if (it == training_map.end())
		return -1;
	else
	{
		for (auto it : training_map[classname])
			result += it.second;
	}
	return result;
}

int BayesClassifier::countUnicWords(void)
{
	vector<wstring> tmp;
	int i = 0;
	for (auto item : training_map)
	{
		for (auto wordmap : item.second)
		{
			if (wordmap.second == 1)
			{
				auto t = find(tmp.begin(), tmp.end(), wordmap.first);
				if (t == tmp.end())
					tmp.push_back(wordmap.first);
				else
					tmp.erase(t);
			}	
		}
	}
	return tmp.size();
}