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
	this->outputPath = outputFile;
    buffer = new Buffer(inputFile, outputFile);
	automat = new Automat();
	token = NULL;

	this->currentState = 0;
	this->scannerIndex = 0;
	this->colIndex = 1;
	this->rowIndex = 1;
	this->tokenType = 0;
	this->lexemLength = 0;

	int i = 0;
	while (i < 512) {
		this->internBuffer[i] = '\0';
		i++;
	}
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
	delete token;
}

void Scanner::getNextToken() {
    //End of File Schaltvariable
    bool eof = false;

    this->currentState = 0;
    char currentChar = ' ';

    //@todo entfernen
    int i = 0;

    //Hauptschleife solange das Ende der Datei nicht erreicht ist
	while(eof == false){
		//@todo entfernen
		i++;

		if(currentChar == '\0'){
			eof = true;
			break;
		} else {
			//cout << " -----> C:" << currentChar << " S:" << this->currentState << endl;

			switch (this->currentState) {
			case Automat::INIT:
				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;

				//Immer bei neuem Zeichen Col Count erhöhen
				//this->incrementColCount();

				// Erhöhe ScannerIndex
				this->scannerIndex++;
				break;

			case Automat::TOKEN:
				this->generateToken(this->tokenType);
				this->currentState = Automat::INIT;
				this->clearInternBuffer();

				this->colIndex += this->lexemLength;
				this->lexemLength = 1;
				break;

			case Automat::ERROR:
				break;

			case Automat::BLANK:
				this->scannerIndex--;
				this->internBuffer[scannerIndex] = '\0';

				this->tokenType = Token::TT_BLANK;

				this->currentState = Automat::INIT;
				break;

			case Automat::LINE_BREAK:
				this->colIndex = 0;
				this->rowIndex++;
				break;

			case Automat::TAB:
				this->lexemLength = 4;
				break;

			case Automat::INTEGER:
				this->lexemLength++;

				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(currentChar) != Automat::INTEGER) {
					this->currentState = 1;
					this->buffer->dekrementBufferPointer();
					this->scannerIndex--;
					this->tokenType = Token::TT_INTEGER;
				}
				break;

			case Automat::IDENTIFIER:
				this->lexemLength++;

				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(currentChar) != Automat::IDENTIFIER) {
					this->currentState = Automat::TOKEN;
					this->buffer->dekrementBufferPointer();
					this->scannerIndex--;
					this->tokenType = Token::TT_IDENTIFIER;
				}
				break;

			case Automat::IF_1:
				this->lexemLength = 1;

				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;
				break;

			case Automat::IF:
				this->lexemLength = 2;

				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(currentChar) < Automat::INTEGER) {
					this->currentState = Automat::TOKEN;
					this->buffer->dekrementBufferPointer();
					this->scannerIndex--;
					this->tokenType = Token::TT_IF;
				}
				break;

			case Automat::WHILE_1:
				this->lexemLength = 1;

				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;

				cout << this->setCurrentState(currentChar) << " as " << endl;
				if (this->setCurrentState(currentChar) != Automat::WHILE_2) {
					this->tokenType = Token::TT_IDENTIFIER;
					this->currentState = Automat::WHILE_2;
				}
				break;

			case Automat::WHILE_2:
				this->lexemLength = 2;

				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(currentChar) != Automat::WHILE_3) {
					this->tokenType = Token::TT_IDENTIFIER;
				}

				break;

			case Automat::WHILE_3:
				this->lexemLength = 3;

				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(currentChar) != Automat::WHILE_4) {
					this->tokenType = Token::TT_IDENTIFIER;
				}
				break;

			case Automat::WHILE_4:
				this->lexemLength = 4;

				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(currentChar) != Automat::WHILE) {
					this->tokenType = Token::TT_IDENTIFIER;
				}
				break;

			case Automat::WHILE:
				this->lexemLength = 5;

				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(currentChar) < Automat::INTEGER) {
					this->currentState = Automat::TOKEN;
					this->buffer->dekrementBufferPointer();
					this->scannerIndex--;
					this->tokenType = Token::TT_WHILE;
				}

				/*currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(currentChar) > Automat::TAB) {
					this->currentState = Automat::IDENTIFIER;
					//this->buffer->dekrementBufferPointer();
					//this->scannerIndex--;
					this->tokenType = Token::TT_IDENTIFIER;
				} else {
					this->currentState = Automat::TOKEN;
					this->buffer->dekrementBufferPointer();
					this->scannerIndex--;
					this->tokenType = Token::TT_IF;
				}*/
				break;

			case Automat::SIGN:
				this->colIndex++;
				this->lexemLength = 1;
				this->tokenType = Token::TT_SIGN;
				break;

			case Automat::COLON:
				this->lexemLength = 1;
				break;

			case Automat::STAR:
				this->lexemLength = 1;
				break;

			case Automat::EQUAL:
				this->lexemLength = 1;
				break;

			case Automat::AND_1:
				this->lexemLength = 1;
				break;

			case Automat::AND:
				this->lexemLength = 2;
				break;

			case Automat::COMMENT_1:
				this->lexemLength++;
				break;

			case Automat::COMMENT_2:
				this->lexemLength++;
				this->lexemLength++;
				break;

			case Automat::COLON_EQUAL:
				this->lexemLength = 2;
				break;

			case Automat::COMPLEX_1:
				this->lexemLength = 3;
				break;
			} // END SELECT
		} // END IF

		this->currentState = this->setCurrentState(currentChar);

		//if (i == 10) break;
	} // END WHILE
} // END METHODE

void Scanner::incrementColCount() {
	this->colIndex++;
}

uint16_t Scanner::setCurrentState(char currentChar) {
	// gebe Zeichen an Automat und erhalte aktuellen Status
	return this->automat->testChar(currentChar);
}


void Scanner::generateToken(uint16_t typ) {
	token = new Token(this->rowIndex, this->colIndex, typ, this->internBuffer);

	printToken();
	//writeOutput();

	/*if (typ == Token::TT_IDENTIFIER) {
		symTable->insert(this->internBuffer, typ);

 		for(int i = 0; i < this->scannerIndex; i++){
	        //cout << this->internBuffer[i];// << this->automat->getCols() << " - " << this->automat->getRows();
	    }
	}*/
}


void Scanner::printToken() {
	if (this->tokenType != Token::TT_BLANK) {
		cout << "Token: ";
		cout << "COLUMN: " << this->token->getCol() << " ROW: " << this->token->getRow() << " TYPE: " << this->token->getTokenType() << ":   ";
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
