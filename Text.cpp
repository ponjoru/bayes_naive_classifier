#include "Text.h"

bool Text::loadData(string filename, mode mode_)
{
	wifstream stream(filename);
	if (!stream.is_open())
	{
		return false;
	}
	stream.imbue(locale(LANGUAGE));
	if (mode_ == TRAINING_MODE)
		getline(stream, classname);
	else
		classname = EMPTY_STRING;
	wstring line;
	while (getline(stream, line))
	{
		updateData(line);
	}
	return true;
}
void Text::updateData(wstring line) 
{
	wchar_t *ptr = 0;       //Указатель
	wchar_t *rowstate;
	ptr = wcstok_s(&line[0], separators, &rowstate); //Выделяем первое слово из строки
	while (ptr) 
	{               
		data.push_back(wstring(ptr));
		ptr = wcstok_s(0, separators, &rowstate);   //Подбираем слово
	}
}
wstring Text::getClassName()
{
	return classname;
}
vector<wstring> Text::getData()
{
	return data;
}


