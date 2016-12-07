/*
 * Symtable.h
 *
 *  Created on: 29.10.2014
 *      Author: root0r
 */

#include <stdint.h>
#include <iostream>
#include "../../Token/src/Token.h"
#include "../../HashMap/src/HashMap.h"
#include "../../LinkedList/src/LinkedList.h"

#ifndef SYMTABLE_H_
#define SYMTABLE_H_

class Symtable {
public:
	Symtable();
	virtual ~Symtable();

	void initSymbols();
	char *insertToken(Token* token);
	void printHashMap();
	Token *lookup(char* lexem);

private:
	HashMap *hashTable;
	Token *token;
};

#endif /* SYMTABLE_H_ */
