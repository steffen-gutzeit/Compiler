#pragma once
#include <iostream>
#include "../Node/Node.h"
#include "../../../Scanner/src/Scanner.h"
#include "../../../Symtable/src/Symtable.h"
#include "../../../Buffer/src/Buffer.h"
#include "../Marker/Marker.h"
#include "../ParserConstant/ParserConstant.h"

class ParseTree {
public:
	ParseTree(Scanner *scanner, char *tempin, char *out2);
	virtual ~ParseTree();
	
	Node *getRootNode();
	
	Scanner *getScanner();
	
	void typeCheck(Node *myNode = NULL);
	

	void printIdentifierNotFound(char *lexem);
	void setType(Node *myNode, ParserConstant::Typification myType);
	ParserConstant::Typification getType(Node *myNode);

	Token *getSymTableEntryForIdentifier(Token* token);
	
	void makeCode(Node *myNode = NULL);

	void writeCode(char *command);

	
private:
	Node *rootNode;
	Scanner *scanner;
	Buffer *buffer;

	int sizeOfNumber(int digit);
	char *intToChar(int digit);
	char *intToChar2(uint32_t digit, int size, char result[]);

	void destroyTree(Node *node);

	char *result;
};
