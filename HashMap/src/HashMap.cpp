#include "HashMap.h"
#include "../../LinkedList/src/LinkedList.h"

#include <stdlib.h>
#include <stdio.h>

HashMap::HashMap() {
	this->size = 512;
	this->hashValue = 1;
}

HashMap::~HashMap() {

}

uint16_t HashMap::hashLexem(char *lexem) {
	uint16_t i = 0;
	this->hashValue = 1;

	while ((lexem[i] != '\0') & (lexem[i] != '\n')) {
		this->hashValue *= lexem[i++];
		this->hashValue %= this->size;
		this->hashValue ++;
	}

	return (this->hashValue %= this->size);
}
char *HashMap::addValue(uint8_t type, char *lexem) {
	char *key;

	//LinkedList::list *currentList = (LinkedList::list*) malloc(sizeof(LinkedList::list));
	this->hashValue = hashLexem(lexem);

	//currentList = &(hashTable[this->hashValue].list);
	key = this->push(&(hashTable[this->hashValue].list), type, lexem);
	//printf("Hashmap: %p \n", key);
	return key;
}

bool HashMap::inList(char *lexem) {
	bool inList = false;
	LinkedList::list *currentList = (LinkedList::list*) malloc(sizeof(LinkedList::list));
	this->hashValue = hashLexem(lexem);

	currentList = &(hashTable[this->hashValue].list);
	inList= this->searchInList(currentList, lexem);

	return inList;
}
