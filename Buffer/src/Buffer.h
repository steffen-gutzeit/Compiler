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

public:
	Buffer(char *inPath, char *outPath);
	virtual ~Buffer();

	char getChar();
	void setBufferPointer(int x);
	void dekrementBufferPointer();
	void dekrementBufferPointer(int i);

	void addCharsToOutBuffer(char* text);

private:
	//Buffer
	char *firstBuffer;
	char *secondBuffer;

	char *firstBufferOut;

	int currentIndex;
	int currentBuffer;

	int currentIndexOut;
	int currentBufferOut;

	//Pfade
	char *inputPath;
	char *outputPath;

	//File Descriptoren
	int file_descriptor;
	int file_descriptor_out;


    int byte_count;
	int byte_count_out;


    char retValue;
    char retValueOut;

    int blockCount;

    int pmError;
    char eof;
    int freeSpace;


    void initBuffer();
    void initDescriptors();

    void closeFile();
    void closeFileOut();

    void loadFirstBuffer();
    void loadSecondBuffer();

    void writeBufferToFile();
};

#endif /* BUFFER_H_ */
