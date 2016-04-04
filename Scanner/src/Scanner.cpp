/*
 * Scanner.cpp
 *
 *  Created on: 27.03.2016
 *      Author: Manuel
 */

#include "Scanner.h"
#include <iostream>

using namespace std;

Scanner::Scanner(char *inputFile, char *outputFile) {
    buffer = new Buffer(inputFile, outputFile);
	automat = new Automat();
	//token = NULL;

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
	//delete token;
}

void Scanner::buildIntegerOrIdentifier(uint16_t state, uint16_t tokenType) {
	this->lexemLength++;
	this->currentChar = this->buffer->getChar();
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

void Scanner::decrementScannerAndBuffer() {
	this->scannerIndex--;
	this->buffer->dekrementBufferPointer();
}

void Scanner::whileIfCascade(uint16_t state) {
	this->getNextChar();

	if (this->getCurrentState(this->currentChar) == state) {
		this->lexemLength++;
	} else {
		this->initForTokenGeneration(Token::TT_IDENTIFIER);
		this->lexemLength++;
	}

}

void Scanner::setLexemData(int16_t lexemLength, uint16_t tokenType) {
	this->lexemLength = lexemLength;
	this->tokenType = tokenType;
}

void Scanner::getNextToken() {
    //End of File Schaltvariable
    bool eof = false;

    //Hauptschleife solange das Ende der Datei nicht erreicht ist
	while(eof == false){
		if(this->currentChar == '\0'){
			eof = true;

			this->generateToken(this->tokenType);
		} else {
			//cout << this->getCurrentState(this->currentChar) << " " << currentState << " " << this->rowIndex << ":" << this->colIndex << endl;
			switch (this->currentState) {
			case Automat::INIT:
				this->lexemLength = 0;
				this->getNextChar();
				break;

			case Automat::TOKEN:
				this->generateToken(this->tokenType);

				this->colIndex += this->lexemLength;
				this->lexemLength = 0;
				break;

			case Automat::ERROR:
				this->setLexemData(1, Token::TT_ERROR);
				/*this->scannerIndex--;
				this->buffer->dekrementBufferPointer();
				this->internBuffer[this->scannerIndex] = '\0';
				this->tokenType = tokenType;*/
				//this->initForTokenGeneration(Token::TT_ERROR);
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

			case Automat::IF_1:
				this->whileIfCascade(Automat::IF);
				break;


			case Automat::IF:
				this->getNextChar();

				if (this->getCurrentState(this->currentChar) != Automat::IDENTIFIER) {
					this->lexemLength = 2;
					this->initForTokenGeneration(Token::TT_IF);
				}
				break;

			case Automat::WHILE_1:
				this->whileIfCascade(Automat::WHILE_2);
				break;

			case Automat::WHILE_2:
				this->whileIfCascade(Automat::WHILE_3);
				break;

			case Automat::WHILE_3:
				this->whileIfCascade(Automat::WHILE_4);
				break;

			case Automat::WHILE_4:
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
				} else {
					this->buffer->dekrementBufferPointer(3);
				}
				break;

			case Automat::CHECK:
				// =:+
				this->throwSpecialToken(Token::TT_EQUAL);

				this->colIndex++;
				this->throwSpecialToken(Token::TT_COLON);
				this->colIndex++;
				this->colIndex++;
				//@todo: TokenType anpassen
				this->throwSpecialToken(Token::TT_DUMMY);

				break;
			} // END SELECT
		} // END IF

		this->currentState = this->setCurrentState(this->currentChar);
	} // END WHILE
} // END METHODE

void Scanner::incrementColCount() {
	this->colIndex++;
}

uint16_t Scanner::setCurrentState(char currentChar) {
	// gebe Zeichen an Automat und erhalte aktuellen Status
	return this->automat->testChar(currentChar);
}

uint16_t Scanner::getCurrentState(char currentChar) {
	// gebe Zeichen an Automat und erhalte aktuellen Status
	return this->automat->getStateByChar(currentChar);
}



void Scanner::generateToken(uint16_t typ) {
	if (this->internBuffer[0] != '\0') {
		this->token = new Token(this->rowIndex, this->colIndex, typ, this->internBuffer);
		printToken();
	}
	this->clearInternBuffer();
	//writeOutput();

	/*if (typ == Token::TT_IDENTIFIER) {
		symTable->insert(this->internBuffer, typ);
 		for(int i = 0; i < this->scannerIndex; i++){
	        //cout << this->internBuffer[i];// << this->automat->getCols() << " - " << this->automat->getRows();
	    }
	}*/

	delete(this->token);
}


void Scanner::printToken() {
	if (this->tokenType != Token::TT_BLANK) {
		cout << this->token->getRow() << ":" << (this->token->getCol() + 1) << " \t TYPE: " << this->token->getTokenType() << ":   ";
		for(int i = 0; i < this->scannerIndex; i++){
			cout << this->internBuffer[i];
		}

		cout << endl;
	}
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
