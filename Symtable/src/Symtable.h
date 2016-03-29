/*
 * Symtable.h
 *
 *  Created on: 29.10.2014
 *      Author: root0r
 */

#include <stdint.h>
#include "../../Token/src/Token.h"
#include "../../HashMap/src/HashMap.h"
#include "../../LinkedList/src/LinkedList.h"

#ifndef SYMTABLE_H_
#define SYMTABLE_H_

class Symtable {
public:
	Symtable();
	virtual ~Symtable();
	void insert(char* lexem, int typ);
	int lookUp(char* lexem);

private:
	void initHashMap();
	HashMap *hashTable;
};

#endif /* SYMTABLE_H_ */
