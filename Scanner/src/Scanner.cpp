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

    char currentChar = ' ';

    int forceState = 0;

    //Hauptschleife solange das Ende der Datei nicht erreicht ist
	while(eof == false){
		if(currentChar == '\0'){
			eof = true;

			this->generateToken(this->tokenType);
		} else {
			//cout << " -----> C:" << currentChar << " S:" << this->currentState << endl;

			switch (this->currentState) {
			case Automat::INIT:
				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;

				forceState = 0;

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

				forceState = 0;
				break;

			case Automat::ERROR:
				break;

			case Automat::BLANK:
				this->tokenType = Token::TT_BLANK;

				this->currentState = Automat::INIT;
				break;

			case Automat::LINE_BREAK:
				this->colIndex = 0;
				this->rowIndex++;

				this->tokenType = Token::TT_BLANK;

				this->currentState = Automat::INIT;
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
					// Durch das weitere manuelle Auslesen von Chars wird der
					// Folgezustand mit falschem Wert überschrieben, sofern
					// der normale Programmablauf durchgeführt wird.
					// Um dies zu verhindern, wird forceState=1 gesetzt.
					forceState = 1;
					this->currentState = Automat::TOKEN;
					this->scannerIndex--;
					this->internBuffer[this->scannerIndex] = '\0';

					this->buffer->dekrementBufferPointer();
					this->tokenType = Token::TT_INTEGER;
				}
				break;

			case Automat::IDENTIFIER:
				this->lexemLength++;

				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(currentChar) != Automat::IDENTIFIER) {
					// Durch das weitere manuelle Auslesen von Chars wird der
					// Folgezustand mit falschem Wert überschrieben, sofern
					// der normale Programmablauf durchgeführt wird.
					// Um dies zu verhindern, wird forceState=1 gesetzt.
					forceState = 1;
					this->currentState = Automat::TOKEN;
					this->scannerIndex--;
					this->internBuffer[this->scannerIndex] = '\0';

					this->buffer->dekrementBufferPointer();
					this->tokenType = Token::TT_IDENTIFIER;
				}
				break;

			case Automat::IF_1:
				//@todo!!!
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
					// Durch das weitere manuelle Auslesen von Chars wird der
					// Folgezustand mit falschem Wert überschrieben, sofern
					// der normale Programmablauf durchgeführt wird.
					// Um dies zu verhindern, wird forceState=1 gesetzt.
					forceState = 1;
					this->currentState = Automat::TOKEN;
					this->scannerIndex--;
					this->internBuffer[this->scannerIndex] = '\0';

					this->buffer->dekrementBufferPointer();
					this->tokenType = Token::TT_IF;
				}
				break;

			case Automat::WHILE_1:
				this->lexemLength++;

				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(currentChar) == Automat::WHILE_2) {
					forceState = 1;
					this->currentState = Automat::WHILE_2;
				} else {
					forceState = 1;
					this->currentState = Automat::IDENTIFIER;
				}
				break;

			case Automat::WHILE_2:
				this->lexemLength++;

				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(currentChar) == Automat::WHILE_3) {
					forceState = 1;
					this->currentState = Automat::WHILE_3;
				} else {
					forceState = 1;
					this->currentState = Automat::IDENTIFIER;
				}
				break;

			case Automat::WHILE_3:
				this->lexemLength++;

				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(currentChar) == Automat::WHILE_4) {
					forceState = 1;
					this->currentState = Automat::WHILE_4;
				} else {
					forceState = 1;
					this->currentState = Automat::IDENTIFIER;
				}
				break;

			case Automat::WHILE_4:
				this->lexemLength++;

				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(currentChar) == Automat::WHILE) {
					forceState = 1;
					this->currentState = Automat::WHILE;
				} else {
					forceState = 1;
					this->currentState = Automat::IDENTIFIER;
				}
				break;

			case Automat::WHILE:
				this->lexemLength++;

				currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = currentChar;
				this->scannerIndex++;

				if ((this->setCurrentState(currentChar) >= Automat::BLANK &&
						this->setCurrentState(currentChar) <= Automat::TAB) ||
						this->setCurrentState(currentChar) == Automat::TOKEN ||
						this->setCurrentState(currentChar) == Automat::SIGN ||
						this->setCurrentState(currentChar) == Automat::COLON ||
						this->setCurrentState(currentChar) == Automat::EQUAL ||
						this->setCurrentState(currentChar) == Automat::AND_1 ||
						this->setCurrentState(currentChar) == Automat::AND ||
						this->setCurrentState(currentChar) == Automat::COMMENT_1 ||
						this->setCurrentState(currentChar) == Automat::COMMENT_2 ||
						this->setCurrentState(currentChar) == Automat::COLON_EQUAL ||
						this->setCurrentState(currentChar) == Automat::COMPLEX_1 ||
						this->setCurrentState(currentChar) == Automat::CHECK) {
					forceState = 1;
					this->currentState = Automat::TOKEN;
					this->scannerIndex--;
					this->internBuffer[this->scannerIndex] = '\0';

					this->buffer->dekrementBufferPointer();
					this->tokenType = Token::TT_WHILE;
				} else {
					forceState = 1;
					this->currentState = Automat::IDENTIFIER;

					this->scannerIndex--;
					this->internBuffer[this->scannerIndex] = '\0';

					this->buffer->dekrementBufferPointer();
					this->tokenType = Token::TT_WHILE;
				}
				break;

			case Automat::SIGN:
				this->colIndex++;
				this->lexemLength = 1;
				this->tokenType = Token::TT_SIGN;
				break;

			case Automat::COLON:
				this->lexemLength = 1;
				this->tokenType = Token::TT_COLON;
				break;

			case Automat::STAR:
				this->lexemLength = 1;
				this->tokenType = Token::TT_STAR;
				break;

			case Automat::EQUAL:
				this->lexemLength = 1;
				this->tokenType = Token::TT_EQUAL;
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

		if (forceState == 0) {
			this->currentState = this->setCurrentState(currentChar);
		}
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
	this->token = new Token(this->rowIndex, this->colIndex, typ, this->internBuffer);

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
