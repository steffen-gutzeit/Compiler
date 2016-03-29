/*
 * LinkedList.h
 *
 *  Created on: 27.10.2014
 *      Author: root0r
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdint.h>

class LinkedList {
public:
	struct listNode{
		char lexem[512];
		int typ;
		struct listNode *next;
	};

	LinkedList();
	virtual ~LinkedList();
	struct listNode *createList(char* lexem, int typ);
	struct listNode *add(char *lexem, int typ);
	void printListValues();

	void setCurrent(listNode* newCurrent);
	void setHead(listNode* newHead);
private:
	struct listNode *head;
	struct listNode *current;
};

#endif /* LINKEDLIST_H_ */
