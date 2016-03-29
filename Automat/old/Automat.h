/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */
#ifndef Automat_H_
#define Automat_H_

//#include "Scanner.h"

#include <iostream>
#include <stdint.h>


class Automat {
public:
	Automat();
	virtual ~Automat();

	uint16_t testChar(char currentChar);
	uint16_t getRows();
	uint16_t getCols();
	void init();
	void printBinaries(uint16_t digit);
	void incrementRowCount();
	void incrementColCount();
	void initColCount();
	void decrementColCount();
	void decrementColCount(int i);
	uint16_t characterType(char testChar);

	enum StateNames {
		//uint16_t codiert!!! also 0000 0000 0000 0000 bzw. 0xFFFF möglich!
		// BIT 0 - 6:  Spalte der Matrix
		// BIT 7 - 8:  Anzahl Schritte seit letztem gültigem Token
		// BIT 9 - 12: Spezialflags - z.B: Token, Error, Whitespace... (siehe Scanner.h)

		S_000 = 0x0000,	// 0000 0000 00 00 0000 - Startzustand
		DI_01 = 0x0001,	// 0000 0000 00 00 0001 - Integer 0-9 Hybridzustand
		CH_01 = 0x0002,	// 0000 0000 00 00 0010 - Bezeichner  Hybridzustand
		SS_01 = 0x0103,	// 0000 0001 00 00 0011 - Ein nicht zusammen gesteztes Zeichen Finalzustand
		SS_02 = 0x0004,	// 0000 0000 00 00 0100 - <        Hybridzustand
		SS_03 = 0x0005,	// 0000 0000 00 00 0101 - <:       Übergangszustand
		CS_01 = 0x0006,	// 0000 0000 00 00 0110 - <:>      Finalzsutand
		SS_04 = 0x0007,	// 0000 0000 00 00 0111 - :        Hybridzsutand
		CS_02 = 0x0008,	// 0000 0000 00 00 1000 - :=       Finalzustand
		KO_01 = 0x1009,	// 0001 0000 00 00 1001 -
		KO_02 = 0x100A,	// 0001 0000 00 00 1010 -
		KO_03 = 0x100B,	// 0001 0000 00 00 1011 -
		KO_04 = 0x100C,	// 0001 0000 00 00 1100 -
		//KO_05 = 0x100D,	// 0001 0000 00 00 1101 -
		KO_05 = 0x0100,	// 0000 0001 00 00 0000 -

		TOKEN = 0x0100,	// 0000 0001 00 00 0000 -
		ERROR =	0x0250,	// 0000 0010 01 01 0000 -
		TOKE2 =	0x0180,	// 0000 0001 10 00 0000 -
		ERRO2 =	0x0292,	// 0000 0010 10 01 0100 -
		NAERA = 0x0215,	// 0000 0010 00 01 0101

		WS_01 = 0x0400,	// 0000 0100 00 00 0000 -         Sonderzustand
		DELWS = 0x0000,	// 0000 0000 00 00 0000
		LNBRK = 0x080F	// 0000 1000 00 00 1111
	};

    enum CharacterType {
        CT_LETTER 		= 0,
        CT_NUMERIC		= 1,
		CT_SIGN			= 2,
        CT_SIGN_LESS 	= 3,
        CT_SIGN_DOUBLE	= 4,
        CT_SIGN_MORE	= 5,
        CT_SIGN_EQUAL	= 6,
        CT_SLASH 		= 7,
        CT_STAR			= 8,
		CT_WHITE_SPACE	= 9,
		CT_LINE_BREAK	= 10,
		CT_ERROR		= 11
    };

private:
    static uint16_t transitionTable[12][21];
    uint16_t currentState;
    uint16_t rows;
    uint16_t cols;

};

#endif /* Automat_H_ */
