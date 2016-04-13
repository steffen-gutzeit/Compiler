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

	void printList(list * head);
	void push(list * head, int val, char *lexem);

private:
	uint16_t strlen(char *value);
	bool sameStrings(char *value, char *compare);
};

#endif /* LINKEDLIST_H_ */
