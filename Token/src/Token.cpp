/*
 * Token.cpp
 *
 *  Created on: 27.03.2016
 *      Author: Manuel
 */

#include "Token.h"
#include <stdint.h>

Token::Token(uint16_t row, uint32_t column, uint32_t tokenType, char *lexem) {
	this->tokenID = 0;
	this->row = row;
	this->column = column;
	this->tokenType = tokenType;
	this->lexem = lexem;

}

Token::~Token() {
	// TODO Auto-generated destructor stub
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

const char *Token::getTokenType(){
    switch (this->tokenType){

    case TT_DUMMY: return "Dummy\t"; break;
    case TT_SIGN: return "Sign\t\t"; break;
    case TT_INTEGER: return "Integer\t\t"; break;
    case TT_IDENTIFIER: return "Identifier\t"; break;
    case TT_IF: return "IF\t\t"; break;
    case TT_WHILE: return "WHILE\t\t"; break;
    case TT_PLUS: return "Plus\t"; break;
    case TT_MINUS: return "Minus\t"; break;
    case TT_COLON: return "Colon\t\t"; break;
    case TT_STAR: return "Star\t\t"; break;
    case TT_LESS: return "Less\t"; break;
    case TT_MORE: return "More\t"; break;
    case TT_EQUAL: return "Equal\t\t"; break;
    case TT_COLON_EQUAL: return "COLON_EQUAL\t"; break;
    case TT_MORE_COLON_MORE: return "Mo_Co_Mo\t\t"; break;
    case TT_EXCLAMATION_MARK: return "Excla_Mark"; break;
    //case 16: return "Quest_Mark"; break;
    case TT_AND: return "And\t\t"; break;
    case TT_SEMICOLON: return "Semicolon\t"; break;
    case TT_BRACKET_UPON: return "Brack_Open"; break;
    case TT_BRACKET_CLOSE: return "Brack_Close"; break;
    case TT_BRACE_UPON: return "Brace_Open"; break;
    case TT_BRACE_CLOSE: return "Brace_Close"; break;
    case TT_SQUARE_BRACKET_UPON: return "SqrBra_Open"; break;
    case TT_SQUARE_BRACKET_CLOSE: return "SqrBra_Close"; break;
    case TT_BLANK: return "Blank\t"; break;
    case TT_ERROR: return "Error\t"; break;

    }
    //Sollte nie erreicht werden :)
    //Default Rückgabewert
    return "Error";
}
