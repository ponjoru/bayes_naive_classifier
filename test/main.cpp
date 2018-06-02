//#include <QtCore/QCoreApplication>
#include <QtTest/QtTest>

#include"../src/stemmer.h"
#include"../src/Headers.h"
#include"../src/stopwords.h"
#include"../src/stopwords.cpp"
#include"../src/DataProcess.h"
#include"../src/DataProcess.cpp"
#include"../src/Text.h"
#include"../src/Text.cpp"
#include"../src/BayesClassifier.h"
#include"../src/BayesClassifier.cpp"

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
wstring loadFile(string filename)
{
	wifstream stream(filename);
	stream.imbue(locale(LANGUAGE));
	wstring line;
	getline(stream, line);
	return line;
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

	void test_updateData_data();
	void test_updateData();

	void test_probability_data();
	void test_probability();

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

	vector<wstring> inputStr1, inputStr2, inputStr3, inputStr4, inputStr5, inputStr6;
	vector<wstring> processedStr1, processedStr2, processedStr3, processedStr4, processedStr5, processedStr6;

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
void TestModules::test_updateData_data()
{
	QTest::addColumn<wstring>("String_input");
	QTest::addColumn<vector<wstring>>("Vector_output2");
	vector<wstring> processedStr1, processedStr2, processedStr3;
	wstring in1 = loadFile("test_1.txt");
	/////////////////////////////////
	processedStr1.push_back(L"если");
	processedStr1.push_back(L"начинаешь");
	processedStr1.push_back(L"играть");
	processedStr1.push_back(L"баскетбол");
	processedStr1.push_back(L"математику");
	processedStr1.push_back(L"сейчас"); 
	processedStr1.push_back(L"делают");

	/////////////////////////////////
	QTest::newRow("String_1") << in1 << processedStr1;
	wstring in2 = loadFile("test_2.txt");
	/////////////////////////////////
	processedStr2.push_back(L"куринные");
	processedStr2.push_back(L"рулетики");
	processedStr2.push_back(L"фаршированные");
	processedStr2.push_back(L"яйцом");
	processedStr2.push_back(L"сыром");
	processedStr2.push_back(L"заленью");

	/////////////////////////////////
	QTest::newRow("String_2") << in2 << processedStr2;

	wstring in3 = loadFile("test_3.txt");
	/////////////////////////////////
	processedStr3.push_back(L"сдача");
	processedStr3.push_back(L"отчетности");
	processedStr3.push_back(L"отнимают");
	processedStr3.push_back(L"времени");
	processedStr3.push_back(L"сил");
	processedStr3.push_back(L"сдача");
	processedStr3.push_back(L"отчетности");
	processedStr3.push_back(L"отнимают");
	processedStr3.push_back(L"времени");
	processedStr3.push_back(L"сил");
	processedStr3.push_back(L"сдача");
	processedStr3.push_back(L"отчетности");
	processedStr3.push_back(L"отнимают");
	processedStr3.push_back(L"времени");
	processedStr3.push_back(L"сил");
	/////////////////////////////////
	QTest::newRow("String_3") << in3 << processedStr3;

}
void TestModules::test_updateData()
{
	Text t;
	QFETCH(wstring, String_input);
	t.updateData(String_input);
	QFETCH(vector<wstring>, Vector_output2);
	vector<wstring> r1 = t.data;
	QCOMPARE(r1, Vector_output2);
}

void TestModules::test_probability_data() 
{
	QTest::addColumn<wstring>("Word");
	QTest::addColumn<wstring>("Classname");
	QTest::addColumn<int>("Class_Size");
	QTest::addColumn<double>("P");

	wstring word1, word2, word3, word4, word5, word6;
	wstring className1, className2, className3, className4;

	className1 = L"economics";
	className2 = L"politics";
	className4 = L"it";
	className3 = L"sports";
	/////////////////////////
	int ClassSizeEconomics = 15;
	int ClassSizeIt = 11;
	int ClassSizePolitics = 15;
	int ClassSports = 16;

	/////////////////////////
	word1 = L"бирж";
	word2 = L"смартфон";
	word3 = L"путин";
	word4 = L"доллар";
	word5 = L"ракет";
	word6 = L"гречк";

	////////////////////////////////
	
	QTest::newRow("word1_economics_economics") << word1 << className1 << ClassSizeEconomics << (double)7/72;
	QTest::newRow("word1_economics_politics")  << word1 << className2 << ClassSizePolitics  << (double)1/72 ;
	QTest::newRow("word1_economics_sports")    << word1 << className3 << ClassSports		<< (double)1/73 ;
	QTest::newRow("word1_economics_it")        << word1 << className4 << ClassSizeIt		<< (double)1/68;

	QTest::newRow("word2_it_economics")        << word2 << className1 << ClassSizeEconomics << (double)1/72;
	QTest::newRow("word2_it_politics")		   << word2 << className2 << ClassSizePolitics  << (double)1/72;
	QTest::newRow("word2_it_sports")		   << word2 << className3 << ClassSports		<< (double)1/73;
	QTest::newRow("word2_it_it")			   << word2 << className4 << ClassSizeIt		<< (double)5/68;

	QTest::newRow("word3_politics_economics")  << word3 << className1 << ClassSizeEconomics << (double)1/72;
	QTest::newRow("word3_politics_politics")   << word3 << className2 << ClassSizePolitics  << (double)4/72;
	QTest::newRow("word3_politics_sports")     << word3 << className3 << ClassSports		<< (double)1/73;
	QTest::newRow("word3_politics_it")		   << word3 << className4 << ClassSizeIt		<< (double)1/68;

	QTest::newRow("word4_economics_economics") << word4 << className1 << ClassSizeEconomics << (double)3/72;
	QTest::newRow("word4_economics_politics")  << word4 << className2 << ClassSizePolitics  << (double)1/72;
	QTest::newRow("word4_economics_sports")    << word4 << className3 << ClassSports        << (double)1/73;
	QTest::newRow("word4_economics_it")		   << word4 << className4 << ClassSizeIt        << (double)1/68;

	QTest::newRow("word5_politics_economics")  << word5 << className1 << ClassSizeEconomics << (double)1/72;
	QTest::newRow("word5_politics_politics")   << word5 << className2 << ClassSizePolitics  << (double)2/72;
	QTest::newRow("word5_politics_sports")     << word5 << className3 << ClassSports		<< (double)1/73;
	QTest::newRow("word5_politics_it")		   << word5 << className4 << ClassSizeIt		<< (double)1/68;

	QTest::newRow("word6_economics")		   << word6 << className1 << ClassSizeEconomics << (double)1/72;
	QTest::newRow("word6_politics")			   << word6 << className2 << ClassSizePolitics  << (double)1/72;
	QTest::newRow("word6_sports")			   << word6 << className3 << ClassSports		<< (double)1/73;
	QTest::newRow("word6_it")				   << word6 << className4 << ClassSizeIt		<< (double)1/68;

}
void TestModules::test_probability() 
{

	BayesClassifier b;
	b.loadClassifier(L"Classifier/TestClassifier.txt");
	int unic_words = 57;
	QFETCH(wstring, Word);
	QFETCH(wstring, Classname);
	QFETCH(int, Class_Size);
	QFETCH(double, P);
	double res = b.probability(Word, Classname, Class_Size, unic_words);
	QCOMPARE(res, P);
}

QTEST_MAIN(TestModules)
#include "main.moc"
