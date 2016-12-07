/*
e * Symtable.cpp
 *
 *  Created on: 29.10.2014
 *      Author: root0r
 */

#include "Symtable.h"

#include "string.h"
#include <stdio.h>

Symtable::Symtable() {

	this->hashTable = new HashMap();
	this->token = NULL;
	initSymbols();

}

Symtable::~Symtable() {
	delete this->hashTable;
}

/*
 * Initialisiert die Symboltabelle und fügt die ersten Token hinzu
 */
void Symtable::initSymbols(){
	char textWhile1[]	= "while";
	char textIf1[] 		= "if";
	char textWrite1[]	= "write";
	char textRead1[]	= "read";
	char textInt1[]		= "int";
	char textElse1[]	= "else";

	char textWhile2[] 	= "WHILE";
	char textIf2[] 		= "IF";
	char textElse2[]	= "ELSE";

	//Nicht sicher ob das notwendig ist (7.12.16)
	char textWrite2[]	= "WRITE";
	char textRead2[]	= "READ";
	char textInt2[]		= "INT";


	//Estelle Token und füge diese in die Symboltabelle ein
	this->insertToken(token = new Token(0, 0, token->TT_WHILE, textWhile1));
	this->insertToken(token = new Token(0, 0, token->TT_WHILE, textWhile2));

	this->insertToken(token = new Token(0, 0, token->TT_IF, textIf1));
	this->insertToken(token = new Token(0, 0, token->TT_IF, textIf2));

	this->insertToken(token = new Token(0, 0, token->TT_ELSE, textElse1));
	this->insertToken(token = new Token(0, 0, token->TT_ELSE, textElse2));

	this->insertToken(token = new Token(0, 0, token->TT_INT, textInt1));
	this->insertToken(token = new Token(0, 0, token->TT_READ, textRead1));
	this->insertToken(token = new Token(0, 0, token->TT_WRITE, textWrite1));

	//Nicht sicher ob das notwendig ist (7.12.16)
	this->insertToken(token = new Token(0, 0, token->TT_INT, textInt2));
	this->insertToken(token = new Token(0, 0, token->TT_READ, textRead2));
	this->insertToken(token = new Token(0, 0, token->TT_WRITE, textWrite2));

}

/*
 * Suche nach übergebenem Lexem und gebe das Token zurück
 */
Token *Symtable::lookup(char* lexem){

	Token *token;

	//Hashe Lexem
	token = this->hashTable->lookup(lexem);

	//Falls gefunden gebe das Token zurück
	return token;
}

/*
 * Füge Token in die Symboltabelle ein
 */
char *Symtable::insertToken(Token* token) {
	char *key;

	//Übergebe Token an die Hash Map
	key = this->hashTable->addToken(token);

	return key;

}

/*
 * Gebe alle Einträge der Symboltabelle aus
 */
void Symtable::printHashMap(){
	this->hashTable->printHashMap();
}

