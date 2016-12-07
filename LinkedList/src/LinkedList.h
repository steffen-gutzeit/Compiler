/*
 * LinkedList.h
 *
 *  Created on: 27.10.2014
 *      Author: root0r
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdint.h>
#include <iostream>

#include "../../Token/src/Token.h"

class LinkedList {
public:
	typedef struct node {
		uint16_t index;
		//char lexem[512];
		Token* token;
	    struct node * next;
	} list;

	LinkedList();
	virtual ~LinkedList();

	char* pushToken(list * head, Token* token);
	void printList(list * head, uint16_t hash);
	Token *lookupLexem(list *head, char *lexem);


private:
	bool sameStrings(char *value, char *compare);
	uint16_t strlen(char *value);
};

#endif /* LINKEDLIST_H_ */
