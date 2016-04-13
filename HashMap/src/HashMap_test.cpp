#include "../../HashMap/src/HashMap.h"
#include "../../LinkedList/src/LinkedList.h"

using namespace std;

int main() {
	HashMap *h = new HashMap(512);

	char test0[16] = "12";
	h->addValue(1, test0);

	char test1[16] = "11";
	h->addValue(2, test1);

	char test2[16] = "WHILE";
	h->addValue(4, test2);

	char test3[16] = "if";
	h->addValue(3, test3);

	char test4[16] = "12";
	h->addValue(3, test4);

	char test5[16] = "tralalala";
	h->addValue(98, test5);

	char test6[16] = "31";
	h->addValue(0013, test6);

	char test7[16] = "33";
	h->addValue(100, test7);

	return 0;
}
