#include <QtTest/QtTest>
#include <string>
//#include"stopwords.h"

using namespace std;
Q_DECLARE_METATYPE(wstring)
class TestDeleteStopWord : public QObject
{
	Q_OBJECT
		private slots:
	void test__deleteStopWords_data();
	void test__deleteStopWords();
};
void TestDeleteStopWord::test__deleteStopWords()
{
	QTest::addColumn<wstring>("String_input");
	QTest::addColumn<wstring>("String_without_stop_words");

	// стоп слова в начале строки
	wstring inputStr6(L"в петербурге открылась выставка");
	wstring withoutStop6(L"петербурге открылась выставка");

	//стоп слова в начале и середине строки
	wstring inputStr1(L"во флориде на берег вынесло обломки корабля");
	wstring withoutStop1(L"флориде берег вынесло обломки корабля");

	//4 стоп слова подряд 
	wstring inputStr2(L"это было по многочисленным просьбам");
	wstring withoutStop2(L"просьбам");

	//стоп слово в конце
	wstring inputStr3(L"средние оптовые цены выросли на");
	wstring withoutStop3(L"средние оптовые цены выросли");

	// нет стоп слов
	wstring inputStr4(L"ученые уточнили время падения китайской станции");
	wstring withoutStop4(L"ученые уточнили время падения китайской станции");

	//строка из стоп слов
	wstring inputStr5(L"он однажды говорил шесть раз подряд");
	wstring withoutStop5(L"");
	// стоп слова в середине строки
	wstring inputStr6(L"связаться с редакцией или сообщить");
	wstring withoutStop6(L"связаться редакцией сообщить");

	QTest::newRow("string_1") << inputStr1 << withoutStop1;
	QTest::newRow("string_2") << inputStr2 << withoutStop2;
	QTest::newRow("string_3") << inputStr3 << withoutStop3;
	QTest::newRow("string_4") << inputStr4 << withoutStop4;
	QTest::newRow("string_5") << inputStr5 << withoutStop5;
	QTest::newRow("string_6") << inputStr6 << withoutStop6;
	
}
void TestDeleteStopWord::test__deleteStopWords()
{
	QFETCH(wstring, String_input);
	QFETCH(wstring, String_without_stop_words);
	StopWord::StopWord stopWords;
	stopWords.deleteStopWord(String_input);
	QCOMPARE(String_input, String_without_stop_words);
}
QTEST_MAIN(TestDeleteStopWord)
#include "stopWordTest.moc"
