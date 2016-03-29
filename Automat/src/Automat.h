/*
 * Automat.h
 *
 *  Created on: 27.03.2016
 *      Author: Manuel
 */

#ifndef AUTOMAT_SRC_AUTOMAT_H_
#define AUTOMAT_SRC_AUTOMAT_H_

#include <stdint.h>

using namespace std;

class Automat {
public:
	Automat();
	virtual ~Automat();

	void initTransitionTable();
	uint16_t getCharacterType(char currentChar);
	uint16_t testChar(char currentChar);

	uint16_t transitionTable[26][17];
	uint16_t currentState;

	enum StateName {
		// BIT  0 - 5: Spalte der transitionTable
		INIT 		=  0, // 0000 0000 0000 0000
		TOKEN 		=  1, // 0000 0000 0000 0001
		ERROR 		=  2, // 0000 0000 0000 0010
		BLANK 		=  3, // 0000 0000 0000 0011
		LINE_BREAK 	=  4, // 0000 0000 0000 0100
		TAB 		=  5, // 0000 0000 0000 0101
		INTEGER 	=  6, // 0000 0000 0000 0110
		IDENTIFIER 	=  7, // 0000 0000 0000 0111
		IF_1 		=  8, // 0000 0000 0000 1000
		IF 			=  9, // 0000 0000 0000 1001
		WHILE_1 	= 10, // 0000 0000 0000 1010
		WHILE_2 	= 11, // 0000 0000 0000 1011
		WHILE_3 	= 12, // 0000 0000 0000 1100
		WHILE_4 	= 13, // 0000 0000 0000 1101
		WHILE		= 14, // 0000 0000 0000 1110
		SIGN 		= 15, // 0000 0000 0000 1111
		COLON 		= 16, // 0000 0000 0001 0000
		STAR 		= 17, // 0000 0000 0001 0001
		EQUAL 		= 18, // 0000 0000 0001 0010
		AND_1 		= 19, // 0000 0000 0001 0011
		AND 		= 20, // 0000 0000 0001 0100
		COMMENT_1 	= 21, // 0000 0000 0001 0101
		COMMENT_2 	= 22, // 0000 0000 0001 0110
		COLON_EQUAL = 23, // 0000 0000 0001 0111
		COMPLEX_1 	= 24, // 0000 0000 0001 1000
		CHECK		= 25
	};


	enum CaracterType {
		CT_DIGIT		=  0,
		CT_LETTER		=  1,
		CT_I			=  2,
		CT_F			=  3,
		CT_W			=  4,
		CT_H			=  5,
		CT_L			=  6,
		CT_E			=  7,
		CT_SIGN			=  8,
		CT_SIGN_COLON	=  9,
		CT_SIGN_STAR	= 10,
		CT_SIGN_EQUAL	= 11,
		CT_SIGN_AND		= 12,
		CT_BLANK		= 13,
		CT_LINE_BREAK	= 14,
		CT_TAB			= 15,
		CT_NOT_ALLOWED	= 16
	};
};
#endif /* AUTOMAT_SRC_AUTOMAT_H_ */

