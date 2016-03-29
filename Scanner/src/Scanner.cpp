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
	this->currentChar = ' ';
	this->forceState = 0;

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

void Scanner::buildIntegerOrIdentifier(uint16_t state, uint16_t tokenType) {
	this->lexemLength++;
	this->currentChar = this->buffer->getChar();
	this->internBuffer[this->scannerIndex] = this->currentChar;
	this->scannerIndex++;
	if (this->setCurrentState(this->currentChar) != state) {
		// Durch das weitere manuelle Auslesen von Chars wird der
		// Folgezustand mit falschem Wert überschrieben, sofern
		// der normale Programmablauf durchgeführt wird.
		// Um dies zu verhindern, wird forceState=1 gesetzt.
		this->forceState = 1;
		this->currentState = Automat::TOKEN;
		this->scannerIndex--;
		this->internBuffer[this->scannerIndex] = '\0';
		this->buffer->dekrementBufferPointer();
		this->tokenType = tokenType;
	}
}

void Scanner::forceTokenGeneration(uint16_t state, uint16_t tokenType) {
	// Durch das weitere manuelle Auslesen von Chars wird der
	// Folgezustand mit falschem Wert überschrieben, sofern
	// der normale Programmablauf durchgeführt wird.
	// Um dies zu verhindern, wird forceState=1 gesetzt.
	this->forceState = 1;
	this->currentState = state;
	this->scannerIndex--;
	this->internBuffer[this->scannerIndex] = '\0';
	this->buffer->dekrementBufferPointer();
	this->tokenType = tokenType;
}

void Scanner::throwSpecialToken(uint16_t tokenType) {
	// =:+
	this->currentChar = this->buffer->getChar();
	this->clearInternBuffer();
	this->internBuffer[0] = this->currentChar;
	this->tokenType = tokenType;
	this->scannerIndex = 1;
	this->generateToken(this->tokenType);
}

void Scanner::getNextToken() {
    //End of File Schaltvariable
    bool eof = false;

    this->currentChar = ' ';

    //Hauptschleife solange das Ende der Datei nicht erreicht ist
	while(eof == false){
		if(this->currentChar == '\0'){
			eof = true;

			this->generateToken(this->tokenType);
		} else {
			//cout << " -----> C:" << this->currentChar << " S:" << this->currentState << endl;

			switch (this->currentState) {
			case Automat::INIT:
				this->currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = this->currentChar;
				this->scannerIndex++;
				forceState = 0;
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
				//@todo
				// Fehlerfall einfaches &

				forceState = 1;
				this->currentState = Automat::TOKEN;
				this->scannerIndex--;
				this->internBuffer[this->scannerIndex] = '\0';

				this->buffer->dekrementBufferPointer();
				this->tokenType = Token::TT_ERROR;
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
				this->buildIntegerOrIdentifier(Automat::INTEGER, Token::TT_INTEGER);
				break;

			case Automat::IDENTIFIER:
				this->buildIntegerOrIdentifier(Automat::IDENTIFIER, Token::TT_IDENTIFIER);
				break;

			case Automat::IF_1:
				//@todo!!!
				this->lexemLength = 1;

				this->currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = this->currentChar;
				this->scannerIndex++;
				break;

			case Automat::IF:
				this->lexemLength = 2;

				this->currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = this->currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(this->currentChar) < Automat::INTEGER) {
					this->forceTokenGeneration(Automat::TOKEN, Token::TT_IF);
				}
				break;

			case Automat::WHILE_1:
				this->lexemLength++;

				this->currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = this->currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(this->currentChar) == Automat::WHILE_2) {
					forceState = 1;
					this->currentState = Automat::WHILE_2;
				} else {
					forceState = 1;
					this->currentState = Automat::IDENTIFIER;
				}
				break;

			case Automat::WHILE_2:
				this->lexemLength++;

				this->currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = this->currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(this->currentChar) == Automat::WHILE_3) {
					forceState = 1;
					this->currentState = Automat::WHILE_3;
				} else {
					forceState = 1;
					this->currentState = Automat::IDENTIFIER;
				}
				break;

			case Automat::WHILE_3:
				this->lexemLength++;

				this->currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = this->currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(this->currentChar) == Automat::WHILE_4) {
					forceState = 1;
					this->currentState = Automat::WHILE_4;
				} else {
					forceState = 1;
					this->currentState = Automat::IDENTIFIER;
				}
				break;

			case Automat::WHILE_4:
				this->lexemLength++;

				this->currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = this->currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(this->currentChar) == Automat::WHILE) {
					forceState = 1;
					this->currentState = Automat::WHILE;
				} else {
					forceState = 1;
					this->currentState = Automat::IDENTIFIER;
				}
				break;

			case Automat::WHILE:
				this->lexemLength++;

				this->currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = this->currentChar;
				this->scannerIndex++;

				if ((this->setCurrentState(this->currentChar) >= Automat::BLANK &&
						this->setCurrentState(this->currentChar) <= Automat::TAB) ||
						this->setCurrentState(this->currentChar) == Automat::TOKEN ||
						this->setCurrentState(this->currentChar) == Automat::SIGN ||
						this->setCurrentState(this->currentChar) == Automat::COLON ||
						this->setCurrentState(this->currentChar) == Automat::EQUAL ||
						this->setCurrentState(this->currentChar) == Automat::AND_1 ||
						this->setCurrentState(this->currentChar) == Automat::AND ||
						this->setCurrentState(this->currentChar) == Automat::COMMENT_1 ||
						this->setCurrentState(this->currentChar) == Automat::COMMENT_2 ||
						this->setCurrentState(this->currentChar) == Automat::COLON_EQUAL ||
						this->setCurrentState(this->currentChar) == Automat::COMPLEX_1 ||
						this->setCurrentState(this->currentChar) == Automat::CHECK) {
					this->forceTokenGeneration(Automat::TOKEN, Token::TT_WHILE);
				} else {
					this->forceTokenGeneration(Automat::IDENTIFIER, Token::TT_WHILE);
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

				this->lexemLength++;

				this->currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = this->currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(this->currentChar) == Automat::COMMENT_1) {
					forceState = 1;
					this->clearInternBuffer();
					this->scannerIndex = 0;
					this->currentState = Automat::COMMENT_1;
				} else if (this->currentChar == '=') {
				//} else if (this->setCurrentState(this->currentChar) == Automat::COLON_EQUAL) {
					// @todo: If-Bedingung überdenken / fixen
					forceState = 1;
					this->currentState = Automat::COLON_EQUAL;
				} else {
					this->forceTokenGeneration(Automat::TOKEN, Token::TT_COLON);
				}
				break;

			case Automat::STAR:
				this->lexemLength = 1;
				this->tokenType = Token::TT_STAR;
				break;

			case Automat::EQUAL:
				/*this->lexemLength = 1;
				this->tokenType = Token::TT_EQUAL;*/

				this->tokenType = Token::TT_EQUAL;
				this->lexemLength++;

				this->currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = this->currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(this->currentChar) == Automat::COMPLEX_1) {
					forceState = 1;
					this->currentState = Automat::COMPLEX_1;
				} else {
					this->forceTokenGeneration(Automat::TOKEN, Token::TT_EQUAL);
				}

				break;

			case Automat::AND_1:
				this->lexemLength++;

				this->currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = this->currentChar;
				this->scannerIndex++;

				if (this->setCurrentState(this->currentChar) == Automat::AND) {
					forceState = 1;
					this->currentState = Automat::TOKEN;
					this->tokenType = Token::TT_AND;
				} else {
					forceState = 1;
					this->currentState = Automat::ERROR;
				}
				break;

			case Automat::AND:
				this->tokenType = Token::TT_AND;
				break;

			case Automat::COMMENT_1:
				this->lexemLength++;

				this->currentChar = this->buffer->getChar();
				//@todo Löschen
//				this->internBuffer[this->scannerIndex] = this->currentChar;
//				this->scannerIndex++;
				//@todo Löschen ENDE

				if (this->setCurrentState(this->currentChar) == Automat::COMMENT_2) {
					forceState = 1;
					this->currentState = Automat::COMMENT_2;
					this->tokenType = Token::TT_DUMMY;
				}
				break;

			case Automat::COMMENT_2:
				this->lexemLength++;

				this->currentChar = this->buffer->getChar();
				//@todo Löschen
//				this->internBuffer[this->scannerIndex] = this->currentChar;
//				this->scannerIndex++;
				//@todo Löschen ENDE

				if (this->setCurrentState(this->currentChar) == Automat::TOKEN) {
					forceState = 1;
					this->clearInternBuffer();
					this->scannerIndex = 0;

					this->currentState = Automat::TOKEN;
					this->tokenType = Token::TT_DUMMY;
				} else {
					forceState = 1;
					this->currentState = Automat::COMMENT_1;
				}
				break;

			case Automat::COLON_EQUAL:
				this->lexemLength = 2;
				forceState = 1;
				this->currentState = Automat::TOKEN;

				this->buffer->dekrementBufferPointer();
				this->tokenType = Token::TT_COLON_EQUAL;
				break;

			case Automat::COMPLEX_1:
				this->lexemLength = 3;

				this->currentChar = this->buffer->getChar();
				this->internBuffer[this->scannerIndex] = this->currentChar;
				this->scannerIndex++;

				//if (this->setCurrentState(this->currentChar) == Automat::EQUAL) {
				if (this->currentChar == '=') {
					forceState = 1;
					this->currentState = Automat::TOKEN;
					this->tokenType = Token::TT_MORE_COLON_MORE;
				} else {
					this->buffer->dekrementBufferPointer(3);
					forceState = 0;
				}
				break;

			case Automat::CHECK:
				// =:+
				this->throwSpecialToken(Token::TT_EQUAL);
				this->throwSpecialToken(Token::TT_COLON);
				//@todo: TokenType anpassen
				this->throwSpecialToken(Token::TT_DUMMY);
				break;
			} // END SELECT
		} // END IF

		if (forceState == 0) {
			this->currentState = this->setCurrentState(this->currentChar);
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
	if (this->internBuffer[0] != '\0') {
		this->token = new Token(this->rowIndex, this->colIndex, typ, this->internBuffer);
		printToken();
	}
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
