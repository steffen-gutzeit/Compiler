#ifndef HashMap_H_
#define HashMap_H_

#include <stdint.h>
#include "../../LinkedList/src/LinkedList.h"

class HashMap : public LinkedList {
public:
	HashMap();
	virtual ~HashMap();

	uint16_t hashLexem(char *lexem);
	void addValue(uint8_t type, char *lexem);
	bool inList(char *lexem);

private:
	struct hashTable {
		LinkedList::node list;
	}hashTable[512];

	uint16_t hashValue;
	uint16_t size;
};

#endif /* HASHMAP_H_ */
