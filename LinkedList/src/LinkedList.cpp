/*
 * LinkedList.cpp
 *
 *  Created on: 27.10.2014
 *      Author: root0r
 */

#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

LinkedList::LinkedList() {
}

LinkedList::~LinkedList() {

}

void LinkedList::printList(list * head) {
	list *current = head;

	uint16_t i = 0;
    while (current != NULL) {
    	i = 0;
        printf("%d - ", current->index);
	    while (current->lexem[i] != '\0') {
	    	printf("%c", current->lexem[i]);
	    	i++;
	    }
	    printf("\n");
        current = current->next;
    }
}

char *LinkedList::push(list * head, int val, char *lexem) {
	uint16_t i = 0;
	bool createFlag = true;
	list *current = head;
	char *key;

    while (current->next != NULL) {
    	current = current->next;

        if (this->sameStrings(lexem, current->lexem)) {
        	createFlag = false;
        	key = &current->lexem[0];
        	//printf("Liste1: %p \n", &current->lexem[0]);
        }

    }



    if (createFlag) {
		current->next = (LinkedList::list*) malloc(sizeof(LinkedList::list));

		while (lexem[i] != '\0') {
			current->next->lexem[i] = lexem[i];
			i++;
		}
		current->next->index = val;
		current->next->next = NULL;

		key = &current->next->lexem[0];
		//printf("Liste2: %p \n", &current->next->lexem[0]);
    }

    //cout << "Liste: " << &current->next->lexem[0] << endl;


    //Gebe index des Lexem zurueck
    return key;
}

bool LinkedList::searchInList(list *currentList, char *lexem) {
	list *current = currentList;

    while (current->next != NULL) {
    	current = current->next;

        if (this->sameStrings(lexem, current->lexem)) {
        	return 1;
        }
    }

    return 0;
}

bool LinkedList::sameStrings(char *value, char *compare) {
	uint16_t i = 0;

	if (this->strlen(value) > this->strlen(compare)) {
		while (value[i] != '\0') {
			if (value[i] != compare[i]) {
				return false;
			}
			i++;
		}
	} else {
		while (compare[i] != '\0') {
			if (compare[i] != value[i]) {
				return false;
			}
			i++;
		}
	}

	//printf("Teste: %s mit %s \n", value, compare);

	return true;
}

uint16_t LinkedList::strlen(char *value) {
	uint16_t stringIndex = 0;
	while (value[stringIndex] != '\0') {
		stringIndex++;
	}

	return stringIndex;
}
