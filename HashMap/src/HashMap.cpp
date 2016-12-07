#include "HashMap.h"
#include "../../LinkedList/src/LinkedList.h"

#include <stdlib.h>
#include <stdio.h>

#include <iostream>

HashMap::HashMap() {
	this->size = 512;
	this->hashValue = 1;
}

HashMap::~HashMap() {

}

/*
 * Ermittelt eines Hashwert aus dem übergebenen Lexem
 */
uint16_t HashMap::hashLexem(char *lexem) {
	uint16_t i = 0;
	this->hashValue = 1;

	while ((lexem[i] != '\0') & (lexem[i] != '\n')) {
		//Multiplizieren aktuellen Hash mit neuem ASCII Wert
		this->hashValue *= lexem[i++];
		//Modulo 512 Rechnung
		this->hashValue %= this->size;
		//Erhöhe Hash Wert um 1
		this->hashValue ++;
	}

	return (this->hashValue %= this->size);
}

/*
 * Fügt ein Token in die Symboltabelle ein
 */
char *HashMap::addToken(Token* token){

	char* key;

	//Hash Wert ermitteln
	this->hashValue = hashLexem(token->getLexem());

	//In die Linked List eintragen
	key = this->pushToken(&(hashTable[this->hashValue].list), token);

	return key;
}

/*
 * Prüft ob ein Lexem in der Symboltabelle vorhanden ist
 */
Token *HashMap::lookup(char* lexem){

	uint16_t hashValue;
	Token *token;

	//Hashe Lexem
	hashValue = hashLexem(lexem);

	//Durchlaufe Index und suche nach Lexem
	token = this->lookupLexem(&(hashTable[hashValue].list), lexem);

	//Falls gefunden gebe das Token zurück
	return token;
}

/*
 * Gibt die komplette Symboltabelle aus
 */
void HashMap::printHashMap(){

	//Durchlaufe alle Möglichen Headindexe (Hashwerte)
	for(uint16_t i=0; i < 512; i++){
		this->printList(&(hashTable[i].list), i);
	}

}
