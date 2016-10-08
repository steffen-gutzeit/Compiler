#pragma once
#include <iostream>
#include "../Node/Node.h"
#include "../../../Scanner/src/Scanner.h"
#include "../../../Symtable/src/Symtable.h"
#include "../Marker/Marker.h"
#include "../ParserConstant/ParserConstant.h"

class ParseTree {
public:
	ParseTree(Scanner *myScanner);
	
	Node *getRootNode();
	void printXML();
	
	Scanner *getScanner(); // needed if you want to use the scanner, p.ex. for viewing the symtable

	
	void typeCheck(Node *myNode = NULL);
	
	// helper functions that match getting and setting of typification for identifiers to the symtable

	void printIdentifierNotFound(char *lexem);
//	std::string identifier);
	void setType(Node *myNode, ParserConstant::Typification myType);
	ParserConstant::Typification getType(Node *myNode);

	
	void makeCode(Node *myNode = NULL);

	
private:
	Node *rootNode;
	Scanner *scanner;
};
