/*
 * Token.cpp
 *
 *  Created on: 29.10.2014
 *      Author: root0r
 */

#include "Token.h"
#include "../../Automat/src/Automat.h"

Token::Token(uint16_t row, uint16_t column, int tokenType, char * lexem) {
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

int Token::matchStateToType(uint16_t stateType) {
	switch (stateType) {
	case Automat::DI_01:
		return TT_INTEGER;

	case Automat::CH_01:
		return TT_IDENTIFIER;

	case Automat::SS_01:
	case Automat::SS_02:
	case Automat::SS_03:
	case Automat::SS_04:
	case Automat::CS_01:
	case Automat::CS_02:
		return TT_SIGN;
	// @todo EVTL IF-Typ und WHILE-Typ

	}
	return TT_DUMMY;


}


uint16_t Token::getRow(){
	return this->row;
}


uint16_t Token::getColumn(){
	return this->column;
}


const char *Token::getTokenType(){
    switch (this->tokenType){

    case 0: return "Dummy\t"; break;
    case 1: return "Sign\t"; break;
    case 2: return "Integer\t"; break;
    case 3: return "Identifier"; break;
    case 4: return "IF\t\t"; break;
    case 5: return "WHILE\t"; break;
    case 6: return "Plus\t"; break;
    case 7: return "Minus\t"; break;
    case 8: return "Slash\t"; break;
    case 9: return "Star\t"; break;
    case 10: return "Less\t"; break;
    case 11: return "More\t"; break;
    case 12: return "Equal\t"; break;
    case 13: return "Double_Equal"; break;
    case 14: return "Mo_Do_Le"; break;
    case 15: return "Excla_Mark"; break;
    case 16: return "Quest_Mark"; break;
    case 17: return "And\t\t"; break;
    case 18: return "Semicolon"; break;
    case 19: return "Brack_Open"; break;
    case 20: return "Brack_Close"; break;
    case 21: return "Brace_Open"; break;
    case 22: return "Brace_Close"; break;
    case 23: return "SqrBra_Open"; break;
    case 24: return "SqrBra_Close"; break;

    }
    //Sollte nie erreicht werden :)
    //Default Rückgabewert
    return "Error";
}

int Token::getTokenTypeInt(){
	return this->tokenType;
}

char *Token::getLexem(){
    return this->lexem;
}
