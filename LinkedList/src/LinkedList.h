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
	typedef struct node {
		uint16_t index;
		char lexem[512];
	    struct node * next;
	} list;

	LinkedList();
	virtual ~LinkedList();

	void printList(list *head);
	char *push(list *head, int val, char *lexem);
	bool searchInList(list *currentList, char *lexem);
private:
	bool sameStrings(char *value, char *compare);
	uint16_t strlen(char *value);
};

#endif /* LINKEDLIST_H_ */
