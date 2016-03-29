/*
 * Symtable.cpp
 *
 *  Created on: 29.10.2014
 *      Author: root0r
 */

#include "Symtable.h"

Symtable::Symtable() {
	this->hashTable = new HashMap(512);
}

Symtable::~Symtable() {
	delete this->hashTable;
}

void Symtable::insert(char* lexem, int typ) {
	this->hashTable->addHashValue(lexem, typ);
}

int Symtable::lookUp(char* lexem) {
	return this->hashTable->searchValue(lexem);
}
