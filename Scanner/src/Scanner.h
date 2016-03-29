/*
 * Scanner.h
 *
 *  Created on: 27.03.2016
 *      Author: Manuel
 */

#ifndef SCANNER_SRC_SCANNER_H_
#define SCANNER_SRC_SCANNER_H_

//#include "Automat.h"
#include "../../Buffer/src/Buffer.h"
#include "../../Automat/src/Automat.h"
#include "../../Token/src/Token.h"
#include <stdint.h>

class Scanner {
public:
	Scanner(char *inputFile, char *outputFile);
	virtual ~Scanner();

	void getNextToken();


private:
	Automat *automat;
	Buffer *buffer;
	Token *token;


	char internBuffer[512];
	char currentChar;
	char *outputPath;
	uint16_t scannerIndex;
	uint32_t currentState;

	uint32_t colIndex;
	uint32_t rowIndex;

	uint8_t tokenType;
	uint8_t forceState;
	uint8_t lexemLength;

	uint16_t setCurrentState(char currentChar);
	void printToken();
	void incrementColCount();
	void generateToken(uint16_t typ);
	void clearInternBuffer();

	void buildIntegerOrIdentifier(uint16_t state, uint16_t tokenType);
	void forceTokenGeneration(uint16_t state, uint16_t tokenType);
	void throwSpecialToken(uint16_t tokenType);
	void readNextChar();
};
#endif /* SCANNER_SRC_SCANNER_H_ */

