/*
 * Scanner.cpp
 *
 *  Created on: 27.03.2016
 *      Author: Manuel
 */

#include "Scanner.h"
#include <iostream>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

#define OVERFLOW_SIZE (511)

using namespace std;

Scanner::Scanner(char *inputFile, char *outputFile) {
    buffer = new Buffer(inputFile, outputFile);
	automat = new Automat();
	symtable = new Symtable();
	token = NULL;
	eof = false;

	this->currentState = 0;
	this->scannerIndex = 0;
	this->colIndex = 0;
	this->rowIndex = 1;
	this->tokenType = Token::TT_DUMMY;
	this->lexemLength = 0;
	this->currentChar = ' ';

	this->outputPath = outputFile;

	initBuffer();
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
	delete symtable;
	//delete token;
}

void Scanner::buildIntegerOrIdentifier(uint16_t state, uint16_t tokenType) {
	this->lexemLength++;

	if (this->lexemLength < OVERFLOW_SIZE) {
		this->currentChar = this->buffer->getChar();
	} else {
		this->buffer->getChar();
		this->currentChar = ' ';
	}

	this->internBuffer[this->scannerIndex] = this->currentChar;
	this->scannerIndex++;

	if (this->getCurrentState(this->currentChar) != state) {
		this->initForTokenGeneration(tokenType);
	}
}

void Scanner::initForTokenGeneration(uint16_t tokenType) {
	this->decrementScannerAndBuffer();
	this->internBuffer[this->scannerIndex] = '\0';
	this->tokenType = tokenType;
}

void Scanner::throwSpecialToken(uint16_t tokenType) {
	this->currentChar = this->buffer->getChar();
	this->clearInternBuffer();
	this->internBuffer[0] = this->currentChar;
	this->tokenType = tokenType;
	this->scannerIndex = 1;

	if (this->currentChar != ' ') {
		this->generateToken(this->tokenType);
	} else {
		this->clearInternBuffer();
	}
}

void Scanner::getNextChar() {
	this->currentChar = this->buffer->getChar();
	this->internBuffer[this->scannerIndex] = this->currentChar;
	this->scannerIndex++;
}

void Scanner::lookupNextChar() {
	this->nextChar = this->buffer->getChar();
	//this->internBuffer[this->scannerIndex] = this->currentChar;
	//this->scannerIndex++;
	this->buffer->dekrementBufferPointer();
}

void Scanner::decrementScannerAndBuffer() {
	this->scannerIndex--;
	this->buffer->dekrementBufferPointer();
}

void Scanner::whileIfCascade(uint16_t state) {
	this->getNextChar();

	if (this->getCurrentState(this->currentChar) == state) {
		this->lexemLength++;
	} else {
		if (this->getCurrentState(this->currentChar) == Automat::TOKEN) {
			this->lexemLength++;
			this->lexemLength++;
		} else {
			this->lexemLength++;
		}
		this->initForTokenGeneration(Token::TT_IDENTIFIER);
	}

}

void Scanner::setLexemData(int16_t lexemLength, uint16_t tokenType) {
	this->lexemLength = lexemLength;
	this->tokenType = tokenType;
}

Token *Scanner::getNextToken() {
    //End of File Schaltvariable
    bool eot = false;

    //Hauptschleife solange das Ende der Datei nicht erreicht ist
	while(eot == false){
		if(this->currentChar == '\0'){
			//End of File ist erreicht
			eof = true;
			eot = true;

			token = NULL;
			//Nötig, damit zum Schluss der nicht voll Buffer geschrieben wird
			buffer->addCharsToOutBuffer("\0");
			//this->generateToken(this->tokenType);
		} else {
			//cout << "\t" << (this->currentState) << endl;
			switch (this->currentState) {
			case Automat::INIT:
				this->lexemLength = 0;
				this->getNextChar();
				//cout << this->currentChar << endl;
				break;

			case Automat::TOKEN:
				if(this->tokenType != Token::TT_BLANK){
					token = this->generateToken(this->tokenType);
					eot = true;
				}else{
					generateTokenPrint(this->tokenType);
					eot = false;
				}


				this->colIndex += this->lexemLength;
				this->lexemLength = 0;
				break;

			case Automat::ERROR:
				this->setLexemData(1, Token::TT_ERROR);
				printErrorToken();
				break;

			case Automat::BLANK:
				this->colIndex++;
				this->clearInternBuffer();
				this->tokenType = Token::TT_BLANK;
				break;

			case Automat::LINE_BREAK:
				this->colIndex = 0;
				this->rowIndex++;
				this->tokenType = Token::TT_BLANK;
				break;

			case Automat::TAB:
				this->setLexemData(4, Token::TT_BLANK);
				break;

			case Automat::INTEGER:
				this->buildIntegerOrIdentifier(Automat::INTEGER, Token::TT_INTEGER);
				break;

			case Automat::IDENTIFIER:
				this->buildIntegerOrIdentifier(Automat::IDENTIFIER, Token::TT_IDENTIFIER);
				break;

			case Automat::IF_SMALL_1:
				lookupNextChar();
				if (this->nextChar == 'f') {
					this->whileIfCascade(Automat::IF);
				} else if (this->nextChar == 'n') {
					this->whileIfCascade(Automat::INT_SMALL_1);
				}
				break;

			case Automat::IF_CAPITAL_1:
				lookupNextChar();
				if (this->nextChar == 'F') {
					this->whileIfCascade(Automat::IF);
				} else if (this->nextChar == 'N') {
					this->whileIfCascade(Automat::INT_CAPITAL_1);
				}
				break;

			case Automat::IF:
				this->getNextChar();

				if (this->getCurrentState(this->currentChar) != Automat::IDENTIFIER) {
					this->lexemLength = 2;
					this->initForTokenGeneration(Token::TT_IF);
				}
				break;

			case Automat::WHILE_SMALL_1:
				lookupNextChar();
				if (this->nextChar == 'h') {
					this->whileIfCascade(Automat::WHILE_SMALL_2);
				} else if (this->nextChar == 'r') {
					this->whileIfCascade(Automat::WRITE_SMALL_1);
				}
				break;

			case Automat::WHILE_SMALL_2:
				this->whileIfCascade(Automat::WHILE_SMALL_3);
				break;

			case Automat::WHILE_SMALL_3:
				this->whileIfCascade(Automat::WHILE_SMALL_4);
				break;

			case Automat::WHILE_SMALL_4:
				this->whileIfCascade(Automat::WHILE);
				break;

			case Automat::WHILE_CAPITAL_1:
				lookupNextChar();
				if (this->nextChar == 'H') {
					this->whileIfCascade(Automat::WHILE_CAPITAL_2);
				} else if (this->nextChar == 'R') {
					this->whileIfCascade(Automat::WRITE_CAPITAL_1);
				}
				break;

			case Automat::WHILE_CAPITAL_2:
				this->whileIfCascade(Automat::WHILE_CAPITAL_3);
				break;

			case Automat::WHILE_CAPITAL_3:
				this->whileIfCascade(Automat::WHILE_CAPITAL_4);
				break;

			case Automat::WHILE_CAPITAL_4:
				this->whileIfCascade(Automat::WHILE);
				break;

			case Automat::WHILE:
				this->getNextChar();

				if (this->getCurrentState(this->currentChar) != Automat::IDENTIFIER) {
					this->lexemLength = 5;
					this->initForTokenGeneration(Token::TT_WHILE);
				} else {
					this->lexemLength++;
				}
				break;

			case Automat::READ_SMALL_1:

				this->whileIfCascade(Automat::READ_SMALL_2);
				break;

			case Automat::READ_SMALL_2:
				this->whileIfCascade(Automat::READ_SMALL_3);
				break;

			case Automat::READ_SMALL_3:
				this->whileIfCascade(Automat::READ);
				break;

			case Automat::READ_CAPITAL_1:
				this->whileIfCascade(Automat::READ_CAPITAL_2);
				break;

			case Automat::READ_CAPITAL_2:
				this->whileIfCascade(Automat::READ_CAPITAL_3);
				break;

			case Automat::READ_CAPITAL_3:
				this->whileIfCascade(Automat::READ);
				break;

			case Automat::READ:
				this->getNextChar();

				if (this->getCurrentState(this->currentChar) != Automat::IDENTIFIER) {
					this->lexemLength = 4;
					this->initForTokenGeneration(Token::TT_READ);
				} else {
					this->lexemLength++;
				}
				break;

			case Automat::INT_SMALL_1:
				this->whileIfCascade(Automat::INT);
				break;

			case Automat::INT_CAPITAL_1:
				this->whileIfCascade(Automat::INT);
				break;

			case Automat::INT:
				this->getNextChar();

				if (this->getCurrentState(this->currentChar) != Automat::IDENTIFIER) {
					this->lexemLength = 3;
					this->initForTokenGeneration(Token::TT_INT);
				} else {
					this->lexemLength++;
				}
				break;

			case Automat::WRITE_SMALL_1:
				this->whileIfCascade(Automat::WRITE_SMALL_2);
				break;

			case Automat::WRITE_SMALL_2:
				this->whileIfCascade(Automat::WRITE_SMALL_3);
				break;

			case Automat::WRITE_SMALL_3:
				this->whileIfCascade(Automat::WRITE);
				break;

			case Automat::WRITE_CAPITAL_1:
				this->whileIfCascade(Automat::WRITE_CAPITAL_2);
				break;

			case Automat::WRITE_CAPITAL_2:
				this->whileIfCascade(Automat::WRITE_CAPITAL_3);
				break;

			case Automat::WRITE_CAPITAL_3:
				this->whileIfCascade(Automat::WRITE);
				break;

			case Automat::WRITE:
				this->getNextChar();

				if (this->getCurrentState(this->currentChar) != Automat::IDENTIFIER) {
					this->lexemLength = 5;
					this->initForTokenGeneration(Token::TT_WRITE);
				} else {
					this->lexemLength++;
				}
				break;

			case Automat::ELSE_SMALL_1:
				this->whileIfCascade(Automat::ELSE_SMALL_2);
				break;

			case Automat::ELSE_SMALL_2:
				this->whileIfCascade(Automat::ELSE_SMALL_3);
				break;

			case Automat::ELSE_SMALL_3:
				this->whileIfCascade(Automat::ELSE);
				break;

			case Automat::ELSE_CAPITAL_1:
				this->whileIfCascade(Automat::ELSE_CAPITAL_2);
				break;

			case Automat::ELSE_CAPITAL_2:
				this->whileIfCascade(Automat::ELSE_CAPITAL_3);
				break;

			case Automat::ELSE_CAPITAL_3:
				this->whileIfCascade(Automat::ELSE);
				break;

			case Automat::ELSE:
				this->getNextChar();

				if (this->getCurrentState(this->currentChar) != Automat::IDENTIFIER) {
					this->lexemLength = 4;
					this->initForTokenGeneration(Token::TT_ELSE);
				} else {
					this->lexemLength++;
				}
				break;

			case Automat::SIGN:
				this->setLexemData(1, Token::TT_SIGN);
				break;

			case Automat::COLON:
				this->lexemLength++;
				this->getNextChar();

				if (this->getCurrentState(this->currentChar) == Automat::COMMENT_1) {
					this->clearInternBuffer();
				} else if (!(this->getCurrentState(this->currentChar) == Automat::COLON_EQUAL)) {
					this->initForTokenGeneration(Token::TT_COLON);
				}
				break;

			case Automat::STAR:
				this->setLexemData(1, Token::TT_STAR);
				break;

			case Automat::EQUAL:
				this->lexemLength++;
				this->getNextChar();

				if (this->getCurrentState(this->currentChar) != Automat::COMPLEX_1) {
					this->initForTokenGeneration(Token::TT_EQUAL);
				}
				break;

			case Automat::AND_1:
				this->lexemLength++;
				this->getNextChar();

				if (this->getCurrentState(this->currentChar) == Automat::AND) {
					this->tokenType = Token::TT_AND;
				}else{
					//Bugfix
					this->colIndex++;
					this->clearInternBuffer();
					decrementColCount();
					this->buffer->dekrementBufferPointer();
					this->internBuffer[0] = '&';
					this->tokenType = Token::TT_ERROR;
				}

				break;

			case Automat::AND:
				this->setLexemData(2, Token::TT_AND);
				break;

			case Automat::COMMENT_1:
				this->lexemLength++;
				this->currentChar = this->buffer->getChar();

				if (currentChar == '\n') {
					this->rowIndex++;
				}

				if (this->getCurrentState(this->currentChar) == Automat::COMMENT_2) {
					this->tokenType = Token::TT_DUMMY;
				}
				break;

			case Automat::COMMENT_2:
				this->lexemLength++;
				this->currentChar = this->buffer->getChar();

				if (this->getCurrentState(this->currentChar) == Automat::TOKEN) {
					this->clearInternBuffer();
					this->scannerIndex = 0;
					this->lexemLength++;

					this->tokenType = Token::TT_DUMMY;
				}
				break;

			case Automat::COLON_EQUAL:
				this->setLexemData(2, Token::TT_COLON_EQUAL);
				break;

			case Automat::COMPLEX_1:
				this->lexemLength = 3;
				this->getNextChar();

				if (this->currentChar == '=') {
					this->tokenType = Token::TT_MORE_COLON_MORE;
				}
				break;

			case Automat::CHECK:
				// Fix
				this->internBuffer[0] = ':';
				this->internBuffer[1] = '\0';

				this->setLexemData(1, Token::TT_EQUAL);
				token = this->generateToken(Token::TT_EQUAL);
				eot = true;
				this->buffer->dekrementBufferPointer(2);
				break;
			} // END SELECT
		} // END IF

		if (this->lexemLength <= OVERFLOW_SIZE) {
			this->currentState = this->setCurrentState(this->currentChar);
		} else {
			this->currentState = this->automat->setTokenState();
		}
	} // END WHILE

	return token;
} // END METHODE

Token *Scanner::getCurrentToken() {

	return this->token;
}

void Scanner::incrementColCount() {
	this->colIndex++;
}

void Scanner::decrementColCount() {
	this->colIndex--;
}

uint16_t Scanner::setCurrentState(char currentChar) {
	// gebe Zeichen an Automat und erhalte aktuellen Status
	return this->automat->testChar(currentChar);
}

uint16_t Scanner::getCurrentState(char currentChar) {
	// gebe Zeichen an Automat und erhalte aktuellen Status
	return this->automat->getStateByChar(currentChar);
}

Token *Scanner::generateToken(uint16_t typ) {
	if (this->internBuffer[0] != '\0') {

			if(typ == token->TT_INTEGER){
				checkInteger(typ);
			}else{
				//Pruefen ob es in die Symboltabelle eingetragen werden muss
				if(typ == token->TT_IDENTIFIER || typ == token->TT_WHILE || typ == token->TT_IF){

					//Key Value zurueck bekommen
					char *key = symtable->insert(this->internBuffer, typ);
					//printf("Scanner: %p \n", key);
					//Token erstellen mit Verweis auf Symboltabelle
					//cout << "Token: " << key << endl;
					this->token = new Token(this->rowIndex, this->colIndex, typ, key);
				}else{
					this->token = new Token(this->rowIndex, this->colIndex, typ, this->internBuffer);
				}

			}

			//Falls If oder While zu einem  Identifier werden
			char tmp = this->internBuffer[0];
			if((typ == token->TT_IDENTIFIER) && ((tmp == 'i') || (tmp == 'I') || (tmp == 'w') || (tmp == 'W'))){
				decrementColCount();
			}




		printToken();

		//Temporaerer Fix für den Memory Leak durch die erstellten Token Objekte
		/*if(this->token){
			delete(this->token);
		}*/
	}
	this->clearInternBuffer();
	//writeOutput();

	/*if (typ == Token::TT_IDENTIFIER) {
		symTable->insert(this->internBuffer, typ);
 		for(int i = 0; i < this->scannerIndex; i++){
	        //cout << this->internBuffer[i];// << this->automat->getCols() << " - " << this->automat->getRows();
	    }
	}*/

	return this->token;

}

void Scanner::generateTokenPrint(uint16_t typ) {
	if (this->internBuffer[0] != '\0') {

			if(typ == token->TT_INTEGER){
				checkInteger(typ);
			}else{
				//Pruefen ob es in die Symboltabelle eingetragen werden muss
				if(typ == token->TT_IDENTIFIER || typ == token->TT_WHILE || typ == token->TT_IF){

					//Key Value zurueck bekommen
					char *key = symtable->insert(this->internBuffer, typ);
					//printf("Scanner: %p \n", key);
					//Token erstellen mit Verweis auf Symboltabelle
					//cout << "Token: " << key << endl;
					this->token = new Token(this->rowIndex, this->colIndex, typ, key);
				}else{
					this->token = new Token(this->rowIndex, this->colIndex, typ, this->internBuffer);
				}

			}

			//Falls If oder While zu einem  Identifier werden
			char tmp = this->internBuffer[0];
			if((typ == token->TT_IDENTIFIER) && ((tmp == 'i') || (tmp == 'I') || (tmp == 'w') || (tmp == 'W'))){
				decrementColCount();
			}




		printToken();

		//Temporaerer Fix für den Memory Leak durch die erstellten Token Objekte
		/*if(this->token){
			delete(this->token);
		}*/
	}
	this->clearInternBuffer();
	//writeOutput();

	/*if (typ == Token::TT_IDENTIFIER) {
		symTable->insert(this->internBuffer, typ);
 		for(int i = 0; i < this->scannerIndex; i++){
	        //cout << this->internBuffer[i];// << this->automat->getCols() << " - " << this->automat->getRows();
	    }
	}*/


}


void Scanner::checkInteger(uint16_t typ){
	char *numberTemp = this->internBuffer;
	char *end;

	char textOverflowInt[] = "Overflow";
	long test;

	errno = 0;
	test = strtol(numberTemp,&end,10);


	if (errno == ERANGE || test < 0 || test > 4294967295) { // ERANGE
		//Integer Overflow
		this->tokenType = Token::TT_ERROR;
	  	this->token = new Token(this->rowIndex, this->colIndex, Token::TT_ERROR, textOverflowInt);
	  	fprintf(stderr, "Overflow Int  Line: %u \tColumn: %u\n", this->rowIndex, (this->colIndex + 1));

	} else {
		//regulaeres Integer

		//Pruefe auf voranstehende 0
		if(this->internBuffer[0] == '0'){

			int size = 0;

			//Ermittle Stellenanzahl
			size = sizeOfNumber(test);
			char resultLine[size + 1];

			//Konvertiere int zu einem chararray
			char *number = intToChar(test, size, resultLine);

			int i = 0;

			while(number[i] != '\0'){
				this->internBuffer[i] = number[i];
				i++;
			}

			this->internBuffer[i] = '\0';


		}

		this->token = new Token(this->rowIndex, this->colIndex, typ, this->internBuffer);





	}

}


void Scanner::printToken() {
	if ((this->tokenType != Token::TT_BLANK)) {

		int size = 0;

		char textNewLine[] = "\n";
		char textTab[] = "\t";
		char textValue[] = "Value:  ";
		char textLexem[] = "Lexem:  ";
		char textError[] = "Symbol: ";


		//Token Bezichner
		char textToken[] = "Token: ";
		buffer->addCharsToOutBuffer(textToken);

		//TokenType
		const char *textTokenTypeTemp = this->token->getTokenType();
		char textTokenType[2];
		textTokenType[1] = '\0';

		int i = 0;
		while(textTokenTypeTemp[i] != '\0'){
			textTokenType[0] = textTokenTypeTemp[i];
			buffer->addCharsToOutBuffer(textTokenType);
			i++;
		}

		//Line
		char textLine[] = "Line: ";
		buffer->addCharsToOutBuffer(textLine);

		//Ermittle Stellenanzahl
		size = sizeOfNumber(token->getRow());
		char resultLine[size + 1];

		//Konvertiere int zu einem chararray
		buffer->addCharsToOutBuffer(intToChar(token->getRow(), size, resultLine));

		//Setze Tab
		buffer->addCharsToOutBuffer(textTab);

		if(size == 1){
			//Setze zweiten Tab (Schönheitskorrektur bei Zeilen 1 - 9)
			buffer->addCharsToOutBuffer(textTab);
		}



		//Column
		char textColumn[] = "Column: ";
		buffer->addCharsToOutBuffer(textColumn);

		//Ermittle Stellenanzahl
		size = sizeOfNumber(token->getCol() + 1);
		char resultColumn[size + 1];

		//Konvertiere int zu einem chararray
		buffer->addCharsToOutBuffer(intToChar(token->getCol() + 1, size, resultColumn));

		//Ausgabe von Integer Value
		if(this->tokenType == Token::TT_INTEGER){
			//Setze Tab
			buffer->addCharsToOutBuffer(textTab);

			//Label ausgeben
			buffer->addCharsToOutBuffer(textValue);

			//Hole Integer Value und pruefe auf Bereichsueberschreitung (uint32 -> 10 Dezimalstellen)
			/*int i= 0;
			char *numberTemp = token->getLexem();

			while(numberTemp[i] != '\0'){
				i++;
			}

			if(i < 11){
				buffer->addCharsToOutBuffer(token->getLexem());
			}else{
				fprintf(stderr, "Overflow Int  Line: %u \tColumn: %u\n", this->rowIndex, (this->colIndex + 1));
				buffer->addCharsToOutBuffer(textOverflow);
			}*/

			buffer->addCharsToOutBuffer(token->getLexem());
		}

		//Ausgabe von Lexem
		if(this->tokenType == Token::TT_IDENTIFIER){
			//Setze Tab
			buffer->addCharsToOutBuffer(textTab);

			//Label ausgeben
			buffer->addCharsToOutBuffer(textLexem);

			//Hole Lexem
			buffer->addCharsToOutBuffer(token->getLexem());


		}

		//Ausgabe von Error Symbol
		if(this->tokenType == Token::TT_ERROR){
			//Setze Tab
			buffer->addCharsToOutBuffer(textTab);

			//Label ausgeben
			buffer->addCharsToOutBuffer(textError);

			//Hole Lexem
			buffer->addCharsToOutBuffer(token->getLexem());


		}


		//Zeilenumbruch
		buffer->addCharsToOutBuffer(textNewLine);




		//cout << this->token->getRow() << ":" << (this->token->getCol() + 1) << " \t TYPE: " << this->token->getTokenType() << ":   ";

		//cout << output << endl;

		//for(int i = 0; i < this->scannerIndex; i++){
			//cout << this->internBuffer[i];
		//}

		//cout << endl;


	}
}

void Scanner::printErrorToken(){
	fprintf(stderr, "unknown Token Line: %u \tColumn: %u \tSymbol: %s \n", this->rowIndex, (this->colIndex + 1), this->internBuffer);

}

int Scanner::sizeOfNumber(uint32_t digit){

	int count = 0;

	//Bestimme Stellenanzahl
	while(digit != 0){
		digit = digit / 10;
		count++;
	}

	return count;
}


char *Scanner::intToChar(uint32_t digit, int size, char result[]){

	//Modulo Rechnung zur Umwandlung
	for(int i = 0; i < size; i++){
		result[(size - 1) - i] = digit % 10 + '0';
		//cout << result[(size - 1) - i] << endl;
		digit = digit / 10;
	}

	result[size] = '\0';

	return result;


}

void Scanner::clearInternBuffer() {
	int i = 0;
	while (i < this->scannerIndex) {
		this->internBuffer[i] = '\0';
		i++;
	}

	this->scannerIndex = 0;
}


void Scanner::initBuffer() {
	int i = 0;
	while (i < 512) {
		this->internBuffer[i] = '\0';
		i++;
	}
}
