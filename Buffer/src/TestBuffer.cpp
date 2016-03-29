#include "Buffer.h"

#include<stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {

	Buffer*  buffer;

	const char *path = "../../test.dat";

	buffer = new Buffer(path);

	char temp = '0';
    int i = 0;

    //Normaler Test
	while (temp != '\0'){
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

	//Teste dekrement




 /*   //Gebe kompletten Buffer aus
    for (int i = 0; i<6 ; i++){
        char tempSign = buffer->getChar();

    cout << tempSign << endl;
    }

    //teste pointer verändern

    buffer->setBufferPointer(-3);

    //Letzten 3 Zeichen erneut ausgeben
    for (int i = 0; i<3 ; i++){
        char tempSign = buffer->getChar();

    cout << tempSign << endl;
    }
*/
    return 0;

}
