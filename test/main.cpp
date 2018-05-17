//#include <QtCore/QCoreApplication>
#include <QtTest/QtTest>

#include"stemmer.h"
#include"Headers.h"
#include"stopwords.h"
#include"stopwords.cpp"
#include"DataProcess.h"
#include"DataProcess.cpp"
#define LANGUAGE "russian"

using namespace std;
Q_DECLARE_METATYPE(wstring)

vector<wstring> stringToVec(wstring wstr)
{
	int count = 0;
	wchar_t c;
	vector <wstring> stringToV;
	wstring tmp;
	do
	{
		c = wstr[count];
		if (c >= L'A' && c <= L'Я' || c >= L'а' && c <= L'я')
			tmp.push_back(c);

		else
		{
			stringToV.push_back(tmp);
			tmp.clear();
		}
		count++;
	} while (count != wstr.size());
	stringToV.push_back(tmp);
	return stringToV;
}

vector<wstring> loadData(string filename)
{
	wifstream stream(filename);
	stream.imbue(locale(LANGUAGE));
	wstring line;
	vector<wstring> res;
	getline(stream, line);
	res = stringToVec(line);
	return res;
}
class TestModules : public QObject
{
	Q_OBJECT
		private slots:
	void test_stemmer_data();
	void test_stemmer();

	void test_deleteStopWords_data();
	void test_deleteStopWords();

	void test_processingWords_data();
	void test_processingWords();

};

void TestModules::test_stemmer_data()
{
	QTest::addColumn<wstring>("Word");
	QTest::addColumn<wstring>("Stem");
	//БЛОК 1. Слово как суфикс или окончание
	wstring word1(L"вши");
	wstring stem1(L"вши");

	wstring word2(L"ей");
	wstring stem2(L"е");

	wstring word3(L"ем");
	wstring stem3(L"ем");

	wstring word4(L"ешь");
	wstring stem4(L"еш");

	wstring word5(L"уют");
	wstring stem5(L"уют");


	//ОКОНЧАНИЕ / СУФФИКС ПОЛНОСТЬЮ ВХОДЯТ В СТЕММУ
	wstring word6(L"поют");
	wstring stem6(L"поют");

	wstring word7(L"тающая");
	wstring stem7(L"тающ");

	wstring word8(L"енот");
	wstring stem8(L"енот");

	QTest::newRow("word_1_as_an_end") << word1 << stem1;
	QTest::newRow("word_2_as_an_end") << word2 << stem2;
	QTest::newRow("word_3_as_an_end") << word3 << stem3;
	QTest::newRow("word_4_as_an_end") << word4 << stem4;
	QTest::newRow("word_5_as_an_end") << word5 << stem5;
	QTest::newRow("word_6_end_in_stemm") << word6 << stem6;
	QTest::newRow("word_7_end_in_stemm") << word7 << stem7;
	QTest::newRow("word_8_end_in_stemm") << word8 << stem8;

	// ПРОВЕРКА НА КАЖДУЮ ГРУППУ ОКОНЧАНИЙ
	wstring word9(L"дальнейшее");
	wstring stem9(L"дальн");

	QTest::newRow("word_9_SUPERLATIVE") << word9 << stem9;

	wstring word10(L"молодость");
	wstring stem10(L"молод");

	QTest::newRow("word_10_DERIVATIONAL") << word10 << stem10;

	//ничего не удаляем
	wstring word11(L"экономист");
	wstring stem11(L"экономист");
	QTest::newRow("word_11_nothing is deleted") << word11 << stem11;

	wstring word12(L"мама");
	wstring stem12(L"мам");
	QTest::newRow("word_12_NOUN") << word12 << stem12;

	wstring word13(L"заплывать");
	wstring stem13(L"заплыва");

	wstring word14(L"уходите");
	wstring stem14(L"уход");

	QTest::newRow("word_13_VERB") << word13 << stem13;
	QTest::newRow("word_14_VERB") << word14 << stem14;

	wstring word15(L"смотрясь");
	wstring stem15(L"смотр");
	QTest::newRow("word_15_REFLXIVE") << word15 << stem15;

	wstring word16(L"сломанный");
	wstring stem16(L"слома");
	QTest::newRow("word_16_PARTICIPLE") << word16 << stem16;


	wstring word17(L"новостной");
	wstring stem17(L"новостн");
	QTest::newRow("word_17_ADJECTIVE") << word17 << stem17;


	wstring word18(L"покаявшись");
	wstring stem18(L"покая");
	QTest::newRow("word_18_RERFECT_GERUND") << word18 << stem18;

	//НЕСКОЛЬКО ОКОНЧАНИЙ ДЛЯ УДАЛЕНИЯ
	wstring word19(L"отстранившись");
	wstring stem19(L"отстран");

	wstring word20(L"информационный");
	wstring stem20(L"информацион");

	wstring word21(L"страхующийся");
	wstring stem21(L"страх");

	QTest::newRow("word_18_several_endings") << word19 << stem19;
	QTest::newRow("word_20_several_endings") << word20 << stem20;
	QTest::newRow("word_21_several_endings") << word21 << stem21;
	
	wstring word22(L"времяисчисление");
	wstring stem22(L"времяисчислен");
	QTest::newRow("word_22_compound_word") << word22 << stem22;

	wstring word23(L"пароход");
	wstring stem23(L"пароход");
	QTest::newRow("word_23_nothing is deleted") << word23 << stem23;

	wstring word24(L"сумел");
	wstring stem24(L"сумел");
	QTest::newRow("word_23_nothing is deleted") << word24 << stem24;

}
void TestModules::test_stemmer()
{
	QFETCH(wstring, Word);
	QFETCH(wstring, Stem);
	stemming::russian_stem <wstring> stem;
	stem(Word);
	QCOMPARE(Word, Stem);
}
void TestModules::test_deleteStopWords_data()
{
	QTest::addColumn<vector<wstring>>("String_input");
	QTest::addColumn<vector<wstring>>("String_without_stop_words");
	vector<wstring> inputStr1, inputStr2, inputStr3, inputStr4, inputStr5, inputStr6, inputStr7, inputStr8;
	vector<wstring> withoutStop1, withoutStop2, withoutStop3, withoutStop4, withoutStop5, withoutStop6, withoutStop7, withoutStop8;

	// стоп слова в начале строки
	inputStr6 = stringToVec(L"в петербурге открылась выставка");
	withoutStop6 = stringToVec(L"петербурге открылась выставка");

	//стоп слова в начале и середине строки
	inputStr1 = stringToVec(L"во флориде на берег вынесло обломки корабля");
	withoutStop1 = stringToVec(L"флориде берег вынесло обломки корабля");

	//4 стоп слова подряд 
	inputStr2 = stringToVec(L"это было по многочисленным просьбам");
	withoutStop2 = stringToVec(L"просьбам");

	//стоп слово в конце
	inputStr3 = stringToVec(L"средние оптовые цены выросли на");
	withoutStop3 = stringToVec(L"средние оптовые цены выросли");

	// нет стоп слов
	inputStr4 = stringToVec(L"ученые уточнили время падения китайской станции");
	withoutStop4 = stringToVec(L"ученые уточнили падения китайской станции");

	//строка из стоп слов
	inputStr7 = stringToVec(L"он однажды говорил шесть раз подряд");

	// стоп слова в середине строки
	inputStr5 = stringToVec(L"связаться с редакцией или сообщить");
	withoutStop5 = stringToVec(L"связаться редакцией сообщить");
	inputStr8 = stringToVec(L"сдерживать рост цен пришлось резервному банку который сумел");
	withoutStop8 = stringToVec(L"сдерживать рост цен пришлось резервному банку сумел");
	QTest::newRow("string_1_at_the_beginning_middle") << inputStr1 << withoutStop1;
	QTest::newRow("string_2_at_four_in_a_row") << inputStr2 << withoutStop2;
	QTest::newRow("string_3_at_the_end") << inputStr3 << withoutStop3;
	QTest::newRow("string_4_without") << inputStr4 << withoutStop4;
	QTest::newRow("string_5_at_the_middle") << inputStr5 << withoutStop5;
	QTest::newRow("string_6_at_the_beginning") << inputStr6 << withoutStop6;
	QTest::newRow("string_7_all") << inputStr7 << withoutStop7;
	QTest::newRow("string_8") << inputStr8 << withoutStop8;


}
void TestModules::test_deleteStopWords()
{
	QFETCH(vector<wstring>, String_input);
	QFETCH(vector<wstring>, String_without_stop_words);
	StopWords stopWord;
	stopWord.removeWord(&String_input);
	QCOMPARE(String_input, String_without_stop_words);
}
void TestModules::test_processingWords_data() 
{
	QTest::addColumn<vector<wstring>>("Words_input");
	QTest::addColumn<vector<wstring>>("Words_processed");

	vector<wstring> inputStr1, inputStr2, inputStr3, inputStr4, inputStr5, inputStr6, inputStr7;
	vector<wstring> processedStr1, processedStr2, processedStr3, processedStr4, processedStr5, processedStr6, processedStr7;

	inputStr1 = stringToVec(L"он однажды говорил шесть раз подряд по многочисленным");
	QTest::newRow("string_1_all_stop_words") << inputStr1 << processedStr1;

	inputStr2 = stringToVec(L"енот ест пароход");
	processedStr2 = stringToVec(L"енот ест пароход");

	QTest::newRow("string_2_without_changes") << inputStr2 << processedStr2;

	inputStr3 = loadData("test_processed1.txt");
	processedStr3 = loadData("test_processed_res1.txt");
	QTest::newRow("string_3") << inputStr3 << processedStr3;

	inputStr4 = loadData("test_processed3.txt");
	processedStr4 = loadData("test_processed_res3.txt");
	QTest::newRow("string_4") << inputStr4 << processedStr4;

	inputStr5 = loadData("test_processed4.txt");
	processedStr5 = loadData("test_processed_res4.txt");
	QTest::newRow("string_5") << inputStr5 << processedStr5;

	inputStr6 = loadData("test_processed5.txt");
	processedStr6 = loadData("test_processed_res5.txt");
	QTest::newRow("string_6") << inputStr6 << processedStr6;
}
void TestModules::test_processingWords()
{
	QFETCH(vector<wstring>, Words_input);
	QFETCH(vector<wstring>, Words_processed);
	DataProcess process;
	process.processingWords(&Words_input);

	QCOMPARE(Words_input, Words_processed);
}
QTEST_MAIN(TestModules)
#include "main.moc"
