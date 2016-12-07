#ifndef HashMap_H_
#define HashMap_H_

#include <stdint.h>
#include <iostream>
#include "../../LinkedList/src/LinkedList.h"
#include "../../Token/src/Token.h"

class HashMap : public LinkedList {
public:
	HashMap();
	virtual ~HashMap();

	uint16_t hashLexem(char *lexem);
	char* addToken(Token* token);
	void printHashMap();
	Token *lookup(char* lexem);

private:
	struct hashTable {
		LinkedList::node list;
	}hashTable[512];

	uint16_t hashValue;
	uint16_t size;
};

#endif /* HASHMAP_H_ */
