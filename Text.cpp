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
	wchar_t *ptr = 0;       //���������
	ptr = wcstok(&line[0], separators); //�������� ������ ����� �� ������
	while (ptr) 
	{               
		data.push_back(wstring(ptr));
		ptr = wcstok(0, separators);   //��������� �����
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


