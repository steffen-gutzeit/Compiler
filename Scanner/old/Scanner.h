/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include <iostream>

#include "../../Buffer/src/Buffer.h"
#include "../../Automat/src/Automat.h"
#include "../../Token/src/Token.h"
#include "../../Symtable/src/Symtable.h"

#ifndef SCANNER_H_
#define SCANNER_H_

#define COUNT_BITS		(0x00C0)
#define COMMENT_BIT 	(1 << 12)
#define NEW_LINE_BIT 	(1 << 11)
#define BLANK_BIT 		(1 << 10)
#define ERROR_BIT 		(1 << 9)
#define TOKEN_BIT 		(1 << 8)


class Scanner {
private:

    char *outputPath;
	char currentChar;
	char internBuffer[512];
	int scannerIndex;

	uint16_t currentState;
	uint8_t commentFlag;

	Buffer *buffer;
	Automat *automat;
	Token *token;
	Symtable *symTable;

	void generateToken(int typ);

	//@todo kann weg
	void printToken();
	void printErrorChar();
	void writeOutput();

	//Schreiben der Output Datei
	int file_descriptor;
	int byte_count;

	int charToInt();


public:
	Scanner(char *inputFile, char *outputFile);
	virtual ~Scanner();
	void getNextToken();
    void init();

    int getTokenType(char *lexem);


};

#endif /* SCANNER_H_ */
