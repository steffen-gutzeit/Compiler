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

/*
 * Destruktor
 */
Symtable::~Symtable() {

	delete this->token1;
	delete this->token2;
	delete this->token3;
	delete this->token4;
	delete this->token5;
	delete this->token6;
	delete this->token7;
	delete this->token8;
	delete this->token9;
	delete this->token10;
	delete this->token11;
	delete this->token12;
	delete this->hashTable;
}

/*
 * Initialisiert die Symboltabelle und fügt die ersten Token hinzu
 */
void Symtable::initSymbols(){
	char textWhile1[]	= "while\0";
	char textIf1[] 		= "if\0";
	char textWrite1[]	= "write\0";
	char textRead1[]	= "read\0";
	char textInt1[]		= "int\0";
	char textElse1[]	= "else\0";

	char textWhile2[] 	= "WHILE\0";
	char textIf2[] 		= "IF\0";
	char textElse2[]	= "ELSE\0";

	char textWrite2[]	= "WRITE\0";
	char textRead2[]	= "READ\0";
	char textInt2[]		= "INT\0";


	//Estelle Token und füge diese in die Symboltabelle ein

	this->insertToken(token1 = new Token(0, 0, token->TT_WHILE, textWhile1));
	this->insertToken(token2 = new Token(0, 0, token->TT_WHILE, textWhile2));

	this->insertToken(token3 = new Token(0, 0, token->TT_IF, textIf1));
	this->insertToken(token4 = new Token(0, 0, token->TT_IF, textIf2));

	this->insertToken(token5 = new Token(0, 0, token->TT_ELSE, textElse1));
	this->insertToken(token6 = new Token(0, 0, token->TT_ELSE, textElse2));

	this->insertToken(token7 = new Token(0, 0, token->TT_INT, textInt1));
	this->insertToken(token8 = new Token(0, 0, token->TT_READ, textRead1));
	this->insertToken(token9 = new Token(0, 0, token->TT_WRITE, textWrite1));

	this->insertToken(token10 = new Token(0, 0, token->TT_INT, textInt2));
	this->insertToken(token11 = new Token(0, 0, token->TT_READ, textRead2));
	this->insertToken(token12 = new Token(0, 0, token->TT_WRITE, textWrite2));


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

