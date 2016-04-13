#include "HashMap.h"
#include "../../LinkedList/src/LinkedList.h"

#include <stdlib.h>

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

void HashMap::addValue(uint8_t type, char *lexem) {
	//LinkedList::list *currentList = (LinkedList::list*) malloc(sizeof(LinkedList::list));
	this->hashValue = hashLexem(lexem);

	//currentList = &(hashTable[this->hashValue].list);
	this->push(&(hashTable[this->hashValue].list), type, lexem);
}

bool HashMap::inList(char *lexem) {
	bool inList = false;
	LinkedList::list *currentList = (LinkedList::list*) malloc(sizeof(LinkedList::list));
	this->hashValue = hashLexem(lexem);

	currentList = &(hashTable[this->hashValue].list);
	inList= this->searchInList(currentList, lexem);

	return inList;
}
