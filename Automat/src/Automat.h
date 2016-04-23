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
	uint16_t getStateByChar(char currentChar);
	uint16_t getCharacterType(char currentChar);
	uint16_t testChar(char currentChar);

	uint16_t transitionTable[31][23];
	uint16_t currentState;

	enum StateName {
		// BIT  0 - 5: Spalte der transitionTable
		INIT 			=  0,
		TOKEN 			=  1,
		ERROR 			=  2,
		BLANK 			=  3,
		LINE_BREAK 		=  4,
		TAB 			=  5,
		INTEGER 		=  6,
		IDENTIFIER 		=  7,
		IF_SMALL_1		=  8,
		IF_CAPITAL_1	=  9,
		IF			  	= 10,
		WHILE_SMALL_1 	= 11,
		WHILE_SMALL_2 	= 12,
		WHILE_SMALL_3 	= 13,
		WHILE_SMALL_4 	= 14,
		WHILE_CAPITAL_1	= 15,
		WHILE_CAPITAL_2 = 16,
		WHILE_CAPITAL_3 = 17,
		WHILE_CAPITAL_4 = 18,
		WHILE			= 19,
		SIGN 			= 20,
		COLON 			= 21,
		STAR 			= 22,
		EQUAL 			= 23,
		AND_1 			= 24,
		AND 			= 25,
		COMMENT_1 		= 26,
		COMMENT_2 		= 27,
		COLON_EQUAL 	= 28,
		COMPLEX_1 		= 29,
		CHECK			= 30
	};


	enum CaracterType {
		CT_DIGIT		=  0,
		CT_LETTER		=  1,
		CT_SMALL_I		=  2,
		CT_SMALL_F		=  3,
		CT_SMALL_W		=  4,
		CT_SMALL_H		=  5,
		CT_SMALL_L		=  6,
		CT_SMALL_E		=  7,
		CT_CAPITAL_I	=  8,
		CT_CAPITAL_F	=  9,
		CT_CAPITAL_W	= 10,
		CT_CAPITAL_H	= 11,
		CT_CAPITAL_L	= 12,
		CT_CAPITAL_E	= 13,
		CT_SIGN			= 14,
		CT_SIGN_COLON	= 15,
		CT_SIGN_STAR	= 16,
		CT_SIGN_EQUAL	= 17,
		CT_SIGN_AND		= 18,
		CT_BLANK		= 19,
		CT_LINE_BREAK	= 20,
		CT_TAB			= 21,
		CT_NOT_ALLOWED	= 22
	};
};
#endif /* AUTOMAT_SRC_AUTOMAT_H_ */

