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

uint16_t Automat::getStateByChar(char currentChar) {
	return transitionTable[this->currentState][this->getCharacterType(currentChar)];
}

uint16_t Automat::testChar(char currentChar) {
	this->currentState = transitionTable[this->currentState][this->getCharacterType(currentChar)];

	return this->currentState;
}

uint16_t Automat::getCharacterType(char currentChar) {
	if (currentChar >= '0' && currentChar <= '9') {
		return CT_DIGIT;
	} else if ( ((currentChar >= 'A') && (currentChar <= 'D')) ||
				(currentChar == 'G') ||
				((currentChar >= 'J') && (currentChar <= 'K')) ||
				((currentChar >= 'M') && (currentChar <= 'V')) ||
				((currentChar >= 'X') && (currentChar <= 'Z')) ||

				((currentChar >= 'a') && (currentChar <= 'd')) ||
				(currentChar == 'g') ||
				((currentChar >= 'j') && (currentChar <= 'k')) ||
				((currentChar >= 'm') && (currentChar <= 'v')) ||
				((currentChar >= 'x') && (currentChar <= 'z'))) {
		return CT_LETTER;
	} else if ( currentChar == 'i') {
		return CT_SMALL_I;
	} else if ( currentChar == 'f') {
		return CT_SMALL_F;
	} else if ( currentChar == 'w') {
		return CT_SMALL_W;
	} else if ( currentChar == 'h') {
		return CT_SMALL_H;
	} else if ( currentChar == 'l') {
		return CT_SMALL_L;
	} else if ( currentChar == 'e') {
		return CT_SMALL_E;
	} else if ( currentChar == 'I') {
		return CT_CAPITAL_I;
	} else if ( currentChar == 'F') {
		return CT_CAPITAL_F;
	} else if ( currentChar == 'W') {
		return CT_CAPITAL_W;
	} else if ( currentChar == 'H') {
		return CT_CAPITAL_H;
	} else if ( currentChar == 'L') {
		return CT_CAPITAL_L;
	} else if ( currentChar == 'E') {
		return CT_CAPITAL_E;
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
	transitionTable[i][2]  = IF_SMALL_1;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = WHILE_SMALL_1;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = IF_CAPITAL_1;
	transitionTable[i][9]  = IDENTIFIER;
	transitionTable[i][10] = WHILE_CAPITAL_1;
	transitionTable[i][11] = IDENTIFIER;
	transitionTable[i][12] = IDENTIFIER;
	transitionTable[i][13] = IDENTIFIER;
	transitionTable[i][14] = SIGN;
	transitionTable[i][15] = COLON;
	transitionTable[i][16] = STAR;
	transitionTable[i][17] = EQUAL;
	transitionTable[i][18] = AND_1;
	transitionTable[i][19] = BLANK;
	transitionTable[i][20] = LINE_BREAK;
	transitionTable[i][21] = TAB;
	transitionTable[i][22] = ERROR;

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
	transitionTable[i][17] = INIT;
	transitionTable[i][18] = INIT;
	transitionTable[i][19] = INIT;
	transitionTable[i][20] = INIT;
	transitionTable[i][21] = INIT;
	transitionTable[i][22] = INIT;

	// ERROR
	i = 2;
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
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// BLANK
	i = 3;
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
	transitionTable[i][17] = INIT;
	transitionTable[i][18] = INIT;
	transitionTable[i][19] = INIT;
	transitionTable[i][20] = INIT;
	transitionTable[i][21] = INIT;
	transitionTable[i][22] = INIT;

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
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

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
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

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
	transitionTable[i][13] = TOKEN;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

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
	transitionTable[i][8]  = IDENTIFIER;
	transitionTable[i][9]  = IDENTIFIER;
	transitionTable[i][10] = IDENTIFIER;
	transitionTable[i][11] = IDENTIFIER;
	transitionTable[i][12] = IDENTIFIER;
	transitionTable[i][13] = IDENTIFIER;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// IF_SMALL_1
	i = 8;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IF;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = IDENTIFIER;
	transitionTable[i][9]  = IDENTIFIER;
	transitionTable[i][10] = IDENTIFIER;
	transitionTable[i][11] = IDENTIFIER;
	transitionTable[i][12] = IDENTIFIER;
	transitionTable[i][13] = IDENTIFIER;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;


	// IF_CAPITAL_1
	i = 9;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = IDENTIFIER;
	transitionTable[i][9]  = IF;
	transitionTable[i][10] = IDENTIFIER;
	transitionTable[i][11] = IDENTIFIER;
	transitionTable[i][12] = IDENTIFIER;
	transitionTable[i][13] = IDENTIFIER;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// IF
	i = 10;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = IDENTIFIER;
	transitionTable[i][9]  = IDENTIFIER;
	transitionTable[i][10] = IDENTIFIER;
	transitionTable[i][11] = IDENTIFIER;
	transitionTable[i][12] = IDENTIFIER;
	transitionTable[i][13] = IDENTIFIER;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// WHILE_SMALL_1
	i = 11;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = WHILE_SMALL_2;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = IDENTIFIER;
	transitionTable[i][9]  = IDENTIFIER;
	transitionTable[i][10] = IDENTIFIER;
	transitionTable[i][11] = IDENTIFIER;
	transitionTable[i][12] = IDENTIFIER;
	transitionTable[i][13] = IDENTIFIER;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// WHILE_SMALL_2
	i = 12;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = WHILE_SMALL_3;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = IDENTIFIER;
	transitionTable[i][9]  = IDENTIFIER;
	transitionTable[i][10] = IDENTIFIER;
	transitionTable[i][11] = IDENTIFIER;
	transitionTable[i][12] = IDENTIFIER;
	transitionTable[i][13] = IDENTIFIER;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// WHILE_SMALL_3
	i = 13;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = WHILE_SMALL_4;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = IDENTIFIER;
	transitionTable[i][9]  = IDENTIFIER;
	transitionTable[i][10] = IDENTIFIER;
	transitionTable[i][11] = IDENTIFIER;
	transitionTable[i][12] = IDENTIFIER;
	transitionTable[i][13] = IDENTIFIER;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// WHILE_SMALL_4
	i = 14;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = WHILE;
	transitionTable[i][8]  = IDENTIFIER;
	transitionTable[i][9]  = IDENTIFIER;
	transitionTable[i][10] = IDENTIFIER;
	transitionTable[i][11] = IDENTIFIER;
	transitionTable[i][12] = IDENTIFIER;
	transitionTable[i][13] = IDENTIFIER;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// WHILE_CAPITAL_1
	i = 15;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = IDENTIFIER;
	transitionTable[i][9]  = IDENTIFIER;
	transitionTable[i][10] = IDENTIFIER;
	transitionTable[i][11] = WHILE_CAPITAL_2;
	transitionTable[i][12] = IDENTIFIER;
	transitionTable[i][13] = IDENTIFIER;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// WHILE_CAPITAL_2
	i = 16;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = WHILE_CAPITAL_3;
	transitionTable[i][9]  = IDENTIFIER;
	transitionTable[i][10] = IDENTIFIER;
	transitionTable[i][11] = IDENTIFIER;
	transitionTable[i][12] = IDENTIFIER;
	transitionTable[i][13] = IDENTIFIER;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// WHILE_CAPITAL_3
	i = 17;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = IDENTIFIER;
	transitionTable[i][9]  = IDENTIFIER;
	transitionTable[i][10] = IDENTIFIER;
	transitionTable[i][11] = IDENTIFIER;
	transitionTable[i][12] = WHILE_CAPITAL_4;
	transitionTable[i][13] = IDENTIFIER;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// WHILE_CAPITAL_4
	i = 18;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = IDENTIFIER;
	transitionTable[i][9]  = IDENTIFIER;
	transitionTable[i][10] = IDENTIFIER;
	transitionTable[i][11] = IDENTIFIER;
	transitionTable[i][12] = IDENTIFIER;
	transitionTable[i][13] = WHILE;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// WHILE
	i = 19;
	transitionTable[i][0]  = IDENTIFIER;
	transitionTable[i][1]  = IDENTIFIER;
	transitionTable[i][2]  = IDENTIFIER;
	transitionTable[i][3]  = IDENTIFIER;
	transitionTable[i][4]  = IDENTIFIER;
	transitionTable[i][5]  = IDENTIFIER;
	transitionTable[i][6]  = IDENTIFIER;
	transitionTable[i][7]  = IDENTIFIER;
	transitionTable[i][8]  = IDENTIFIER;
	transitionTable[i][9]  = IDENTIFIER;
	transitionTable[i][10] = IDENTIFIER;
	transitionTable[i][11] = IDENTIFIER;
	transitionTable[i][12] = IDENTIFIER;
	transitionTable[i][13] = IDENTIFIER;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// SIGN
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
	transitionTable[i][13] = TOKEN;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = BLANK;
	transitionTable[i][20] = LINE_BREAK;
	transitionTable[i][21] = TAB;
	transitionTable[i][22] = ERROR;

	// COLON
	i = 21;
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
	transitionTable[i][16] = COMMENT_1;
	transitionTable[i][17] = COLON_EQUAL;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// STAR
	i = 22;
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
	transitionTable[i][15] = COMMENT_1;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = BLANK;
	transitionTable[i][20] = LINE_BREAK;
	transitionTable[i][21] = TAB;
	transitionTable[i][22] = ERROR;

	// EQUAL
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
	transitionTable[i][12] = TOKEN;
	transitionTable[i][13] = TOKEN;
	transitionTable[i][14] = TOKEN;
	transitionTable[i][15] = COMPLEX_1;
	transitionTable[i][16] = TOKEN;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// AND_1
	i = 24;
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
	transitionTable[i][12] = ERROR;
	transitionTable[i][13] = ERROR;
	transitionTable[i][14] = ERROR;
	transitionTable[i][15] = ERROR;
	transitionTable[i][16] = ERROR;
	transitionTable[i][17] = ERROR;
	transitionTable[i][18] = AND;
	transitionTable[i][19] = ERROR;
	transitionTable[i][20] = ERROR;
	transitionTable[i][21] = ERROR;
	transitionTable[i][22] = ERROR;

	// AND
	i = 25;
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
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = BLANK;
	transitionTable[i][20] = LINE_BREAK;
	transitionTable[i][21] = TAB;
	transitionTable[i][22] = ERROR;

	// COMMENT_1
	i = 26;
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
	transitionTable[i][10] = COMMENT_1;
	transitionTable[i][11] = COMMENT_1;
	transitionTable[i][12] = COMMENT_1;
	transitionTable[i][13] = COMMENT_1;
	transitionTable[i][14] = COMMENT_1;
	transitionTable[i][15] = COMMENT_1;
	transitionTable[i][16] = COMMENT_2;
	transitionTable[i][17] = COMMENT_1;
	transitionTable[i][18] = COMMENT_1;
	transitionTable[i][19] = COMMENT_1;
	transitionTable[i][20] = COMMENT_1;
	transitionTable[i][21] = COMMENT_1;
	transitionTable[i][22] = COMMENT_1;

	// COMMENT_2
	i = 27;
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
	transitionTable[i][10] = COMMENT_1;
	transitionTable[i][11] = COMMENT_1;
	transitionTable[i][12] = COMMENT_1;
	transitionTable[i][13] = COMMENT_1;
	transitionTable[i][14] = COMMENT_1;
	transitionTable[i][15] = TOKEN;
	transitionTable[i][16] = COMMENT_1;
	transitionTable[i][17] = COMMENT_1;
	transitionTable[i][18] = COMMENT_1;
	transitionTable[i][19] = COMMENT_1;
	transitionTable[i][20] = COMMENT_1;
	transitionTable[i][21] = COMMENT_1;
	transitionTable[i][22] = COMMENT_1;

	// COLON_EQUAL
	i = 28;
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
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;

	// COMPLEX_1
	i = 29;
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
	transitionTable[i][11] = CHECK;
	transitionTable[i][12] = CHECK;
	transitionTable[i][13] = CHECK;
	transitionTable[i][14] = CHECK;
	transitionTable[i][15] = CHECK;
	transitionTable[i][16] = CHECK;
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = CHECK;
	transitionTable[i][19] = CHECK;
	transitionTable[i][20] = CHECK;
	transitionTable[i][21] = CHECK;
	transitionTable[i][22] = CHECK;


	// CHECK
	i = 30;
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
	transitionTable[i][17] = TOKEN;
	transitionTable[i][18] = TOKEN;
	transitionTable[i][19] = TOKEN;
	transitionTable[i][20] = TOKEN;
	transitionTable[i][21] = TOKEN;
	transitionTable[i][22] = TOKEN;
}
