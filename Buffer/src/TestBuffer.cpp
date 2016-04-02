#include "Buffer.h"

#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {

	//Initialisierung
	Buffer *buffer;

	char pathIn[] = "test.dat";
	char pathOut[] = "out.txt";

	char currentSign = '0';


	buffer = new Buffer(pathIn, pathOut);


	//char temp = '0';
    //int i = 0;

    //Normaler Test
	/*while (temp != '\0'){
       temp = buffer->getChar();
       //Teste dekrement
       if(i == 513){
           buffer->dekrementBufferPointer();
       }

       if(i == 515){
           buffer ->dekrementBufferPointer(4);
       }

	   cout << temp << endl;
	   i++;
	}
*/
	//Teste dekrement




    //Gebe bestimme Anzahl an zeichen des Buffers aus
    /*for (int i = 0; i<10 ; i++){
        char tempSign = buffer->getChar();

    cout << tempSign << endl;
    }*/

	//Gebe kompletten Buffer aus
    while(currentSign != '\0'){
    	currentSign = buffer->getChar();
    	//cout << currentSign << endl;
    	//char test[] = "eof1111111111111111111111111111111111111111111111111111111111111eof1111111111111111111111111111111111111111111111111111111111111eof1111111111111111111111111111111111111111111111111111111111111eof1111111111111111111111111111111111111111111111111111111111111eof1111111111111111111111111111111111111111111111111111111111111eof1111111111111111111111111111111111111111111111111111111111111eof1111111111111111111111111111111111111111111111111111111111111eof1111111111111111111111111111111111111111111111111111111111111";
    	char test[2];
		test[0] = currentSign;
		test[1] = 'j';
		test[2] = 'a';
		test[3] = 'v';
		test[4] = 'a';
    	test[5] = '\0';

    	if(test[0] == '\0'){
    		cout << "Endterminal erkannt" << endl;
    	}
    	//cout << currentSign << endl;
    	//cout << "schreibe in Buffer" << endl;
    	buffer->addCharsToOutBuffer(test);

    }
    //char test[2];
    //test[0] = '\0';
    //test[1] = '\0';
    //buffer->addCharsToOutBuffer(test);
    //char test[] = "lol";
    //buffer->addCharsToOutBuffer(test);
    //teste pointer veraendern

    //buffer->setBufferPointer(-3);

    //Letzten 3 Zeichen erneut ausgeben
    /*for (int i = 0; i<3 ; i++){
        char tempSign = buffer->getChar();

    cout << tempSign << endl;
    }*/

    delete buffer;

    return 0;

}
