/*
 * Token.h
 *
 *  Created on: 27.03.2016
 *      Author: Manuel
 */

#ifndef TOKEN_SRC_TOKEN_H_
#define TOKEN_SRC_TOKEN_H_

#include <stdint.h>
#include "../../Automat/src/Automat.h"

class Token {
public:
	Token(uint16_t row, uint32_t column, uint32_t tokenType, char *lexem);
	virtual ~Token();

	Token getToken();
	uint32_t getCol();
	uint32_t getRow();
	uint16_t matchStateToType(uint16_t stateType);
	char *getLexem();
	const char *getTokenType();
	const char *getTokenType(uint16_t &tokenType);

	enum tokenType {
		TT_DUMMY				=  0,
		TT_IDENTIFIER			=  1,
		TT_INTEGER				=  2,
		TT_IF					=  3,
		TT_WHILE				=  4,
		TT_SIGN					=  5,

		TT_PLUS					=  6,
		TT_MINUS        		=  7,
		TT_COLON        		=  8,
		TT_STAR         		=  9,
		TT_LESS         		= 10,
		TT_MORE         		= 11,
		TT_EQUAL        		= 12,
		TT_COLON_EQUAL 			= 13,
		TT_MORE_COLON_MORE   	= 14,
		TT_EXCLAMATION_MARK   	= 15,
		//TT_QUESTION_MARK      	= 16,
		TT_AND                	= 17,
		TT_SEMICOLON          	= 18,
		// (
		TT_BRACKET_UPON       	= 19,
		TT_BRACKET_CLOSE      	= 20,
		// {
		TT_BRACE_UPON         	= 21,
		TT_BRACE_CLOSE        	= 22,
		// [
		TT_SQUARE_BRACKET_UPON  = 23,
		TT_SQUARE_BRACKET_CLOSE = 24,

		TT_BLANK				= 25,
		TT_ERROR				= 26,

		TT_READ					= 27,
		TT_WRITE				= 28,
		TT_ELSE					= 29,
		TT_INT					= 30
	};

private:
	uint16_t tokenID;
	uint32_t row;
	uint32_t column;
	uint8_t tokenType;
	char *lexem;

	void setTokenTypeSign(char lexem);
};
#endif /* TOKEN_SRC_TOKEN_H_ */
