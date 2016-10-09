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
	char textWhile1[]	= "while";
	char textIf1[] 		= "if";
	char textWrite1[]	= "write";
	char textRead1[]	= "read";
	char textInt1[]		= "int";
	char textElse1[]	= "else";

	char textWhile2[] 	= "WHILE";
	char textIf2[] 		= "IF";
	char textWrite2[]	= "WRITE";
	char textRead2[]	= "READ";
	char textInt2[]		= "INT";
	char textElse2[]	= "ELSE";

	//Fülle Symboltabelle mit Schluesselwörter
	insert(textWhile1, 4); 	//While: TT_WHILE = 4
	insert(textWhile2, 4); 	//While: TT_WHILE = 4

	insert(textIf1, 3);		//If:	 TT_IF = 3
	insert(textIf2, 3);		//If:	 TT_IF = 3

	insert(textWrite1, 3);	//Write: TT_WRITE= 28
	insert(textWrite2, 3);	//Write: TT_WRITE= 28

	insert(textRead1, 3);	//Read:	 TT_READ = 27
	insert(textRead2, 3);	//Read:	 TT_READ = 27

	insert(textInt1, 3);	//Int:	 TT_INT = 30
	insert(textInt2, 3);	//Int:	 TT_INT = 30

	insert(textElse1, 3);	//Else:	 TT_ELSE = 29
	insert(textElse2, 3);	//Else:	 TT_ELSE = 29
}

char *Symtable::insert(char* lexem, int typ) {
	char *key;
	//Uebergebe Lexem an HashTable und bekomme KeyValue zurueck. Dieses wird im Token gespeichert.
	key = this->hashTable->addValue(typ, lexem);
	//printf("Symbol: %p \n", key);
	return key;
}


bool Symtable::lookUp(char* lexem) {
	return this->hashTable->inList(lexem);
}

