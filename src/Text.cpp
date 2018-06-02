#include "Text.h"


bool Text::loadData(wstring filename, wstring& class_name)
{
	wifstream stream(filename);
	if (!stream.is_open())
	{
		return false;
	}
	stream.imbue(locale(LANGUAGE));
	this->classname = class_name;
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
		if (wcslen(ptr) > 1)
		{
			for (size_t i = 0;i < wcslen(ptr);i++)
			{
				wchar_t a = towlower(ptr[i]);
				ptr[i] = a;
			}
			//std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
			data.push_back(wstring(ptr));
		}
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


