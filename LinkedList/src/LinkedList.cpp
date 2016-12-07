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

/*
 * Überprüft ob 2 Lexem identisch sind
 */
bool LinkedList::sameStrings(char *value, char *compare) {
	uint16_t i = 0;

	//printf("Teste: %s mit %s \n", value, compare);

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

	return true;
}

/*
 * Ermittelt die Länge eines Lexems
 */
uint16_t LinkedList::strlen(char *value) {
	uint16_t stringIndex = 0;
	while (value[stringIndex] != '\0') {
		stringIndex++;
	}

	return stringIndex;
}

/*
 * Fügt ein Token in die Linked List hinzu
 */
char *LinkedList::pushToken(list * head, Token* token) {

	//Parameter ob neuer Eintrag erstellt werden muss
	bool createFlag = true;

	//Aktuelle Head Position (Hash Wert)
	list *current = head;

	char *key;

	//Index innerhalb der Liste
	uint16_t index = current->index;

	//Prüfe ob es schon existiert
	while (current->next != NULL) {

		//Falls es schon existiert gebe Schlüsselwert zurück und füge nichts ein
		//cout << "Vergleiche " << token->getLexem() << " mit " <<  current->next->token->getLexem() << " Head: " << current << endl;
		if (this->sameStrings(token->getLexem(), current->next->token->getLexem())) {
			createFlag = false;
			key = &current->next->token->getLexem()[0];
			//cout << token->getLexem() << " existiert schon" << endl;
			//printf("Liste1: %p \n", &current->lexem[0]);
		}


		//Gehe zum nächsten Listeneintrag und setze den Index hoch
		current = current->next;
		index++;

	}


	//Erstelle neuen Eintrag in der Linked List
	if (createFlag) {

		//Speicherplatz allokieren
		current->next = (LinkedList::list*) malloc(sizeof(LinkedList::list));

		//Setze Token und INdex
		current->next->token = token;
		current->next->index = index;

		//Nächster Listeneintrag auf NULL setzen
		current->next->next = NULL;

		//Der Keywert scheint irgendwie überflüssig zu sein (7.12.16)
		key = &current->next->token->getLexem()[0];

	}

	//Gebe index des Lexem zurueck
	return key;

}

/*
 * Versuche ein Lexem in der aktuellen Liste zu finden und gebe das Token zurück
 */
Token *LinkedList::lookupLexem(list *head, char* lexem){
	list *current = head;
	Token *token = NULL;

	//Durchlaufe den LinkedList Strang und Versuche das Lexem zu finden
	while (current->next != NULL) {

		//Vergleiche Lexem
		if (this->sameStrings(lexem, current->next->token->getLexem())) {
			//Gab es einen Treffer setze den Rückgabewert auf dieses Token
			token = current->next->token;
		}

		//Gehe zum nächsten Listeneintrag
		current = current->next;
	}

	//Gebe NULL zurück falls es nicht gefunden wurde
	return token;

}

/*
 * Gebe komplette Liste aus
 */
void LinkedList::printList(list * head, uint16_t hash) {
	list *current = head;

	//Durchlaufe die LinkedList bis kein Eintrag mehr vorhanden ist
    while (current->next != NULL) {

    	//Gebe die Informationen der LinkedList aus
    	cout << "Symtable: " << head << "\tHashwert: " << hash << "\tIndex: " << current->next->index << "\tTokenTyp: " << current->next->token->getTokenType() << "\tLexem: " << current->next->token->getLexem() << endl;

    	//Gehe zum nächsten Listeneintrag
        current = current->next;
    }
}
