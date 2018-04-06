#include "DataProcess.h"

DataProcess::DataProcess()
{
	InitStopWords(STOP_WORDS_FILE_NAME_RUS);
}

DataProcess::DataProcess(wstring data)
{
	InitStopWords(STOP_WORDS_FILE_NAME_RUS);

}

vector<wstring> DataProcess::GetData(void)
{
	return this->data;
}

bool DataProcess::InitStopWords(string filename)
{
	wifstream stream(filename);
	

	if (!stream.is_open())
	{
		cout << "Error:: File with stop words not found";
		return false;
	}
	wstring word;

	stream.imbue(locale("russian"));
	while (getline(stream, word))
	{
		stop_words.insert(pair<wchar_t, wstring>(word[0], word));
		word.clear();
	}
	stop_words.insert(pair<wchar_t, wstring>(word[0], word));
	auto it = stop_words.end();
	///////////////////////////////////////////////////////////////////////

	for (auto it = stop_words.begin(); it != stop_words.end()--; ++it)
	{
		wcout << it->first << " : " << it->second << endl;
	}
	return true;
}

wstring DataProcess::Stemmer(wstring word)
{
	return wstring();
}

void DataProcess::Tokeniaztion(wstring line)
{
}

void DataProcess::DeleteStopWords(void)
{
}
 