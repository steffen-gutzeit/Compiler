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
#include <malloc.h>

#include <iostream>


#define BUF_SIZE (512)

using namespace std;

Buffer::Buffer(char *inPath, char *outPath) {

	//Buffer In
	currentIndex = 0;
	currentBuffer = 1;

	retValue = ' ';
	byte_count = 0;

	//Buffer Out
	currentIndexOut = 0;
	currentBufferOut = 1;

	retValueOut = ' ';
	byte_count_out = 0;

	//Initialisiere Variablen
	pmError = 0;
	eof = '\0';
	freeSpace = 0;

	//Zaehler wie viele Blocksizes vollstaendig geschrieben wurden
	blockCount = 0;

	//File Discriptors
	file_descriptor = 0;
	file_descriptor_out = 0;

	//Dateipfad uebergeben
	inputPath = inPath;
	outputPath = outPath;

	//File Descriptor init
	initDescriptors();

    //Buffer init
    initBuffer();

    //Fuellt Inputbuffer 1
    loadFirstBuffer();

}

Buffer::~Buffer() {
	//Schreibe den restlichen Buffer
	char temp[1];
	temp[0] = '\0';

	addCharsToOutBuffer(temp);

	// Schliese descriptor und OutBuffer
	closeFileOut();

	//Notwendig um beim Parser Aufruf die Input Datei zu schliessen
	closeFile();
}

void Buffer::initDescriptors(){
	//oeffnet die uebergebene Datei
	//O_DIRECT sorgt dafuer, dass keine automatische Bufferverwaltung uebernommen wird
	//Daher muss mittels posix_Memalign der Bufferspeicher allokiert werden

	file_descriptor = open(inputPath, O_DIRECT);

	file_descriptor_out = open(outputPath, O_CREAT | O_TRUNC | O_WRONLY | O_DIRECT, S_IRWXU);

	//Prueft auf Fehler beim oeffnen der Input Datei
	if (file_descriptor == -1){
	   perror ("Fehler beim Oeffnen der Input Datei\n");
	   exit( errno);
	}

	//Prueft auf Fehler beim oeffnen der Output Datei
	if (file_descriptor_out == -1){
	   perror ("Fehler beim Oeffnen der Output Datei\n");
	   exit( errno);
	}
}

void Buffer::initBuffer(){
	//Allokiere Speicher, muss ein Vielfaches der Blocksize sein
	//512 ist die Blocksize, BUF_SIZE muss ein vielfaches von der Blocksize sein
	//Gibt 0 zurueck wenn keine Fehler auftraten

	//Erster In Buffer
	pmError = posix_memalign((void**)&firstBuffer, 512, BUF_SIZE);

	if (pmError != 0) {
		perror("posix_memalign");
		exit(EXIT_FAILURE);
	}

	//Zweiter In Buffer
	pmError = posix_memalign((void**)&secondBuffer, 512, BUF_SIZE);

	if (pmError != 0) {
		perror("posix_memalign");
		exit(EXIT_FAILURE);
	}

	//Erster Out Buffer
	pmError = posix_memalign((void**)&firstBufferOut, 512, BUF_SIZE);

	if (pmError != 0) {
		perror("posix_memalign");
		exit(EXIT_FAILURE);
	}
}

//####################### Eingabe #####################################

char Buffer::getChar() {

        if(currentBuffer == 1){

           //Aktionen Buffer 1
        	if((currentIndex == byte_count) && (currentIndex == 512)){
               //Wechsle Buffer und setze Index herab
               currentBuffer = 2;
               currentIndex = 0;

               //Lade Buffer
               loadSecondBuffer();

               //Ermitlle Wert
               retValue = secondBuffer[currentIndex++];

           } else
           if((currentIndex == byte_count) && (currentIndex < 512) && (currentIndex != 511)){ //Change wegen Unix / windows dateien
               //EOF ist erreicht
               retValue = '\0';

               //Schliese Datei
               //closeFile();

           }else{
               //Normale Rueckgabe
               retValue = firstBuffer[currentIndex++];

           }

        } else {
            //Aktionen Buffer 2
        	if((currentIndex == byte_count) && (currentIndex == 512)){
               //Wechsle Buffer und setze Index herab
               currentBuffer = 1;
               currentIndex = 0;

               //Lade Buffer
               loadFirstBuffer();

               //Ermitlle Wert
               retValue = firstBuffer[currentIndex++];

           } else
           if((currentIndex == byte_count) && (currentIndex < 512) && (currentIndex != 511)){ //Change wegen Unix / windows dateien vorher byte_count - 1
               //EOF ist erreicht
               retValue = '\0';
               //Schliese Datei
               //this->closeFile();

           }else{
               //Normale Rueckgabe
               retValue = secondBuffer[currentIndex++];
           }

        }

    return retValue;
}


void Buffer::loadFirstBuffer(){
    //read setzt den Zeiger innerhalb der Datei automatisch hoch
    //Es werden nur so viele Zeichen gelesen wie angegeben (512)
    //Sollten weniger Bytes eingelesen werden, wird der Rest automatisch mit NULL aufgefuellt
    byte_count = read(file_descriptor, firstBuffer, BUF_SIZE);

    //Pruefe auf Fehler beim einlesen
    if (byte_count == -1){
       perror ("Fehler beim Lesen der Datei\n");
       exit( errno);
    }

}

void Buffer::loadSecondBuffer(){
    //read setzt den Zeiger innerhalb der Datei automatisch hoch
    //Es werden nur so viele Zeichen gelesen wie angegeben (512)
    //Sollten weniger Bytes eingelesen werden, wird der Rest automatisch mit NULL aufgefuellt
    byte_count = read(file_descriptor, secondBuffer, BUF_SIZE);

    //Pruefe auf Fehler beim einlesen
    if (byte_count == -1){
       perror ("Fehler beim Lesen der Datei\n");
       exit( errno);
    }



}

//Schliest die Input Datei
void Buffer::closeFile(){
	//gebe Buffer frei

	if(firstBuffer){
		free((void**)firstBuffer);
	}

	if(secondBuffer){
		free((void**)secondBuffer);
	}

	if(file_descriptor){
		close(file_descriptor);
	}


    //Valgrind error messages, nur zum debuggen auskommentieren!
    //fclose( stdin );
    //fclose( stdout );
    //fclose( stderr );
}


//####################### Ausgabe #####################################

void Buffer::addCharsToOutBuffer(char* text){
	//Uebergebene Strings oder Zeichen müssen mit '/0' terminiert werden!

	//Pruefe ob Ende erreicht
	//Um Ende der auszugebenden Datei zu signalisieren eine '\0' an erster Stelle übergeben
	if(text[0] == '\0'){


		//Fuelle restlichen Buffer bis 512 auf
		for(int i=currentIndexOut; i<512;i++){
			firstBufferOut[i] = '\0';
		}

		//Schreibe Buffer
		writeBufferToFile();

		//Rest der Datei abschneiden mit ftruncate, ansonsten ist der Rest der Datei mit Nullen gefuellt
		int er = ftruncate(file_descriptor_out, ((blockCount - 1) * BUF_SIZE) + currentIndexOut);

		if(er > 0){
			cout << "Error beim Abschneiden der Datei" << endl;
		}

		//BufferOut und File Descriptor werden über den Dekonstruktor beendet

	}else{

		//Länge Text bestimmen
		int sizeOfText = 0;
		while(text[sizeOfText] != '\0'){
			sizeOfText++;
		}

		//Genug freie Kapazitaet im Buffer
		if((currentIndexOut + sizeOfText) <= BUF_SIZE){
			//Fülle Buffer
			for(int i = 0; i < sizeOfText; i++){
				firstBufferOut[currentIndexOut] = text[i];
				currentIndexOut++;
			}

			//Buffer schreiben falls voll
			if(currentIndexOut == 512){
				writeBufferToFile();
				currentIndexOut = 0;
			}


		//Nicht genug freie Kapazitaet im Buffer vorhanden
		}else{
			//Ermittle freien Platz im Buffer
			freeSpace = BUF_SIZE - currentIndexOut;

			//Fuelle Buffer bis voll
			for(int i = 0; i < freeSpace; i++){
				firstBufferOut[currentIndexOut] = text[i];
				currentIndexOut++;
			}

			//Schreibe Buffer
			writeBufferToFile();

			//Resette Buffer
			currentIndexOut = 0;

			//Schreibe Rest in Buffer
			for(int i = freeSpace; i < sizeOfText; i++){
				firstBufferOut[currentIndexOut] = text[i];
				currentIndexOut++;
			}


		}
	}

}


void Buffer::writeBufferToFile(){

	byte_count_out = write(file_descriptor_out, firstBufferOut, BUF_SIZE);

	//Pruefe auf Fehler beim schreiben
	 if (byte_count_out == -1){
		perror ("Fehler beim Schreiben der Datei\n");
		exit( errno);
	 }

	 //BlockCount erhoehen
	 blockCount++;


}

//Schliest die Output Datei
void Buffer::closeFileOut(){

    //gebe Buffer frei
    free((void**)firstBufferOut);

	//Schliese Datei
    close(file_descriptor_out);
}


//####################### Dekrementierungen #####################################



/*void Buffer::setBufferPointer(int x) {
	//Fehlerfaelle abfangen!
	currentIndex += x;
}*/


//ToDo Falls im ersten Buffer mehr zurueckgegangen wird als da ist
//und der zweite noch gar nicht initialisiert wurde --> Fehler ausgeben
void Buffer::dekrementBufferPointer(){
    //Pruefen auf Bufferwechsel
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

void Buffer::dekrementBufferPointer(int i){
    //Pr�fen auf Bufferwechsel
    if(currentIndex > i ){
        currentIndex -= i;
    } else {

    	for(int y = 0; i < y; y++){
    		dekrementBufferPointer();
    	}
        //Wechsle Buffer
        /*if(currentBuffer == 1){
            currentBuffer = 2;
            currentIndex = 512 - 1;
        }else {
            currentBuffer = 1;
            currentIndex = 512 + currentIndex;
            currentIndex -=i;
        }*/

    }

}
