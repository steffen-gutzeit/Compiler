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
	Token *token1;
	Token *token2;
	Token *token3;
	Token *token4;
	Token *token5;
	Token *token6;
	Token *token7;
	Token *token8;
	Token *token9;
	Token *token10;
	Token *token11;
	Token *token12;
};

#endif /* SYMTABLE_H_ */
