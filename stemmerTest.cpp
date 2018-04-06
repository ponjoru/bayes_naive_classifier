#include <QtTest/QtTest>
#include <string>
#include"stemmer.h"

using namespace std;
Q_DECLARE_METATYPE(wstring)
class TestTokenization : public QObject 
{
	Q_OBJECT
		private slots:
	void test_stemmer_data();
	void test_stemmer();
};
void TestTokenization::test_stemmer_data()
{
	QTest::addColumn<wstring>("Word");
	QTest::addColumn<wstring>("Stem");
	//политика и формы слова
	wstring word1(L"политический");
	wstring stem1(L"политическ");

	wstring word2(L"политика");
	wstring stem2(L"политик"); 

	wstring word3(L"политикою");
	wstring stem3(L"политик"); 
	
	wstring word4(L"политизировать");
	wstring stem4(L"политизирова"); 

	wstring word5(L"политически");
	wstring stem5(L"политическ"); 

	wstring word6(L"политология");
	wstring stem6(L"политолог"); 

	QTest::newRow("word_1") << word1 << stem1;
	QTest::newRow("word_2") << word2 << stem2;
	QTest::newRow("word_3") << word3 << stem3;
	QTest::newRow("word_4") << word4 << stem4;
	QTest::newRow("word_5") << word5 << stem5;
	QTest::newRow("word_6") << word6 << stem6;

	//экономика и формы слова
	wstring word7(L"экономика");
	wstring stem7(L"экономик"); 

	wstring word8(L"экономического");
	wstring stem8(L"экономическ");

	wstring word9(L"экономический");
	wstring stem9(L"экономическ");

	wstring word10(L"экономическому");
	wstring stem10(L"экономическ");

	wstring word11(L"экономист");
	wstring stem11(L"экономист"); 

	wstring word12(L"экономный");
	wstring stem12(L"экономн"); 

	wstring word13(L"макроэкономика");
	wstring stem13(L"макроэкономик"); 

	wstring word14(L"экономических");
	wstring stem14(L"экономическ");

	QTest::newRow("word_7") << word7 << stem7;
	QTest::newRow("word_8") << word8 << stem8;
	QTest::newRow("word_9") << word9 << stem9;
	QTest::newRow("word_10") << word10 << stem10;
	QTest::newRow("word_11") << word11 << stem11;
	QTest::newRow("word_12") << word12 << stem12;
	QTest::newRow("word_13") << word13 << stem13;
	QTest::newRow("word_14") << word14 << stem14;
	//другие слова
	wstring word15(L"дисквалификация");
	wstring stem15(L"дисквалификац"); 

	wstring word16(L"спортивный");
	wstring stem16(L"спортивн");

	wstring word17(L"новостной");
	wstring stem17(L"новостн");

	wstring word18(L"информационный");
	wstring stem18(L"информацион");

	wstring word19(L"происшествие");
	wstring stem19(L"происшеств");

	wstring word20(L"отстранившись");
	wstring stem20(L"отстран");

	QTest::newRow("word_15") << word15 << stem15;
	QTest::newRow("word_16") << word16 << stem16;
	QTest::newRow("word_17") << word17 << stem17;
	QTest::newRow("word_18") << word18 << stem18;
	QTest::newRow("word_19") << word19 << stem19;
	QTest::newRow("word_20") << word20 << stem20;

	wstring word21(L"страхующийся");
	wstring stem21(L"страх");

	wstring word22(L"пополняясь");
	wstring stem22(L"пополн");

	wstring word23(L"крупнейшее");
	wstring stem23(L"крупн");

	wstring word24(L"стремящихся");
	wstring stem24(L"стремя");

	wstring word25(L"опасность");
	wstring stem25(L"опасн");

	QTest::newRow("word_21") << word21 << stem21;
	QTest::newRow("word_22") << word22 << stem22; 
	QTest::newRow("word_23") << word23 << stem23; 
	QTest::newRow("word_24") << word24 << stem24;
	QTest::newRow("word_25") << word25 << stem25;
}
void TestTokenization::test_stemmer()
{
	QFETCH(wstring, Word);
	QFETCH(wstring, Stem);
	stemming::russian_stem <wstring> stem;
	stem(Word);
	QCOMPARE(Word, Stem);
}
QTEST_MAIN(TestTokenization)
#include "stemmerTest.moc"
