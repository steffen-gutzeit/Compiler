/*
 * Token.cpp
 *
 *  Created on: 27.03.2016
 *      Author: Manuel
 */

#include "Token.h"
#include <stdint.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>

Token::Token(uint16_t row, uint32_t column, uint32_t tokenType, char *lexem) {
	this->tokenID = 0;
	this->row = row;
	this->column = column;

	//Lexem kopieren!
	//Lexem Länge bestimmen
	int length = 0;
	while(lexem[length] != '\0'){
		length++;
	}

	//Speicher für die Kopie allokieren
	this->lexem = (char *) malloc(length * sizeof(char));

	//cout << "Versuche Kopieren der Länge: " << length << "und Lexem: " << lexem << endl;

	//Lexem kopieren
	strncpy(this->lexem, lexem, length);
	//Endterminal setzen
	this->lexem[length] = '\0';

	//cout << "Kopiert: " << this->lexem << endl;

	this->integerValue = 0;
	this->typification = ParserConstant::noType;

	if(tokenType == TT_SIGN) {
		setTokenTypeSign(lexem[0]);
	} else {
		this->tokenType = tokenType;
	}
}

Token::Token(uint16_t row, uint32_t column, uint32_t tokenType, long integerValue) {
	this->tokenID = 0;
	this->row = row;
	this->column = column;
	//this->lexem = {"NotRelevant"};
	char textLexem[] = "NotRelevant";
	this->lexem = textLexem;
	this->integerValue = integerValue;
	this->typification = ParserConstant::noType;

	this->tokenType = tokenType;
}


Token::~Token() {
	// TODO Auto-generated destructor stub
}

long Token::getIntegerValue() {
	return this->integerValue;
}

Token Token::getToken() {
	return *this;
}

uint32_t Token::getCol() {
	return this->column;
}

uint32_t Token::getRow() {
	return this->row;
}

char *Token::getLexem(){
	return this->lexem;
}

uint16_t getLexemAsInteger(char *lexem) {
	//TODO Ausprogrammieren
	return 4711;
}

uint16_t Token::getIntValue() {
//	std::istringstream i(Token::myTokenValue);
//	int myResult;
//	i >> myResult;
//	return myResult;
//	cout << this->lexem << endl;
	return 0;
}

void Token::setTypification(ParserConstant::Typification typification) {
	this->typification = typification;
}

ParserConstant::Typification Token::getTypification()  {
	return this->typification;
}

void Token::setTokenTypeSign(char lexem) {
	switch(lexem){

		case '+': this->tokenType = TT_PLUS; break;
		case '-': this->tokenType = TT_MINUS; break;
		case '<': this->tokenType = TT_LESS; break;
		case '>': this->tokenType = TT_MORE; break;
		case '!': this->tokenType = TT_EXCLAMATION_MARK; break;
		case ';': this->tokenType = TT_SEMICOLON; break;
		case '(': this->tokenType = TT_BRACKET_UPON; break;
		case ')': this->tokenType = TT_BRACKET_CLOSE; break;
		case '{': this->tokenType = TT_BRACE_UPON; break;
		case '}': this->tokenType = TT_BRACE_CLOSE; break;
		case '[': this->tokenType = TT_SQUARE_BRACKET_UPON; break;
		case ']': this->tokenType = TT_SQUARE_BRACKET_CLOSE; break;

	}
}

uint16_t Token::matchStateToType(uint16_t stateType) {
	switch (stateType) {
	case Automat::INTEGER:
		return TT_INTEGER;
		break;

	case Automat::IDENTIFIER:
		return TT_INTEGER;
		break;

	case Automat::IF:
		return TT_IF;
		break;

	case Automat::WHILE:
		return TT_WHILE;
		break;

	case Automat::READ:
		return TT_READ;
		break;

	case Automat::WRITE:
		return TT_WRITE;
		break;

	case Automat::INT:
		return TT_INT;
		break;

	case Automat::ELSE:
		return TT_ELSE;
		break;

	case Automat::AND:
	case Automat::SIGN:
	case Automat::COLON:
	case Automat::EQUAL:
	case Automat::COLON_EQUAL:
	case Automat::COMPLEX_1:
			return TT_SIGN;
			break;
	}

	return TT_DUMMY;
}

uint16_t Token::getTokenTypeInt(){
	return tokenType;
}

const char *Token::getTokenType(){
	return getTokenTypeIntern(this->tokenType);
}


const char *Token::getTokenType(uint16_t &tokenType){
	return getTokenTypeIntern(tokenType);
}

const char *Token::getTokenTypeIntern(uint16_t &tokenType) {
    switch (this->tokenType){

    case TT_DUMMY: return "Dummy\t"; break;
    case TT_SIGN: return "Sign\t\t"; break;
    case TT_INTEGER: return "Integer\t\t"; break;
    case TT_IDENTIFIER: return "Identifier\t"; break;
    case TT_IF: return "IF\t\t"; break;
    case TT_WHILE: return "WHILE\t\t"; break;
    case TT_PLUS: return "Plus\t\t"; break;
    case TT_MINUS: return "Minus\t\t"; break;
    case TT_COLON: return "Colon\t\t"; break;
    case TT_STAR: return "Star\t\t"; break;
    case TT_LESS: return "Less\t\t"; break;
    case TT_MORE: return "More\t\t"; break;
    case TT_EQUAL: return "Equal\t\t"; break;
    case TT_COLON_EQUAL: return "COLON_EQUAL\t"; break;
    case TT_MORE_COLON_MORE: return "Mo_Co_Mo\t\t"; break;
    case TT_EXCLAMATION_MARK: return "Excla_Mark\t"; break;
    //case 16: return "Quest_Mark"; break;
    case TT_AND: return "And\t\t"; break;
    case TT_SEMICOLON: return "Semicolon\t"; break;
    case TT_BRACKET_UPON: return "Brack_Open\t"; break;
    case TT_BRACKET_CLOSE: return "Brack_Close\t"; break;
    case TT_BRACE_UPON: return "Brace_Open\t"; break;
    case TT_BRACE_CLOSE: return "Brace_Close\t"; break;
    case TT_SQUARE_BRACKET_UPON: return "SqrBra_Open\t"; break;
    case TT_SQUARE_BRACKET_CLOSE: return "SqrBra_Close\t"; break;
    case TT_BLANK: return "Blank\t"; break;
    case TT_ERROR: return "Error\t\t"; break;
    case TT_READ: return "Read\t\t"; break;
    case TT_WRITE: return "Write\t\t"; break;
    case TT_INT: return "int\t\t"; break;
    case TT_ELSE: return "Else\t\t"; break;

    }
    //Sollte nie erreicht werden :)
    //Default Rückgabewert
    return "Error";
}
