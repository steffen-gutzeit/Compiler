/*
 * Token.h
 *
 *  Created on: 29.10.2014
 *      Author: root0r
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <stdint.h>

class Token {
public:
	Token(uint16_t row, uint16_t column, int tokenType, char * lexem);
	virtual ~Token();

	Token getToken();

	uint16_t getRow();
	uint16_t getColumn();
	const char *getTokenType();
	char *getLexem();
	int getTokenTypeInt();


	enum tokenTypeEnum {
		TT_DUMMY		=	0,
		TT_SIGN			=	1,
		TT_INTEGER		=	2,
		TT_IDENTIFIER	=	3,
		TT_IF			=	4,
		TT_WHILE		=	5,
		TT_PLUS			=   6,
		TT_MINUS        =   7,
		TT_SLASH        =   8,
		TT_STAR         =   9,
		TT_LESS         =   10,
		TT_MORE         =   11,
		TT_EQUAL        =   12,
		TT_DOUBLE_EQUAL =   13,
		TT_MORE_DOUBLE_LESS   =   14,
		TT_EXCLAMATION_MARK   =   15,
		TT_QUESTION_MARK      =   16,
		TT_AND                =   17,
		TT_SEMICOLON          =   18,
		TT_BRACKET_UPON       =   19,
		TT_BRACKET_CLOSE      =   20,
		TT_BRACE_UPON         =   21,
		TT_BRACE_CLOSE        =   22,
		TT_SQUARE_BRACKET_UPON     =   23,
		TT_SQUARE_BRACKET_CLOSE    =   24


	}tt;

private:
	uint16_t tokenID;
	uint16_t row;
	uint16_t column;
	int tokenType;
	char* lexem;

	int matchStateToType(uint16_t stateType);

};

#endif /* TOKEN_H_ */
