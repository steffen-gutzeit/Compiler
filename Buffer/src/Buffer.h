/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <fstream>
#include <stdint.h>

using namespace std;

class Buffer {

//@todo
	//iostream ersetzen
	//eof ermitteln und an Scanner schicken
	//2. Buffer benutzen und übergänge möglich machen

public:
	Buffer(char *inPath, char *outPath);
	virtual ~Buffer();

	char getChar();
	void setBufferPointer(int x);
	void dekrementBufferPointer();
	void dekrementBufferPointer(unsigned int i);

	void addCharsToOutBuffer(char* text);

	void closeFileOut();


private:
	char *firstBuffer;
	char *secondBuffer;

	char *firstBufferOut;
	char *secondBufferOut;

	unsigned int currentIndex;
	unsigned int currentBuffer;

	unsigned int currentIndexOut;
	unsigned int currentBufferOut;

	char *inputPath;
	char *outputPath;

	int file_descriptor;
	int file_descriptor_out;

    int byte_count;
	int byte_count_out;

    char retValue;
    char retValueOut;

    int blockCount;


    void closeFile();

    void loadFirstBuffer();
    void loadSecondBuffer();
};

#endif /* BUFFER_H_ */
