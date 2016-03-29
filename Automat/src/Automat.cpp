/*
 * Automat.cpp
 *
 *  Created on: 27.03.2016
 *      Author: Manuel
 */

#include "Automat.h"
#include <iostream>

Automat::Automat() {
	// TODO Auto-generated constructor stub
	this->initTransitionTable();
	this->currentState = INIT;
}

Automat::~Automat() {
	// TODO Auto-generated destructor stub
}

uint16_t Automat::testChar(char currentChar) {

	this->currentState = transitionTable[(this->currentState)][this->getCharacterType(currentChar)];
/*
	cout
		<< " Matrix-Col:" << this->currentState << endl
		<< " Matrix-Row:" << this->getCharacterType(currentChar) << endl
		<< " State: " << currentState << endl
		<< " Char: " << currentChar << endl
		<< endl;
*/
	return this->currentState;
}

uint16_t Automat::getCharacterType(char currentChar) {
	if (currentChar >= '0' && currentChar <= '9') {
		return CT_DIGIT;
	} else if ( ((currentChar >= 'A') && (currentChar <= 'D') &&
				(currentChar >= 'G') && (currentChar <= 'H') &&
				(currentChar >= 'J') && (currentChar <= 'K') &&
				(currentChar >= 'M') && (currentChar <= 'V') &&
				(currentChar >= 'X') && (currentChar <= 'Z')) ||

				((currentChar >= 'a') && (currentChar <= 'd') &&
				(currentChar >= 'g') && (currentChar <= 'h') &&
				(currentChar >= 'j') && (currentChar <= 'k') &&
				(currentChar >= 'm') && (currentChar <= 'v') &&
				(currentChar >= 'x') && (currentChar <= 'z'))) {
		return CT_LETTER;
	} else if ( currentChar == 'i' || currentChar == 'I') {
		return CT_I;
	} else if ( currentChar == 'f' || currentChar == 'F') {
		return CT_F;
	} else if ( currentChar == 'w' || currentChar == 'W') {
		return CT_W;
	} else if ( currentChar == 'h' || currentChar == 'H') {
		return CT_H;
	} else if ( currentChar == 'l' || currentChar == 'L') {
		return CT_L;
	} else if ( currentChar == 'e' || currentChar == 'E') {
		return CT_E;
	} else if ( currentChar == ':') {
		return CT_SIGN_COLON;
	} else if ( currentChar == '*') {
		return CT_SIGN_STAR;
	} else if ( currentChar == '=') {
		return CT_SIGN_EQUAL;
	} else if ( currentChar == '&') {
		return CT_SIGN_AND;
	} else if ( currentChar == ' ') {
		return CT_BLANK;
	} else if ( currentChar == '\n' || currentChar == '\0') {
		return CT_LINE_BREAK;
	} else if ( currentChar == '\t') {
		return CT_TAB;
	} else if ( currentChar == '+' || currentChar == '-' ||
			currentChar == '<' || currentChar == '>' ||
			currentChar == '!' || currentChar == ';' ||
			currentChar == '(' || currentChar == ')' ||
			currentChar == '{' || currentChar == '}' ||
			currentChar == '[' || currentChar == ']') {
		return CT_SIGN;
	} else {
		return CT_NOT_ALLOWED;
	}
}

void Automat::initTransitionTable() {
	int i = 0;
	// INIT
	transitionTable[i][0]  = INTEGER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IF_1;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = WHILE_1;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = SIGN;
	transitionTable[i][9]  = COLON;
	transitionTable[i][10] = STAR;
	transitionTable[i][11] = EQUAL;
	transitionTable[i][12] = AND_1;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// TOKEN
	i = 1;
	transitionTable[i][0]  = INIT;
	transitionTable[i][1]  = INIT;
	transitionTable[i][2]  = INIT;
	transitionTable[i][3]  = INIT;
	transitionTable[i][4]  = INIT;
	transitionTable[i][5]  = INIT;
	transitionTable[i][6]  = INIT;
	transitionTable[i][7]  = INIT;
	transitionTable[i][8]  = INIT;
	transitionTable[i][9]  = INIT;
	transitionTable[i][10] = INIT;
	transitionTable[i][11] = INIT;
	transitionTable[i][12] = INIT;
	transitionTable[i][13] = INIT;
	transitionTable[i][14] = INIT;
	transitionTable[i][15] = INIT;
	transitionTable[i][16] = INIT;

	// ERROR
	i = 2;
	transitionTable[i][0]  = INIT;
	transitionTable[i][1]  = INIT;
	transitionTable[i][2]  = INIT;
	transitionTable[i][3]  = INIT;
	transitionTable[i][4]  = INIT;
	transitionTable[i][5]  = INIT;
	transitionTable[i][6]  = INIT;
	transitionTable[i][7]  = INIT;
	transitionTable[i][8]  = INIT;
	transitionTable[i][9]  = INIT;
	transitionTable[i][10] = INIT;
	transitionTable[i][11] = INIT;
	transitionTable[i][12] = INIT;
	transitionTable[i][13] = INIT;
	transitionTable[i][14] = INIT;
	transitionTable[i][15] = INIT;
	transitionTable[i][16] = INIT;

	// BLANK
	i = 3;
	transitionTable[i][0]  = TOKEN;
	transitionTable[i][1]  = TOKEN;
	transitionTable[i][2]  = TOKEN;
	transitionTable[i][3]  = TOKEN;
	transitionTable[i][4]  = TOKEN;
	transitionTable[i][5]  = TOKEN;
	transitionTable[i][6]  = TOKEN;
	transitionTable[i][7]  = TOKEN;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = TOKEN;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;

	// LINE_BREAK
	i = 4;
	transitionTable[i][0]  = TOKEN;
	transitionTable[i][1]  = TOKEN;
	transitionTable[i][2]  = TOKEN;
	transitionTable[i][3]  = TOKEN;
	transitionTable[i][4]  = TOKEN;
	transitionTable[i][5]  = TOKEN;
	transitionTable[i][6]  = TOKEN;
	transitionTable[i][7]  = TOKEN;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = TOKEN;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;

	// TAB
	i = 5;
	transitionTable[i][0]  = TOKEN;
	transitionTable[i][1]  = TOKEN;
	transitionTable[i][2]  = TOKEN;
	transitionTable[i][3]  = TOKEN;
	transitionTable[i][4]  = TOKEN;
	transitionTable[i][5]  = TOKEN;
	transitionTable[i][6]  = TOKEN;
	transitionTable[i][7]  = TOKEN;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = TOKEN;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;

	// INTEGER
	i = 6;
	transitionTable[i][0]  = INTEGER;
	transitionTable[i][1]  = TOKEN;
	transitionTable[i][2]  = TOKEN;
	transitionTable[i][3]  = TOKEN;
	transitionTable[i][4]  = TOKEN;
	transitionTable[i][5]  = TOKEN;
	transitionTable[i][6]  = TOKEN;
	transitionTable[i][7]  = TOKEN;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// IDENTIFIER
	i = 7;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// IF_1
	i = 8;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IF;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// IF
	i = 9;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// WHILE_1
	i = 10;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = WHILE_2;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// WHILE_2
	i = 11;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = WHILE_3;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// WHILE_3
	i = 12;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = WHILE_4;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// WHILE_4
	i = 13;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = WHILE;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// WHILE
	i = 14;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// SIGN
	i = 15;
	transitionTable[i][0]  = TOKEN;
	transitionTable[i][1]  = TOKEN;
	transitionTable[i][2]  = TOKEN;
	transitionTable[i][3]  = TOKEN;
	transitionTable[i][4]  = TOKEN;
	transitionTable[i][5]  = TOKEN;
	transitionTable[i][6]  = TOKEN;
	transitionTable[i][7]  = TOKEN;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// COLON
	i = 16;
	transitionTable[i][0]  = TOKEN;
	transitionTable[i][1]  = TOKEN;
	transitionTable[i][2]  = TOKEN;
	transitionTable[i][3]  = TOKEN;
	transitionTable[i][4]  = TOKEN;
	transitionTable[i][5]  = TOKEN;
	transitionTable[i][6]  = TOKEN;
	transitionTable[i][7]  = TOKEN;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = COMMENT_1;
	transitionTable[i][11] = COLON_EQUAL;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// STAR
	i = 17;
	transitionTable[i][0]  = TOKEN;
	transitionTable[i][1]  = TOKEN;
	transitionTable[i][2]  = TOKEN;
	transitionTable[i][3]  = TOKEN;
	transitionTable[i][4]  = TOKEN;
	transitionTable[i][5]  = TOKEN;
	transitionTable[i][6]  = TOKEN;
	transitionTable[i][7]  = TOKEN;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = COMMENT_1;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// EQUAL
	i = 18;
	transitionTable[i][0]  = TOKEN;
	transitionTable[i][1]  = TOKEN;
	transitionTable[i][2]  = TOKEN;
	transitionTable[i][3]  = TOKEN;
	transitionTable[i][4]  = TOKEN;
	transitionTable[i][5]  = TOKEN;
	transitionTable[i][6]  = TOKEN;
	transitionTable[i][7]  = TOKEN;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = COMPLEX_1;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// AND_1
	i = 19;
	transitionTable[i][0]  = ERROR;
	transitionTable[i][1]  = ERROR;
	transitionTable[i][2]  = ERROR;
	transitionTable[i][3]  = ERROR;
	transitionTable[i][4]  = ERROR;
	transitionTable[i][5]  = ERROR;
	transitionTable[i][6]  = ERROR;
	transitionTable[i][7]  = ERROR;
	transitionTable[i][8]  = ERROR;
	transitionTable[i][9]  = ERROR;
	transitionTable[i][10] = ERROR;
	transitionTable[i][11] = ERROR;
	transitionTable[i][12] = AND;
	transitionTable[i][13] = ERROR;
	transitionTable[i][14] = ERROR;
	transitionTable[i][15] = ERROR;
	transitionTable[i][16] = ERROR;

	// AND
	i = 20;
	transitionTable[i][0]  = TOKEN;
	transitionTable[i][1]  = TOKEN;
	transitionTable[i][2]  = TOKEN;
	transitionTable[i][3]  = TOKEN;
	transitionTable[i][4]  = TOKEN;
	transitionTable[i][5]  = TOKEN;
	transitionTable[i][6]  = TOKEN;
	transitionTable[i][7]  = TOKEN;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// COMMENT_1
	i = 21;
	transitionTable[i][0]  = COMMENT_1;
	transitionTable[i][1]  = COMMENT_1;
	transitionTable[i][2]  = COMMENT_1;
	transitionTable[i][3]  = COMMENT_1;
	transitionTable[i][4]  = COMMENT_1;
	transitionTable[i][5]  = COMMENT_1;
	transitionTable[i][6]  = COMMENT_1;
	transitionTable[i][7]  = COMMENT_1;
	transitionTable[i][8]  = COMMENT_1;
	transitionTable[i][9]  = COMMENT_1;
	transitionTable[i][10] = COMMENT_2;
	transitionTable[i][11] = COMMENT_1;
	transitionTable[i][12] = COMMENT_1;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// COMMENT_2
	i = 22;
	transitionTable[i][0]  = COMMENT_1;
	transitionTable[i][1]  = COMMENT_1;
	transitionTable[i][2]  = COMMENT_1;
	transitionTable[i][3]  = COMMENT_1;
	transitionTable[i][4]  = COMMENT_1;
	transitionTable[i][5]  = COMMENT_1;
	transitionTable[i][6]  = COMMENT_1;
	transitionTable[i][7]  = COMMENT_1;
	transitionTable[i][8]  = COMMENT_1;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = COMMENT_1;
	transitionTable[i][11] = COMMENT_1;
	transitionTable[i][12] = COMMENT_1;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// COLON_EQUAL
	i = 23;
	transitionTable[i][0]  = TOKEN;
	transitionTable[i][1]  = TOKEN;
	transitionTable[i][2]  = TOKEN;
	transitionTable[i][3]  = TOKEN;
	transitionTable[i][4]  = TOKEN;
	transitionTable[i][5]  = TOKEN;
	transitionTable[i][6]  = TOKEN;
	transitionTable[i][7]  = TOKEN;
	transitionTable[i][8]  = TOKEN;
	transitionTable[i][9]  = TOKEN;
	transitionTable[i][10] = TOKEN;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = AND;
	transitionTable[i][13] = BLANK;
	transitionTable[i][14] = LINE_BREAK;
	transitionTable[i][15] = TAB;
	transitionTable[i][16] = ERROR;

	// COMPLEX_1
	i = 24;
	transitionTable[i][0]  = CHECK;
	transitionTable[i][1]  = CHECK;
	transitionTable[i][2]  = CHECK;
	transitionTable[i][3]  = CHECK;
	transitionTable[i][4]  = CHECK;
	transitionTable[i][5]  = CHECK;
	transitionTable[i][6]  = CHECK;
	transitionTable[i][7]  = CHECK;
	transitionTable[i][8]  = CHECK;
	transitionTable[i][9]  = CHECK;
	transitionTable[i][10] = CHECK;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = CHECK;
	transitionTable[i][13] = CHECK;
	transitionTable[i][14] = CHECK;
	transitionTable[i][15] = CHECK;
	transitionTable[i][16] = ERROR;


	// COMPLEX_1
	i = 25;
	transitionTable[i][0]  = INIT;
	transitionTable[i][1]  = INIT;
	transitionTable[i][2]  = INIT;
	transitionTable[i][3]  = INIT;
	transitionTable[i][4]  = INIT;
	transitionTable[i][5]  = INIT;
	transitionTable[i][6]  = INIT;
	transitionTable[i][7]  = INIT;
	transitionTable[i][8]  = INIT;
	transitionTable[i][9]  = INIT;
	transitionTable[i][10] = INIT;
	transitionTable[i][11] = TOKEN;
	transitionTable[i][12] = INIT;
	transitionTable[i][13] = INIT;
	transitionTable[i][14] = INIT;
	transitionTable[i][15] = INIT;
	transitionTable[i][16] = ERROR;
}
