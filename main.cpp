#include "BayesClassifier.h"

// 1. добавление поля result в класс байесов классификатор => метод getResult
// 2. вынесение в отдельный класс вычислителя вероятностей (но неудобный доступ к мапам) => можно закинуть все мапы в отдельный класс данных и передавать их в класс вычислителя по ссылке
// 3. updateExeMap кто пишет?
// 4. согласование потоков wcout и cout
// 5. training_map[classname][data[i]]++ стремный код? как поправить
int main(void)
{
	std::locale::global(std::locale(""));
	std::ios::sync_with_stdio(false);
	BayesClassifier b_cl;
	b_cl.run();
	return 0;
}