/*
 * Automat.cpp
 * Stand: 5.11.2014
 */

#include "Automat.h"

using namespace std;


//Da statisches Feld au�erhalb des Konstruktors initialisiert
uint16_t Automat::transitionTable[12][21] = {
//			 0		1		2	  3		 4		5      6      7      8      9      10     11     12     13     14     15     16     17     18      19	  20
//			 S_000, DI_01, CH_01, SS_01, SS_02, SS_03, CS_01, SS_04, CS_02, KO_01, KO_02, KO_03, KO_04,	KO_05  WS_01, LNBRK, TOKEN, ERROR,	TOKE2, ERRO2  NAERA
/* a-z */	{CH_01, TOKEN, CH_01, TOKEN, TOKEN, ERRO2, TOKEN, ERROR, TOKEN, TOKEN, KO_02, KO_03, TOKEN,	TOKEN, DELWS, S_000, S_000, 0,		S_000, TOKE2, 0},
/* 0-9 */	{DI_01, DI_01, CH_01, TOKEN, TOKEN, ERRO2, TOKEN, ERROR, TOKEN, TOKEN, KO_02, KO_03, TOKEN,	TOKEN, DELWS, S_000, S_000, 0,		S_000, TOKE2, 0},
/* +, -*/	{TOKEN, TOKEN, TOKEN, TOKEN, TOKEN, ERRO2, TOKEN, ERROR, TOKEN, TOKEN, KO_02, KO_03, TOKEN,	TOKEN, DELWS, S_000, S_000, 0,		S_000, TOKE2, 0},
/* < */		{SS_02, TOKEN, TOKEN, TOKEN, TOKEN, ERRO2, TOKEN, ERROR, TOKEN, TOKEN, KO_02, KO_03, TOKEN,	TOKEN, DELWS, S_000, S_000, 0,		S_000, TOKE2, 0},
/* : */		{SS_04, TOKEN, TOKEN, TOKEN, SS_03, ERRO2, TOKEN, ERROR, TOKEN,	TOKEN, KO_02, KO_03, TOKEN,	TOKEN, DELWS, S_000, S_000, 0,		S_000, TOKE2, 0},
/* > */		{TOKEN, TOKEN, TOKEN, TOKEN, TOKEN, CS_01, TOKEN, ERROR, TOKEN, TOKEN, KO_02, KO_03, TOKEN,	TOKEN, DELWS, S_000, S_000, 0,		S_000, TOKE2, 0},
/* = */		{TOKEN, TOKEN, TOKEN, TOKEN, TOKEN, ERRO2, TOKEN, CS_02, TOKEN, TOKEN, KO_02, KO_03, TOKEN,	TOKEN, DELWS, S_000, S_000, 0,		S_000, TOKE2, 0},
/*/  */	    {KO_01,	TOKEN, TOKEN, TOKEN, TOKEN, ERRO2, TOKEN, ERROR, TOKEN, TOKEN, KO_02, KO_04, KO_05,	TOKEN, DELWS, S_000, S_000, 0,		S_000, TOKE2, 0},
/* * */		{SS_01, TOKEN, TOKEN, TOKEN, TOKEN, ERRO2, TOKEN, ERROR, TOKEN, KO_02, KO_03, KO_03, TOKEN,	TOKEN, DELWS, S_000, S_000, 0,		S_000, TOKE2, 0},
/* blank */	{WS_01,	TOKEN, TOKEN, TOKEN, TOKEN, ERRO2, TOKEN, ERROR, TOKEN, TOKEN, KO_02, KO_03, TOKEN,	TOKEN, WS_01, S_000, S_000, 0,		S_000, TOKE2, 0},
/* \n */	{LNBRK,	TOKEN, TOKEN, TOKEN, TOKEN, ERRO2, TOKEN, ERROR, TOKEN, TOKEN, KO_02, KO_03, TOKEN, TOKEN, DELWS, LNBRK, S_000, 0,		S_000, TOKE2, 0},
/*Error*/	{NAERA,	NAERA, NAERA, TOKEN, NAERA, NAERA, TOKEN, ERROR, NAERA, NAERA, KO_02, KO_03, TOKEN, TOKEN, DELWS, LNBRK, S_000, 0,		S_000, TOKE2, 0}
};



Automat::Automat() {
    init();
    this->cols = 0;
    this->rows = 1;
}

Automat::~Automat() {

}

uint16_t Automat::testChar(char currentChar){
    //Ermittle anhand der Transitionstabelle den nächsten Zustand
    //Übergangsfunktion

    this->currentState = this->transitionTable[this->characterType(currentChar)]
											   [(this->currentState & 0x000F)];
    return this->currentState;
}

void Automat::printBinaries(uint16_t digit) {
	cout << digit << "\t-\t";

	for(int i = 15; i >= 0; i--) {
		if (((i + 1) % 4) == 0 && (i != 15)) {
			cout << " ";
		}

		if ((digit & (1 << i))) {
			cout << 1;
		} else {
			cout << 0;
		}
	}
	cout << "\t" << (digit & 0x000F) << endl;
}

void Automat::init(){
    this->currentState = 0;
}

uint16_t Automat::getCols() {
	return this->cols;
}

uint16_t Automat::getRows() {
	return this->rows;
}

void Automat::incrementRowCount() {
	this->rows++;
}

void Automat::incrementColCount() {
	this->cols++;
}

void Automat::initColCount() {
	this->cols = 0;
}

void Automat::decrementColCount() {
	this->cols--;
}

void Automat::decrementColCount(int i) {
	this->cols -= i;
}

uint16_t Automat::characterType(char testChar) {
	//cout << "        " << testChar << endl;
	//cout << testChar << endl;

	if (testChar >= '0' && testChar <= '9') {
        return CT_NUMERIC;
    } else if ( ((testChar >= 'A') && (testChar <= 'Z')) || ((testChar >= 'a') && (testChar <= 'z'))){
    	return CT_LETTER;
    } else if (testChar == ' ') {
    	return CT_WHITE_SPACE;
    } else if (testChar == '\n'){
    	return CT_LINE_BREAK;
    } else if (testChar == '/'){
    	return CT_SLASH;
    } else if (testChar == '*'){
    	return CT_STAR;
    } else if ((testChar == '<') | (testChar == ':') | (testChar == '>') | (testChar == '!') | (testChar == '&') | (testChar == ';') | (testChar == '(') | (testChar == ')') | (testChar == '{') | (testChar == '}') | (testChar == '[') | (testChar == ']') | (testChar == '+') | (testChar == '-') | (testChar == '=')) {
        switch(testChar){
            case '<': return CT_SIGN_LESS;
            case ':': return CT_SIGN_DOUBLE;
            case '>': return CT_SIGN_MORE;
            case '=': return CT_SIGN_EQUAL;
            default : return CT_SIGN;
        }
    }else{
    	return CT_ERROR;
    }
}

