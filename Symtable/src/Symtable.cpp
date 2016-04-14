/*
e * Symtable.cpp
 *
 *  Created on: 29.10.2014
 *      Author: root0r
 */

#include "Symtable.h"

#include "string.h";

Symtable::Symtable() {

	this->hashTable = new HashMap();
	initSymbols();

}

Symtable::~Symtable() {
	delete this->hashTable;
}

void Symtable::initSymbols(){
	char textWhile[] = "while";
	char textIf[] = "if";

	//Fülle Symboltabelle mit Schluesselwörter
	insert(textWhile, 4); 	//While: TT_WHILE = 4
	insert(textIf, 3);	//If:	 TT_IF = 3
}

void Symtable::insert(char* lexem, int typ) {
	//Uebergebe Lexem an HashTable und bekomme KeyValue zurueck. Dieses wird im Token gespeichert.
	this->hashTable->addValue(typ, lexem);

}


int Symtable::lookUp(char* lexem) {
	return this->hashTable->inList(lexem);
}
