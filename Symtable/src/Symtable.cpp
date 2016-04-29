/*
e * Symtable.cpp
 *
 *  Created on: 29.10.2014
 *      Author: root0r
 */

#include "Symtable.h"

#include "string.h"
#include <stdio.h>

Symtable::Symtable() {

	this->hashTable = new HashMap();
	initSymbols();

}

Symtable::~Symtable() {
	delete this->hashTable;
}

void Symtable::initSymbols(){
	char textWhile1[] = "while";
	char textIf1[] = "if";
	char textWhile2[] = "WHILE";
	char textIf2[] = "IF";

	//Fülle Symboltabelle mit Schluesselwörter
	insert(textWhile1, 4); 	//While: TT_WHILE = 4
	insert(textWhile2, 4); 	//While: TT_WHILE = 4
	insert(textIf1, 3);		//If:	 TT_IF = 3
	insert(textIf2, 3);		//If:	 TT_IF = 3
}

char *Symtable::insert(char* lexem, int typ) {
	char *key;;
	//Uebergebe Lexem an HashTable und bekomme KeyValue zurueck. Dieses wird im Token gespeichert.
	key = this->hashTable->addValue(typ, lexem);
	//printf("Symbol: %p \n", key);
	return key;

}


int Symtable::lookUp(char* lexem) {
	return this->hashTable->inList(lexem);
}
