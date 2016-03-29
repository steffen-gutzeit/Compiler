/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "Buffer.h"


#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


#define BUF_SIZE (512)

using namespace std;

Buffer::Buffer(char *inPath, char *outPath) {
	currentIndex = 0;
	currentBuffer = 1;

	this->currentIndexOut = 0;
	this->currentBufferOut = 1;

	//Initialisieren der privaten Variablen
	retValue = ' ';
	byte_count = 0;

	this->retValueOut = ' ';
	this->byte_count_out = 0;

	//Zaehler wie viele Blocksizes vollstaendig geschrieben wurden
	this->blockCount = 0;

	//Dateipfad �bergeben
	inputPath = inPath;
	this->outputPath = outPath;

    //�ffnet die �bergebene Datei
    //O_DIRECT sorgt daf�r, dass keine automatische Bufferverwaltung �bernommen wird
    //Daher muss mittels posix_Memalign der Bufferspeicher allokiert werden
    file_descriptor = open(inputPath, O_DIRECT);

    file_descriptor_out = open(outputPath, O_CREAT | O_TRUNC | O_WRONLY | O_DIRECT, S_IRWXU);

    //Pr�ft auf Fehler beim �ffnen der Input Datei
    if (file_descriptor == -1){
       perror ("Fehler beim Oeffnen der Input Datei\n");
       exit( errno);
    }

    //Pr�ft auf Fehler beim �ffnen der Output Datei
    if (file_descriptor_out == -1){
       perror ("Fehler beim Oeffnen der Output Datei\n");
       exit( errno);
    }

    //Input Buffer
    //Allokiere Speicher, muss ein Vielfaches der Blocksize sein
    //512 ist die Blocksize, BUF_SIZE muss ein vielfaches von der Blocksize sein
    posix_memalign((void**)&firstBuffer, 512, BUF_SIZE);
    posix_memalign((void**)&secondBuffer, 512, BUF_SIZE);

    //Output Buffer
    //Allokiere Speicher, muss ein Vielfaches der Blocksize sein
    //512 ist die Blocksize, BUF_SIZE muss ein vielfaches von der Blocksize sein
    posix_memalign((void**)&firstBufferOut, 512, BUF_SIZE);
    posix_memalign((void**)&secondBufferOut, 512, BUF_SIZE);

    //F�llt Inputbuffer 1
    this->loadFirstBuffer();

}

Buffer::~Buffer() {
	// TODO Auto-generated destructor stub
}

char Buffer::getChar() {

        if(currentBuffer == 1){
           //Aktionen Buffer 1
           if((this->firstBuffer[this->currentIndex] == '\0') & (this->currentIndex == 512)){
               //Wechsle Buffer und setze Index herab
               currentBuffer = 2;
               currentIndex = 0;
               //Lade Buffer
               loadSecondBuffer();
               //Ermitlle Wert
               retValue = this->secondBuffer[this->currentIndex++];
           } else
           if ((this->firstBuffer[this->currentIndex] == '\0') & (this->currentIndex < 512)){
               //EOF ist erreicht
               retValue = '\0';
               //Schliese Datei
               this->closeFile();

           }else{
               //Normale R�ckgabe
               retValue = this->firstBuffer[this->currentIndex++];
           }

        } else {
            //Aktionen Buffer 2
            if((this->secondBuffer[this->currentIndex] == '\0') & (this->currentIndex == 512)){
               //Wechsle Buffer und setze Index herab
               currentBuffer = 1;
               currentIndex = 0;
               //Lade Buffer
               loadFirstBuffer();
               //Ermitlle Wert
               retValue = this->firstBuffer[this->currentIndex++];
           } else
           if ((this->secondBuffer[this->currentIndex] == '\0') & (this->currentIndex < 512)){
               //EOF ist erreicht
               retValue = '\0';
               //Schliese Datei
               this->closeFile();

           }else{
               //Normale R�ckgabe
               retValue = this->secondBuffer[this->currentIndex];
           }

        }

    return retValue;
}







  /*  //Pr�fen ob n�chstes Element noch im Buffer ist
    if(((this->firstBuffer[this->currentIndex]) != '\0') & (this->currentBuffer == 1){

        retValue = this->firstBuffer[this->currentIndex++];

    } else
    if (((this->firstBuffer[this->currentIndex]) == '\0') & (this->currentBuffer == 1){
        //Buffer ist am Ende
        this->currentIndex = 0;
        this->currentBuffer = 2;
    }
	//Inkrement wird erst nach Zugriff erhoeht
    return retValue;
}*/

void Buffer::setBufferPointer(int x) {
	currentIndex += x;
}


//ToDo Falls im ersten Buffer mehr zur�ckgegangen wird als da ist
//und der zweite noch gar nicht initialisiert wurde --> Fehler ausgeben
void Buffer::dekrementBufferPointer(){
    //Pr�fen auf Bufferwechsel
    if(currentIndex > 0){
        currentIndex--;
    } else {
        //Wechsle Buffer
        if(currentBuffer == 1){
            currentBuffer = 2;
            currentIndex = 512 - 1;
        }else {
            currentBuffer = 1;
            currentIndex = 512 - 1;
        }
    }


}

void Buffer::dekrementBufferPointer(unsigned int i){
    //Pr�fen auf Bufferwechsel
    if(currentIndex > i ){
        currentIndex -= i;
    } else {
        //Wechsle Buffer
        if(currentBuffer == 1){
            currentBuffer = 2;
            currentIndex = 512 - 1;
        }else {
            currentBuffer = 1;
            currentIndex = 512 + currentIndex;
            currentIndex -=i;
        }

    }

}

//Schliest die Input Datei
void Buffer::closeFile(){
    close(file_descriptor);
}


void Buffer::loadFirstBuffer(){
    //read setzt den Zeiger innerhalb der Datei automatisch hoch
    //Es werden nur so viele Zeichen gelesen wie angegeben (512)
    //Sollten weniger Bytes eingelesen werden, wird der Rest automatisch mit NULL aufgef�llt
    byte_count = read(file_descriptor, firstBuffer, BUF_SIZE);

    //Pr�fe auf Fehler beim einlesen
    if (byte_count == -1){
       perror ("Fehler beim Lesen der Datei\n");
       exit( errno);
    }

    //Anzeichen f�r Ende des Buffers1
    firstBuffer[511] = '\0';
}

void Buffer::loadSecondBuffer(){
    //read setzt den Zeiger innerhalb der Datei automatisch hoch
    //Es werden nur so viele Zeichen gelesen wie angegeben (512)
    //Sollten weniger Bytes eingelesen werden, wird der Rest automatisch mit NULL aufgef�llt
    byte_count = read(file_descriptor, secondBuffer, BUF_SIZE);

    //Pr�fe auf Fehler beim einlesen
    if (byte_count == -1){
       perror ("Fehler beim Lesen der Datei\n");
       exit( errno);
    }

    //Anzeichen f�r Ende des Buffers2
    secondBuffer[511] = '\0';
}

//####################### Ausgabe #####################################

void Buffer::addCharsToOutBuffer(char* text){

	//Länge Text bestimmen
	int sizeOfText = 0;
    while(text[sizeOfText] != '\0'){
    	sizeOfText++;
    }
    //printf("String mit LAenge: %d", sizeOfText);


    //Prüfe freie Kapazität
    if((this->currentIndexOut + sizeOfText) <= BUF_SIZE){
    	//Fülle Buffer
    	for(int i = 0; i < sizeOfText; i++){
    		this->firstBufferOut[this->currentIndexOut] = text[i];
    		this->currentIndexOut++;
    	}


    	    //close(file_descriptor_out);
    }else{
        //Buffer füllen bis Limit
    	int tempIndex = 0;

    	//Buffer füllen bis BUF_SIZE erreicht
    	for(int i = 0; this->currentIndexOut <= BUF_SIZE; i++){
    		this->firstBufferOut[this->currentIndexOut] = text[i];
    		this->currentIndexOut++;
    		tempIndex = i;
    	}

    	//Buffer schreiben
    	this->byte_count_out = write(this->file_descriptor_out, firstBufferOut, BUF_SIZE);

    	//Pr�fe auf Fehler beim schreiben
    	 if (byte_count == -1){
    	    perror ("Fehler beim Schreiben der Datei\n");
    	    exit( errno);
    	 }

    	//Buffer löschen
        for(int i = 0; i < BUF_SIZE; i++){
        	this->firstBufferOut[i] = '\0';
        }

        //Bufferzeiger zurücksetzen
        this->currentIndexOut = 0;

        //BlockCount erhoehen
        this->blockCount++;


    	//Rest in Buffer laden
    	for(int i = tempIndex; i < sizeOfText; i++){
    	   this->firstBufferOut[this->currentIndexOut] = text[i];
    	   this->currentIndexOut++;
    	}
    }


}

//Schliest die Output Datei
void Buffer::closeFileOut(){
	//Prüfe auf Rest im Buffer
    if(this->currentIndexOut > 0){

    	//Buffer schreiben
    	this->byte_count_out = write(this->file_descriptor_out, firstBufferOut, BUF_SIZE);

    	//Pruefe auf Fehler beim schreiben
    	if (byte_count == -1){
    	   perror ("Fehler beim Schreiben der Datei\n");
    	   exit( errno);
    	   }
    }

    //Rest der Datei abschneiden mit ftruncate, ansonsten ist der Rest der Datei mit Nullen gefuellt
    ftruncate(this->file_descriptor_out, (this->blockCount * BUF_SIZE) + this->currentIndexOut);

	//Schliese Datei
    close(this->file_descriptor_out);
}





