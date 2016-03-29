/*
 * LinkedList.cpp
 *
 *  Created on: 27.10.2014
 *      Author: root0r
 */

#include "LinkedList.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

LinkedList::LinkedList() {
	current = NULL;
	head = NULL;
}

LinkedList::~LinkedList() {

}


struct LinkedList::listNode* LinkedList::createList(char* lexem, int typ) {
	listNode *listPointer = (struct listNode*) malloc( sizeof (struct listNode) );

	if (listPointer != NULL) {
		int i = 0;
				while (lexem[i] != '\0'){
					listPointer->lexem[i] = lexem[i];
					i++;
				}
		//listPointer->lexem = *lexem;
		listPointer->typ = typ;
		listPointer->next = NULL;
	}

	head = listPointer;
	current = listPointer;
	return listPointer;
}

struct LinkedList::listNode* LinkedList::add(char *lexem, int typ) {
	listNode *listPointer = (struct listNode*) malloc( sizeof (struct listNode) );

	if (listPointer != NULL) {
		int i = 0;
		while (lexem[i] != '\0'){
			listPointer->lexem[i] = lexem[i];
			i++;
		}
		//listPointer->lexem = lexem;
		listPointer->typ = typ;
		listPointer->next = NULL;
	}

	current->next = listPointer;
	current = listPointer;

	//cout << "Symtable " << lexem << endl;

	return listPointer;
}

void LinkedList::setCurrent (struct listNode* newCurrent) {
	current = newCurrent;
}

void LinkedList::setHead (struct listNode* newHead) {
	head = newHead;
}

void LinkedList::printListValues() {
	current = head;

	cout << head->lexem << endl;

	while (current->next != NULL) {
		current = current->next;
		cout << current->lexem << endl;
	}
}

