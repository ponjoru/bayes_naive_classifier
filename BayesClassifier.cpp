#include "BayesClassifier.h"

BayesClassifier::BayesClassifier()
{
	classes.push_back(L"it");
	classes.push_back(L"economics");
	classes.push_back(L"politics");
	classes.push_back(L"sports");
}

void BayesClassifier::run(void)
{
	wstring clsf_name = CLASSIFIER_PATH;
	clsf_name += CLASSIFIER_NAME;
	if (!setMethaInfo())
		return;
	wcout << L"Success:: Metainformation was loaded" << endl;
	if (saved_classifier)
	{
		if (!loadClassifier(clsf_name)) return;
	}
	else
	{
		train();
		wcout << L"Success:: Training completed" << endl;
		saveClassifier(clsf_name);
	}

	if (DEBUG)
	{
		wcout << L"Тренировочная выборка:" << endl;
		printTrainingMap();
		wcout << L"Число текстов в выборке - " << texts_amount << endl;
		wcout << L"Число текстов в в каждом классе:" << endl;
		printClassmap(&class_metha, wcout);
		wcout << L"-----------------------------------------" << endl;
	}
	execute(file_to_check);
}
void BayesClassifier::train(void)
{
	for (auto class_id : classes)
	{
		for (int i = 1; i <= TRAINING_TEXTS_AMOUNT;i++)
		{
			Text txt;
			wstring file_name_i = FOLDER_WITH_TEXTS;
			file_name_i += class_id + L"/";
			file_name_i += to_wstring(i);
			file_name_i += FILE_EXTENSION;
			
			if (!txt.loadData(file_name_i, class_id))
			{
				wcout << "Warning:: File '" << file_name_i << "' with training data not found" << endl;	
				continue;
			}
			texts_amount++;
			word_arr data = txt.getData();
			wstring classname = txt.getClassName();
			data_processor.processingWords(&data);
			updateTrainingMap(data, classname);
			class_metha[classname]++;
			wcout << "Success:: File '" << file_name_i << "' with training data was proccessed" << endl;
			
		}
		//if (DEBUG) printTrainingMap();
	}
	modifyTrainingMap(DEFAULT_BORDER);
	if (DEBUG) printTrainingMap();
	cout << "Info:: " << texts_amount << " files of " << TRAINING_TEXTS_AMOUNT * classes.size() << " were loaded" << endl;
}
void BayesClassifier::execute(wstring filename)
{
	Text txt;
	wstring class_name = EMPTY_STRING;
	if (!txt.loadData(filename, class_name))
	{
		wcout << "Error:: File '" << filename << "' with data to analyze not found" << endl;
	}
	word_arr data = txt.getData();
	data_processor.processingWords(&data);
	updateExeMap(data);
	if (DEBUG) printClassmap(&exe_map, wcout);
	/*int k = count(L"пес", L"собака");
	int m = classSize(L"собака");
	int n = countUnicWords();*/
	

	evaluateProbability();
}


void BayesClassifier::printClassmap(classmap* elem, wostream& stream)
{
	stream.imbue(locale("russian"));
	for (auto it = elem->begin(); it != elem->end()--; ++it)
	{
		stream << it->first << " : " << it->second << endl;
	}
}
void BayesClassifier::printTrainingMap(void)
{
	wcout << "--------------------begin---------------------------" << endl;
	for (auto it = training_map.begin(); it != training_map.end()--; ++it)
	{
		wcout << "----------------------------------------------------" << endl;
		wcout << it->first << endl;
		wcout << "----------------------------------------------------" << endl;
		printClassmap(&(it->second), wcout);
	}
	wcout << "---------------------end----------------------------" << endl;
}

void BayesClassifier::saveClassifier(wstring &name)
{
	wstring clsf_name = name;
	wofstream stream(clsf_name);
	if (!stream.is_open())
	{
		wcout << "Error:: Classifier cannot be saved" << endl;
		return;
	}
	stream << "##" << texts_amount << endl;
	printClassmap(&class_metha, stream);
	stream << "##" << endl;
	for (auto it = training_map.begin(); it != training_map.end()--; ++it)
	{
		stream << it->first << "#" << endl;
		printClassmap(&(it->second), stream);
	}
	wcout << "Success:: Classifier " << clsf_name << " was saved"<< endl;
}
bool BayesClassifier::loadClassifier(wstring clsf_filename)
{
	wifstream stream(clsf_filename);
	if (!stream.is_open())
	{
		wcout << "Error:: Classifier was not found " << clsf_filename << endl;
		return false;
	}
	stream.imbue(locale(LANGUAGE));
	wstring line;
	classmap tmp_map;
	wstring classname;

	getline(stream, line);
	texts_amount = stoi(line.substr(2, line.length()));
	getline(stream, line);
	while (line.compare(L"##"))
	{
		wstring class_name = line.substr(0, line.find_first_of(':') - 1);
		wstring class_texts_amount = line.substr(line.find_first_of(':') + 1, line.length() - 1);
		class_metha[class_name] = stoi(class_texts_amount);
		getline(stream, line);
	}
	while (getline(stream, line))
	{
		int length = line.length();
		if (line[length - 1] == '#')
		{
			classname = line.substr(0, length - 1);
			training_map[classname] = tmp_map;
		}
		else
		{
			wstring word = line.substr(0, line.find_first_of(':') - 1);
			wstring frequency = line.substr(line.find_first_of(':') + 1, length - 1);
			training_map[classname][word] = stoi(frequency);
		}
	}
	wcout << "Success:: Classifier " << clsf_filename << " was loaded" << endl;
	return true;
}

void BayesClassifier::modifyTrainingMap(int border)
{
	for (auto i = training_map.begin(); i != training_map.end(); i++)
		for (auto j = i->second.begin(); j != i->second.end(); j++)
		{
			if (j->second <= border)
			{
				i->second.erase(j);
				j = i->second.begin();
			}
		}
}
void BayesClassifier::updateTrainingMap(word_arr data, wstring classname)
{
	map<wstring,classmap>::iterator map_it = training_map.find(classname);
	classmap tmp_map;
	
	if (map_it != training_map.end())
		tmp_map = training_map[classname];
	else
		training_map.emplace(classname, tmp_map);
	
	for (unsigned int i = 0;i < data.size();i++)
		training_map[classname][data[i]]++; 
}
void BayesClassifier::updateExeMap(word_arr data)
{
	for (unsigned int i = 0;i < data.size();i++)
		exe_map[data[i]]++;
}

vector<double> BayesClassifier::getResults()
{
	return results;
}

bool BayesClassifier::setMethaInfo()
{
	char command;
	wcout << endl << L"Использовать сохраненный классификатор? y/n (Иначе будет создан новый классификатор) - ";
	cin >> command;

	switch (command)
	{
	case ('Y' | 'y'):
	{
		saved_classifier = true;
		break;
	}
	case ('N' | 'n'):
	{
		saved_classifier = false;
		break;
	}
	default:
	{
		wcout << "Error:: wrong command entered" << endl;
		return false;
	}
	}
	wcout << L"Введите имя файла, в котором содержится текст, который вы хотите классифицировать - ";
	wcin >> file_to_check;
	wcout << endl << L"1.Вероятность принадлежности всем классам" << endl;
	wcout << L"2.Вероятность принадлежности одному конкретному классу" << endl;
	wcout << L"Выберите режим выполнения (1 или 2): - ";
	
	
	cin >> command;
	switch (command)
	{
	case '1':
	{
		mode_ = EXTENDED;
		classname_to_check = L"";
		break;
	}
	case '2':
	{
		mode_ = SINGLE;
		wcout << L"-------------------------------------------------------------------------------------------------------------" << endl;
		wcout << L"Выберете класс из перечня, к которому вы хотите проверить принадлежность текущего текста" << endl;
		for (auto it : classes)
			wcout << L"* " << it << endl;
		wcout << L"Введите имя класса ";
		wcin.imbue(locale("rus_rus.866"));
		wcin >> classname_to_check;
		/*if (training_map.find(classname_to_check) == training_map.end())
			return false;*/
		break;
	}
	default:
	{
		wcout << "Error:: wrong command entered" << endl;
		return false;
	}
	}
	return true;
}

void BayesClassifier::evaluateProbability()
{
	int unic_words_amount = countUnicWords();
	switch (mode_)
	{
		case SINGLE:
		{
			results.push_back(p(classname_to_check, unic_words_amount));
			break;
		}
		case EXTENDED:
		{
			for (auto it : training_map)
			{
				results.push_back(p(it.first, unic_words_amount));
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
	{
		double p = probability(it.first, classname, class_size, unic_words);
		double k = 1;
		for (int i = 0;i < it.second;i++)
		{
			k *= p;
			result *= p;
		}
		//wcout << k << endl;
	}
	if (DEBUG) wcout << "P(class) = " << class_metha[classname] << "/" << double(texts_amount) << endl;
	result *= (class_metha[classname] / double(texts_amount));
	return result;
}
double BayesClassifier::probability(wstring word, wstring classname, int class_size, int unic_words)
{
	//wcout << word << L"  "<< classname << endl;
	//wcout << L"count(word, classname) = " << count(word, classname) << endl;
	//wcout << L"unique words = " << unic_words << endl;
	//wcout << L"class_size = " << class_size << endl;
	if (DEBUG)wcout << "P(" << word << "|" << classname << ") = " << count(word, classname) + ALFA << "/" << class_size + ALFA * unic_words << endl;
	return (count(word, classname) + ALFA) / double(class_size + ALFA * unic_words);
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
		for (auto jt : training_map[classname])
			result += jt.second;
	}
	return result;
}
int BayesClassifier::countUnicWords(void)
{
	map<wstring, int> buf;
	int res = 0;
	for (auto item : training_map)
	{
		for (auto wordmap : item.second)
		{
			auto t = buf.find(wordmap.first);
			//wcout << L"word - " << wordmap.first << L" ammount - " << wordmap.second << endl;
			if (t == buf.end())
			{
				buf.insert(pair<wstring, int>(wordmap.first, wordmap.second));
				res += wordmap.second;
				//wcout << L"res - " << res << endl;
			}
			else
			{
				res -= buf[wordmap.first];
				buf[wordmap.first] = 0;
				//wcout << L"res - " << res << endl;
			}	
		}
		//wcout << L"res - " << res  << " ---- " << endl;
	}
	return res;
}