/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "Scanner.h"

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;


Scanner::Scanner(char *inputFile, char *outputFile) {
	this->outputPath = outputFile;
    buffer = new Buffer(inputFile, outputFile);
    automat = new Automat();
    symTable = new Symtable();
	init();
}

Scanner::~Scanner() {
	delete automat;
	delete buffer;
	delete token;
	delete symTable;
}

/*Token*/
void Scanner::getNextToken() {
    //End of File Schaltvariable
    bool eof = false;

    //Hauptschleife solange das Ende der Datei nicht erreicht ist
	while(eof == false){

	char currentChar = this->buffer->getChar();

	if(currentChar == '\0'){
		eof = true;
	}else{

	//Hole Zeichen aus Buffer und schreibe es in internen Buffer
	this->internBuffer[this->scannerIndex] = currentChar;

    //gebe Zeichen an Automat
	this->currentState = this->automat->testChar(this->internBuffer[this->scannerIndex]);

    this->scannerIndex++;

    //Prüfe metaData
    if (scannerIndex == 1 && (this->currentState & TOKEN_BIT)) {
		// SS_01 - SS_03: +, - / ...
    	this->automat->init();
		//this->printToken();


    	switch(this->internBuffer[0]){
    	case '+': this->generateToken(Token::TT_PLUS);
    		break;
    	case '-': this->generateToken(Token::TT_MINUS);
    	    break;
    	case '(': this->generateToken(Token::TT_BRACKET_UPON);
    	    break;
    	case ')': this->generateToken(Token::TT_BRACE_CLOSE);
    	    break;
    	case '{': this->generateToken(Token::TT_BRACE_UPON);
    	    break;
    	case '}': this->generateToken(Token::TT_BRACE_CLOSE);
    	    break;
    	case '[': this->generateToken(Token::TT_SQUARE_BRACKET_UPON);
    	    break;
    	case ']': this->generateToken(Token::TT_SQUARE_BRACKET_CLOSE);
    	    break;
    	case '!': this->generateToken(Token::TT_EXCLAMATION_MARK);
    	    break;
    	case '&': this->generateToken(Token::TT_AND);
    	    break;
    	case ';': this->generateToken(Token::TT_SEMICOLON);
    	    break;
    	case '<': this->generateToken(Token::TT_LESS);
    	    break;
    	case '>': this->generateToken(Token::TT_MORE);
    	    break;
    	case '=': this->generateToken(Token::TT_EQUAL);
    	    break;
    	case '/': this->generateToken(Token::TT_SLASH);
    	    break;
    	case '*': this->generateToken(Token::TT_STAR);
    	    break;
    	}

		this->init();
		this->automat->incrementColCount();
    } else {
		if (this->currentState & TOKEN_BIT) {

			this->scannerIndex--;
			this->internBuffer[scannerIndex] = '\0';
			this->buffer->dekrementBufferPointer();
			this->automat->init();

			if (this->commentFlag == 0) {
				if (automat->characterType(this->internBuffer[0]) == Automat::CT_NUMERIC) {
					//INTEGER 0123456789
					this->generateToken(Token::TT_INTEGER);
				} else if (automat->characterType(this->internBuffer[0]) == Automat::CT_LETTER) {
					//IDENTIFIER dungeonKeeper0815
					this->generateToken(Token::TT_IDENTIFIER);
				} else {
					//Hier muss noch was abgefangen werden, <:> und < und :=
					//####### Hier läuft er rein, weis aber nicht wie man die einzelnen Zeichen erkennen kann #################
					if(automat->characterType(this->internBuffer[0]) == Automat::CT_SIGN_LESS){
						//kleiner
						this->generateToken(Token::TT_LESS);
					//}else if(automat->characterType(this->internBuffer[0]) == Automat::){
						//<:>
					//	this->generateToken(Token::TT_MORE_DOUBLE_LESS);
					}else{
						// := richtiger zustand
						this->generateToken(Token::TT_DOUBLE_EQUAL);
					}
				}
				//this->printToken();
			} else {
				// Alle Kommentartypen: /***/ /* dsgsda */
				this->commentFlag = 0;
			}

			this->init();
			this->automat->decrementColCount();

		} else if (this->currentState & ERROR_BIT){
			//Fehlerbehanldung
			this->automat->decrementColCount((this->currentState & COUNT_BITS) >> 6);
			this->scannerIndex -= ((this->currentState & COUNT_BITS) >> 6);
			this->buffer->dekrementBufferPointer((this->currentState & COUNT_BITS) >> 6);

			switch (this->currentState) {
			case 0x250:
				//Fehler bei : folgendes Zeichen
				//Nach ":" muss "=" folgen!
				this->automat->incrementColCount();
				this->printErrorChar();

				this->init();
				break;
			case 0x292:
				//Fehler bei <: folgendes Zeichen
				//Nach "<:" muss ">" folgen!
				this->automat->incrementColCount();
				this->generateToken(Token::TT_LESS);
				//this->printToken();
				this->init();
				break;
			case 0x215:
				//this->scannerIndex--;

				this->automat->incrementColCount();
				this->printErrorChar();

				this->init();
				break;
			}
			//this->printErrorChar();

			this->automat->init();

		} else if (this->currentState & BLANK_BIT) {
			//Whitespacebehandlung
			this->scannerIndex--;
			this->internBuffer[scannerIndex] = '\0';

			this->automat->incrementColCount();
		} else if (this->currentState & NEW_LINE_BIT) {
			//Linebreak-Behandlung

			this->scannerIndex--;

			this->internBuffer[scannerIndex] = '\0';

			this->init();

			this->automat->init();
			this->automat->incrementRowCount();
			this->automat->initColCount();
		} else if (this->currentState & COMMENT_BIT) {
			//Kommentar-Hilfsfall
			commentFlag = 1;
		} else {
			// Nur sammeln
			this->automat->incrementColCount();
		}
    }
  }
	}

	buffer->closeFileOut();
}

void Scanner::init(){
    //Buffer löschen
	int i = 0;
	while (this->internBuffer[i] != '\0') {
		this->internBuffer[i++] = '\0';
	}

	//Index zurücksetzen
    this->scannerIndex = 0;
    this->commentFlag = 0;
}

void Scanner::printToken() {
    cout << "Token: ";
	for(int i = 0; i < this->scannerIndex; i++){
        cout << this->internBuffer[i];// << this->automat->getCols() << " - " << this->automat->getRows();
    }
    cout << endl;
}

void Scanner::generateToken(int typ) {
	token = new Token(this->automat->getRows(), this->automat->getCols(), typ, this->internBuffer);

	//printToken();
	writeOutput();

	if (typ == Token::TT_IDENTIFIER) {
		symTable->insert(this->internBuffer, typ);

 		for(int i = 0; i < this->scannerIndex; i++){
	        //cout << this->internBuffer[i];// << this->automat->getCols() << " - " << this->automat->getRows();
	    }
	}
}

void Scanner::printErrorChar() {
	//cout << "Ungültiges Zeichen \t" << this->internBuffer[0] << "\tLine " << this->automat->getRows() <<
	//		" Column " << this->automat->getCols() << endl;
	printf("unbekanntes Token Zeile: %d Spalte: %d Symbol: %c | %d\n", this->automat->getRows(), this->automat->getCols() ,this->internBuffer[0], this->internBuffer[0]);
}

int Scanner::getTokenType(char *lexem) {
	return this->symTable->lookUp(lexem);
}

void Scanner::writeOutput(){
	//Baue temporären String für Ausgabebuffer
	char *tempString = (char*)" ";
	//Wichtig für die Konvertierung von int zu char*
	char bufferTemp[100];

	//TODO Der String zur Übergabe in den Buffer muss ich noch fertig machen, sonst passt es.

    //Abfrage auf Lexem, Value, Sign
	if(token->getTokenTypeInt() == Token::TT_IDENTIFIER){
		cout << "Token\t"<< token->getTokenType() << "\t Line: " << token->getRow() << "\t Column: " << token->getColumn() << "\tLexem " << token->getLexem()<< endl;
        //tempString = "Token \t" + token->getTokenType() + "\t Line: " + token->getRow() + "\t Column: " + token->getColumn() + "\tLexem " + token->getLexem() + "\n";
	}else if(token->getTokenTypeInt() == Token::TT_INTEGER){
		cout << "Token\t"<< token->getTokenType() << "\t Line: " << token->getRow() << "\t Column: " << token->getColumn() << "\tValue: " << this->charToInt()<< endl;
	}else{
		cout << "Token\t"<< token->getTokenType() << "\t Line: " << token->getRow() << "\t Column: " << token->getColumn() << endl;
	}

	//Token
	buffer->addCharsToOutBuffer((char*)"Token\t");
    //TokenTyp
	buffer->addCharsToOutBuffer((char*)token->getTokenType());

    //Zeile
    buffer->addCharsToOutBuffer((char*)"\t Line: ");
    //Konvertiert mittels sprintf das int in das Chararray
    sprintf(bufferTemp ,"%d",token->getRow());
    buffer->addCharsToOutBuffer(bufferTemp);

    //Spalte
    buffer->addCharsToOutBuffer((char*)"\t Column: ");
    //Konvertiert mittels sprintf das int in das Chararray
    sprintf(bufferTemp ,"%d",token->getColumn());
    buffer->addCharsToOutBuffer(bufferTemp);

    //Prüfe ob Value oder Lexem vorhanden
    if(token->getTokenTypeInt() == Token::TT_IDENTIFIER){

    	//Übergebe Bezeichnungstext an die Ausgabe
    	buffer->addCharsToOutBuffer((char*)"\tLexem ");

    	//Übergebe Lexem an die Ausgabe
    	buffer->addCharsToOutBuffer((char*)token->getLexem());

    	//Beende aktuelle Zeile
    	buffer->addCharsToOutBuffer((char*)"\n");

    }else if(token->getTokenTypeInt() == Token::TT_INTEGER){

    	//Übergebe Bezeichnungstext an die Ausgabe
    	buffer->addCharsToOutBuffer((char*)"\tValue: ");

    	//lade aktuellen Buffer in temporäreren String
    	tempString = this->internBuffer;

    	//Schneide die gewünschte Zahl mittels Terminal ab
    	tempString[this->scannerIndex] = '\0';

    	//Übergebe den nun korrekten String an die Ausgabe
    	buffer->addCharsToOutBuffer(tempString);

    	//Beende aktuelle Zeile
    	buffer->addCharsToOutBuffer((char*)"\n");

    }else{
    	//Erforderlich falls kein Value oder Lexem Token
    	buffer->addCharsToOutBuffer((char*)"\n");
    }


}

int Scanner::charToInt(){
	int num = 0;
	for(int i = 0; i < this->scannerIndex; i++){
		num=((this->internBuffer[i])-'0')+num*10;
    }
	return num;
}

/*char* Scanner::intToChar(int num){
	char letter = "0";
	for(int i = 0; i < num; i++){

	}

}*/
