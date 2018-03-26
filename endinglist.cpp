#include "endinglist.h"
#include <QTextCodec>
QString russian(const char * text)
{
   // подбираем нужную кодировку, другой вариант UTF8
   return QTextCodec::codecForName("CP1251")->toUnicode(text);
}
EndingList::EndingList()
{

    perGerund_1.push_back(russian("вши"));
    perGerund_1.push_back(russian("вшись"));
    perGerund_1.push_back(russian("в"));

    perGerund_2.push_back(russian("ив"));
    perGerund_2.push_back(russian("ивши"));
    perGerund_2.push_back(russian("ившись"));
    perGerund_2.push_back(russian("ыв"));
    perGerund_2.push_back(russian("ывши"));
    perGerund_2.push_back(russian("ывшись"));

    participle_1.push_back(russian("ем"));
    participle_1.push_back(russian("нн"));
    participle_1.push_back(russian("вш"));
    participle_1.push_back(russian("ющ"));
    participle_1.push_back(russian("щ"));

    reflexive.push_back(russian("с€"));
    reflexive.push_back(russian("сь"));

    verb_1.push_back(russian("ла"));
    verb_1.push_back(russian("на"));
    verb_1.push_back(russian("ете"));
    verb_1.push_back(russian("ли"));
    verb_1.push_back(russian("й"));
    verb_1.push_back(russian("л"));
    verb_1.push_back(russian("ем"));
    verb_1.push_back(russian("н"));
    verb_1.push_back(russian("ло"));
    verb_1.push_back(russian("но"));
    verb_1.push_back(russian("ет"));
    verb_1.push_back(russian("ют"));
    verb_1.push_back(russian("ны"));
    verb_1.push_back(russian("ть"));
    verb_1.push_back(russian("ешь"));
    verb_1.push_back(russian("нно"));

    verb_2.push_back(russian("ила"));
    verb_2.push_back(russian("ыла"));
    verb_2.push_back(russian("ена"));
    verb_2.push_back(russian("ейте"));
    verb_2.push_back(russian("уйте"));
    verb_2.push_back(russian("или"));
    verb_2.push_back(russian("ыли"));
    verb_2.push_back(russian("ей"));
    verb_2.push_back(russian("уй"));
    verb_2.push_back(russian("ил"));
    verb_2.push_back(russian("ыл"));
    verb_2.push_back(russian("им"));
    verb_2.push_back(russian("ым"));
    verb_2.push_back(russian("ен"));
    verb_2.push_back(russian("ило"));
    verb_2.push_back(russian("ыло"));
    verb_2.push_back(russian("ено"));
    verb_2.push_back(russian("€т"));
    verb_2.push_back(russian("ует"));
    verb_2.push_back(russian("уют"));
    verb_2.push_back(russian("ит"));
    verb_2.push_back(russian("ыт"));
    verb_2.push_back(russian("ены"));
    verb_2.push_back(russian("ить"));
    verb_2.push_back(russian("ыть"));
    verb_2.push_back(russian("ишь"));
    verb_2.push_back(russian("ую"));
    verb_2.push_back(russian("ю"));

    participle_2.push_back(russian("ивш"));
    participle_2.push_back(russian("ывш"));
    participle_2.push_back(russian("ующ"));

    noun.push_back(russian("а"));
    noun.push_back(russian("ев"));
    noun.push_back(russian("ов"));
    noun.push_back(russian("ие"));
    noun.push_back(russian("ье"));
    noun.push_back(russian("е"));
    noun.push_back(russian("и€ми"));
    noun.push_back(russian("€ми"));
    noun.push_back(russian("ами"));
    noun.push_back(russian("еи"));
    noun.push_back(russian("ии"));
    noun.push_back(russian("и"));
    noun.push_back(russian("ией"));
    noun.push_back(russian("ей"));
    noun.push_back(russian("ой"));
    noun.push_back(russian("й"));
    noun.push_back(russian("ий"));
    noun.push_back(russian("и€м"));
    noun.push_back(russian("€м"));
    noun.push_back(russian("ам"));
    noun.push_back(russian("ом"));
    noun.push_back(russian("о"));
    noun.push_back(russian("у"));
    noun.push_back(russian("ах"));
    noun.push_back(russian("и€х"));
    noun.push_back(russian("€х"));
    noun.push_back(russian("ы"));
    noun.push_back(russian("ь"));
    noun.push_back(russian("ию"));
    noun.push_back(russian("ью"));
    noun.push_back(russian("ю"));
    noun.push_back(russian("и€"));
    noun.push_back(russian("ь€"));
    noun.push_back(russian("€"));

    superlative.push_back(russian("ейш"));
    superlative.push_back(russian("ейше"));

    derivational.push_back(russian("ост"));
    derivational.push_back(russian("ость"));

    adjective.push_back(russian("ee"));
    adjective.push_back(russian("иe"));
    adjective.push_back(russian("ыe"));
    adjective.push_back(russian("ыми"));
    adjective.push_back(russian("ими"));
    adjective.push_back(russian("eй"));
    adjective.push_back(russian("ий"));
    adjective.push_back(russian("ый"));
    adjective.push_back(russian("ой"));
    adjective.push_back(russian("eм"));
    adjective.push_back(russian("им"));
    adjective.push_back(russian("ым"));
    adjective.push_back(russian("ом"));
    adjective.push_back(russian("eго"));
    adjective.push_back(russian("ого"));
    adjective.push_back(russian("eму"));
    adjective.push_back(russian("ому"));
    adjective.push_back(russian("их"));
    adjective.push_back(russian("ых"));
    adjective.push_back(russian("ую"));
    adjective.push_back(russian("юю"));
    adjective.push_back(russian("а€"));
    adjective.push_back(russian("€€"));
    adjective.push_back(russian("ою"));
    adjective.push_back(russian("eю"));
}
endingList EndingList:: getEnding(ending end)
{
    switch(end)
    {
    case PERFECTIVE_GERUND_1:
        return perGerund_1;
    case PERFECTIVE_GERUND_2:
        return perGerund_2;
    case PARTICIPLE_1:
        return participle_1;

    case PARTICIPLE_2:
        return participle_2;
    case REFLEXIVE:
        return reflexive;
    case ADJECTIVE:
        return adjective;
    case NOUN:
        return noun;
    case VERB_1:
        return verb_1;
    case VERB_2:
        return verb_2;
    case SUPERLATIVE:
        return superlative;
    case DERIVATIONAL:
        return derivational;
    }
}
