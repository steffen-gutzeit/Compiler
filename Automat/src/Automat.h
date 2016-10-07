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
	uint16_t setTokenState();

	uint16_t transitionTable[55][35];
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
		READ_SMALL_1	= 20,
		READ_SMALL_2	= 21,
		READ_SMALL_3	= 22,
		READ_CAPITAL_1	= 23,
		READ_CAPITAL_2	= 24,
		READ_CAPITAL_3	= 25,
		READ			= 26,
		INT_SMALL_1		= 27,
		INT_CAPITAL_1	= 29,
		INT				= 31,
		WRITE_SMALL_1	= 32,
		WRITE_SMALL_2	= 33,
		WRITE_SMALL_3	= 34,
		WRITE_CAPITAL_1 = 36,
		WRITE_CAPITAL_2	= 37,
		WRITE_CAPITAL_3	= 38,
		WRITE			= 40,
		ELSE_SMALL_1	= 41,
		ELSE_SMALL_2	= 42,
		ELSE_SMALL_3	= 43,
		ELSE_CAPITAL_1	= 44,
		ELSE_CAPITAL_2	= 45,
		ELSE_CAPITAL_3	= 46,
		ELSE			= 47,
		SIGN 			= 48,
		COLON 			= 49,
		STAR 			= 50,
		EQUAL 			= 51,
		AND_1 			= 52,
		AND 			= 53,
		COMMENT_1 		= 54,
		COMMENT_2 		= 55,
		COLON_EQUAL 	= 56,
		COMPLEX_1 		= 57,
		CHECK			= 58
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
		CT_SMALL_R		= 14,
		CT_SMALL_A		= 15,
		CT_SMALL_D		= 16,
		CT_SMALL_N		= 17,
		CT_SMALL_T		= 18,
		CT_SMALL_S		= 19,
		CT_CAPITAL_R	= 20,
		CT_CAPITAL_A	= 21,
		CT_CAPITAL_D	= 22,
		CT_CAPITAL_N	= 23,
		CT_CAPITAL_T	= 24,
		CT_CAPITAL_S	= 25,
		CT_SIGN			= 26,
		CT_SIGN_COLON	= 27,
		CT_SIGN_STAR	= 28,
		CT_SIGN_EQUAL	= 29,
		CT_SIGN_AND		= 30,
		CT_BLANK		= 31,
		CT_LINE_BREAK	= 32,
		CT_TAB			= 33,
		CT_NOT_ALLOWED	= 34
	};
};
#endif /* AUTOMAT_SRC_AUTOMAT_H_ */
