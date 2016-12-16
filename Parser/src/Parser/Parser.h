#pragma once
#include "../../../Scanner/src/Scanner.h"
#include "../../../Token/src/Token.h"
#include "../Node/Node.h"
#include "../NodeInfo/NodeInfo.h"
#include "../ParserConstant/ParserConstant.h"
#include "../Tree/ParseTree.h"

class Parser
{
	
public:
	Parser(Scanner *scanner, char *tempin, char *out2);
	uint16_t processFile();
	Token *token;
	
private:

	void syntaxError(uint16_t expected, Token *t);
	void syntaxError(uint16_t expected[], int expectedCount, Token *t);

	// implement grammar
	uint16_t PROG(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount);
	uint16_t DECLS(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount);
	uint16_t DECL(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount);
	uint16_t ARRAY(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount);
	uint16_t TYPE(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount);
	uint16_t STATEMENTS(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount);
	uint16_t STATEMENT(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount);
	uint16_t EXP(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount);
	uint16_t EXP2(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount);
	uint16_t INDEX(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount);
	uint16_t OP_EXP(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount);
	uint16_t OP(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount);
	
	// other things
	Scanner *scanner;
	ParseTree *parseTree;
	
};
