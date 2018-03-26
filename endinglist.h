#ifndef ENDINGLIST_H
#define ENDINGLIST_H
#include <QString>
#include <QVector>
enum ending {
    PERFECTIVE_GERUND_1,
    PERFECTIVE_GERUND_2,
    ADJECTIVE,
    PARTICIPLE_1,
    PARTICIPLE_2,
    REFLEXIVE,
    VERB_1,
    VERB_2,
    NOUN,
    SUPERLATIVE,
    DERIVATIONAL
};
typedef QVector<QString> endingList;
class EndingList
{
public:
    EndingList();
    endingList  perGerund_1;
    endingList  perGerund_2;
    endingList  adjective;
    endingList  participle_1;
    endingList  participle_2;
    endingList  reflexive;
    endingList  verb_1;
    endingList  verb_2;
    endingList  derivational;
    endingList  noun;
    endingList  superlative;

    endingList getEnding(ending end);
};

#endif // endingListLIST_H
