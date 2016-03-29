#ifndef HashMap_H_
#define HashMap_H_

#include <stdint.h>
#include "../../LinkedList/src/LinkedList.h"
#include "../../Token/src/Token.h"

class HashMap : public LinkedList {
public:
	HashMap(uint32_t size);
	virtual ~HashMap();

	void addHashValue(char *lexem, int typ);
	void flush();
	int searchValue(char *lexem);

private:
	struct hashTable {
		int key;
		LinkedList::listNode linkedList;
	}hashTable[512];

	uint32_t hash(char *input);
	bool compareString(char *value, char *compare);

	int32_t hashValue;
	uint16_t currentFillingLevel;




};

#endif /* HASHMAP_H_ */
