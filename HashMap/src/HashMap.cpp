#include "HashMap.h"
#include "../../LinkedList/src/LinkedList.h"

#include <iostream>
#include <stdint.h>
#include <stdlib.h>

using namespace std;

HashMap::HashMap(uint32_t size) {
	this->currentFillingLevel = 0;
	this->hashValue = 1;

	for (uint32_t i = 0; i < size; i++) {
		this->hashTable[i].linkedList.lexem[0] = '\0';
	}

	/*this->hashTable[this->hash("if")].linkedList.lexem = "if";
	this->hashTable[this->hash("IF")].linkedList.lexem = "IF";
	this->hashTable[this->hash("while")].linkedList.lexem = "while";
	this->hashTable[this->hash("WHILE")].linkedList.lexem = "WHILE";*/

}

HashMap::~HashMap() {

}

void HashMap::addHashValue(char *lexem, int typ) {
	LinkedList::listNode *listPointer = (LinkedList::listNode*) malloc(sizeof(LinkedList::listNode));
	bool createFlag = true;
	this->hashValue = this->hash(lexem);

	//cout << "addHashValue " << lexem << " "<< this->hashValue << endl;

	listPointer = &(this->hashTable[this->hashValue].linkedList);

		while (listPointer->next != NULL) {
			if (this->compareString(listPointer->next->lexem, lexem)){
				createFlag = false;
			}
			listPointer = listPointer->next;
		}

		if (createFlag){
			this->setCurrent(listPointer);
			this->add(lexem, typ);
		}

}

int HashMap::searchValue(char *lexem) {
	int returnValue = 0;
	LinkedList::listNode *listPointer = (LinkedList::listNode*) malloc(sizeof(LinkedList::listNode));

	this->hashValue = this->hash(lexem);
	while (listPointer->next != NULL) {
		if(!this->compareString(this->hashTable[this->hashValue].linkedList.lexem, lexem)) {
			returnValue = this->hashTable[this->hashValue].linkedList.typ;
			break;
		}
	}

	return returnValue;
}

uint32_t HashMap::hash(char *input) {
	uint16_t i = 0;
	hashValue = 1;

	while ((input[i] != '\0') & (input[i] != '\n')) {
		hashValue *= input[i++];
		hashValue %= 512;
		hashValue ++;
	}

	return hashValue %= 512;
}

bool HashMap::compareString(char *value, char *compare){
	int i = 0;
	while((value[i] != '\0') | (compare[i] != '\0')){
		//cout << value[i] << " | " << compare[i] << endl;
		if(value[i] != compare[i]){
			return false;
		}
		i++;
	}
	return true;


}
