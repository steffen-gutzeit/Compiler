#pragma once
#include "../../../Scanner/src/Scanner.h"
#include "../../../Token/src/Token.h"
#include "parserConst.h"
#include "../Node/Node.h"
#include "../NodeInfo/NodeInfo.h"
#include "../Tree/ParseTree.h"

class Parser
{
	
public:
	Parser(Scanner *myScanner);
	int processFile();
	Token token;
	
private:

	void syntaxError(uint16_t expected, Token *t);
	void syntaxError(uint16_t expected[], int expectedCount, Token *t);

	// implement grammar
	int PROG(Node *node, Token *myCommand[], uint8_t startCount, uint8_t tokenCount);
	int DECLS(Node *node, Token *myCommand[], uint8_t startCount, uint8_t tokenCount);
	int DECL(Node *node, Token *myCommand[], uint8_t startCount, uint8_t tokenCount);
	int ARRAY(Node *node, Token *myCommand[], uint8_t startCount, uint8_t tokenCount);
	int TYPE(Node *node, Token *myCommand[], uint8_t startCount, uint8_t tokenCount);
	int STATEMENTS(Node *node, Token *myCommand[], uint8_t startCount, uint8_t tokenCount);
	int STATEMENT(Node *node, Token *myCommand[], uint8_t startCount, uint8_t tokenCount);
	int EXP(Node *node, Token *myCommand[], uint8_t startCount, uint8_t tokenCount);
	int EXP2(Node *node, Token *myCommand[], uint8_t startCount, uint8_t tokenCount);
	int INDEX(Node *node, Token *myCommand[], uint8_t startCount, uint8_t tokenCount);
	int OP_EXP(Node *node, Token *myCommand[], uint8_t startCount, uint8_t tokenCount);
	int OP(Node *node, Token *myCommand[], uint8_t startCount, uint8_t tokenCount);
	
	// other things
	Scanner *scanner;
	ParseTree *parseTree;
	
};
