//#include <QtCore/QCoreApplication>
#include <QtTest/QtTest>

#include"stemmer.h"
#include"Headers.h"
#include"stopwords.h"
#include"stopwords.cpp"
#include"DataProcess.h"
#include"DataProcess.cpp"
#include"Text.h"
#include"Text.cpp"

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
		if (c >= L'A' && c <= L'�' || c >= L'�' && c <= L'�')
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

};

void TestModules::test_stemmer_data()
{
	QTest::addColumn<wstring>("Word");
	QTest::addColumn<wstring>("Stem");
	//���� 1. ����� ��� ������ ��� ���������
	wstring word1(L"���");
	wstring stem1(L"���");

	wstring word2(L"��");
	wstring stem2(L"�");

	wstring word3(L"��");
	wstring stem3(L"��");

	wstring word4(L"���");
	wstring stem4(L"��");

	wstring word5(L"���");
	wstring stem5(L"���");


	//��������� / ������� ��������� ������ � ������
	wstring word6(L"����");
	wstring stem6(L"����");

	wstring word7(L"������");
	wstring stem7(L"����");

	wstring word8(L"����");
	wstring stem8(L"����");

	QTest::newRow("word_1_as_an_end") << word1 << stem1;
	QTest::newRow("word_2_as_an_end") << word2 << stem2;
	QTest::newRow("word_3_as_an_end") << word3 << stem3;
	QTest::newRow("word_4_as_an_end") << word4 << stem4;
	QTest::newRow("word_5_as_an_end") << word5 << stem5;
	QTest::newRow("word_6_end_in_stemm") << word6 << stem6;
	QTest::newRow("word_7_end_in_stemm") << word7 << stem7;
	QTest::newRow("word_8_end_in_stemm") << word8 << stem8;

	// �������� �� ������ ������ ���������
	wstring word9(L"����������");
	wstring stem9(L"�����");

	QTest::newRow("word_9_SUPERLATIVE") << word9 << stem9;

	wstring word10(L"���������");
	wstring stem10(L"�����");

	QTest::newRow("word_10_DERIVATIONAL") << word10 << stem10;

	//������ �� �������
	wstring word11(L"���������");
	wstring stem11(L"���������");
	QTest::newRow("word_11_nothing is deleted") << word11 << stem11;

	wstring word12(L"����");
	wstring stem12(L"���");
	QTest::newRow("word_12_NOUN") << word12 << stem12;

	wstring word13(L"���������");
	wstring stem13(L"�������");

	wstring word14(L"�������");
	wstring stem14(L"����");

	QTest::newRow("word_13_VERB") << word13 << stem13;
	QTest::newRow("word_14_VERB") << word14 << stem14;

	wstring word15(L"��������");
	wstring stem15(L"�����");
	QTest::newRow("word_15_REFLXIVE") << word15 << stem15;

	wstring word16(L"���������");
	wstring stem16(L"�����");
	QTest::newRow("word_16_PARTICIPLE") << word16 << stem16;


	wstring word17(L"���������");
	wstring stem17(L"�������");
	QTest::newRow("word_17_ADJECTIVE") << word17 << stem17;


	wstring word18(L"����������");
	wstring stem18(L"�����");
	QTest::newRow("word_18_RERFECT_GERUND") << word18 << stem18;

	//��������� ��������� ��� ��������
	wstring word19(L"�������������");
	wstring stem19(L"�������");

	wstring word20(L"��������������");
	wstring stem20(L"�����������");

	wstring word21(L"������������");
	wstring stem21(L"�����");

	QTest::newRow("word_18_several_endings") << word19 << stem19;
	QTest::newRow("word_20_several_endings") << word20 << stem20;
	QTest::newRow("word_21_several_endings") << word21 << stem21;
	
	wstring word22(L"���������������");
	wstring stem22(L"�������������");
	QTest::newRow("word_22_compound_word") << word22 << stem22;

	wstring word23(L"�������");
	wstring stem23(L"�������");
	QTest::newRow("word_23_nothing is deleted") << word23 << stem23;

	wstring word24(L"�����");
	wstring stem24(L"�����");
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

	// ���� ����� � ������ ������
	inputStr6 = stringToVec(L"� ���������� ��������� ��������");
	withoutStop6 = stringToVec(L"���������� ��������� ��������");

	//���� ����� � ������ � �������� ������
	inputStr1 = stringToVec(L"�� ������� �� ����� ������� ������� �������");
	withoutStop1 = stringToVec(L"������� ����� ������� ������� �������");

	//4 ���� ����� ������ 
	inputStr2 = stringToVec(L"��� ���� �� �������������� ��������");
	withoutStop2 = stringToVec(L"��������");

	//���� ����� � �����
	inputStr3 = stringToVec(L"������� ������� ���� ������� ��");
	withoutStop3 = stringToVec(L"������� ������� ���� �������");

	// ��� ���� ����
	inputStr4 = stringToVec(L"������ �������� ����� ������� ��������� �������");
	withoutStop4 = stringToVec(L"������ �������� ������� ��������� �������");

	//������ �� ���� ����
	inputStr7 = stringToVec(L"�� ������� ������� ����� ��� ������");

	// ���� ����� � �������� ������
	inputStr5 = stringToVec(L"��������� � ��������� ��� ��������");
	withoutStop5 = stringToVec(L"��������� ��������� ��������");
	inputStr8 = stringToVec(L"���������� ���� ��� �������� ���������� ����� ������� �����");
	withoutStop8 = stringToVec(L"���������� ���� ��� �������� ���������� ����� �����");
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

	inputStr1 = stringToVec(L"�� ������� ������� ����� ��� ������ �� ��������������");
	QTest::newRow("string_1_all_stop_words") << inputStr1 << processedStr1;

	inputStr2 = stringToVec(L"���� ��� �������");
	processedStr2 = stringToVec(L"���� ��� �������");

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
	processedStr1.push_back(L"����");
	processedStr1.push_back(L"���������");
	processedStr1.push_back(L"������");
	processedStr1.push_back(L"���������");
	processedStr1.push_back(L"����������");
	processedStr1.push_back(L"������"); 
	processedStr1.push_back(L"������");

	/////////////////////////////////
	QTest::newRow("String_1") << in1 << processedStr1;
	wstring in2 = loadFile("test_2.txt");
	/////////////////////////////////
	processedStr2.push_back(L"��������");
	processedStr2.push_back(L"��������");
	processedStr2.push_back(L"�������������");
	processedStr2.push_back(L"�����");
	processedStr2.push_back(L"�����");
	processedStr2.push_back(L"�������");

	/////////////////////////////////
	QTest::newRow("String_2") << in2 << processedStr2;

	wstring in3 = loadFile("test_3.txt");
	/////////////////////////////////
	processedStr3.push_back(L"�����");
	processedStr3.push_back(L"����������");
	processedStr3.push_back(L"��������");
	processedStr3.push_back(L"�������");
	processedStr3.push_back(L"���");
	processedStr3.push_back(L"�����");
	processedStr3.push_back(L"����������");
	processedStr3.push_back(L"��������");
	processedStr3.push_back(L"�������");
	processedStr3.push_back(L"���");
	processedStr3.push_back(L"�����");
	processedStr3.push_back(L"����������");
	processedStr3.push_back(L"��������");
	processedStr3.push_back(L"�������");
	processedStr3.push_back(L"���");
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
QTEST_MAIN(TestModules)
#include "main.moc"
