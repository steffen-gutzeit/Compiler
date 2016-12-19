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
	virtual ~Parser();
	uint16_t processFile();
	Token *token;
	
private:

	void syntaxError(uint16_t expected, Token *t);
	void syntaxError(uint16_t expected[], int expectedCount, Token *t);

	// implement grammar
	int PROG(Node *node, Token *myCommand[], int startCount, int tokenCount);
	int DECLS(Node *node, Token *myCommand[], int startCount, int tokenCount);
	int DECL(Node *node, Token *myCommand[], int startCount, int tokenCount);
	int ARRAY(Node *node, Token *myCommand[], int startCount, int tokenCount);
	int TYPE(Node *node, Token *myCommand[], int startCount, int tokenCount);
	int STATEMENTS(Node *node, Token *myCommand[], int startCount, int tokenCount);
	int STATEMENT(Node *node, Token *myCommand[], int startCount, int tokenCount);
	int EXP(Node *node, Token *myCommand[], int startCount, int tokenCount);
	int EXP2(Node *node, Token *myCommand[], int startCount, int tokenCount);
	int INDEX(Node *node, Token *myCommand[], int startCount, int tokenCount);
	int OP_EXP(Node *node, Token *myCommand[], int startCount, int tokenCount);
	int OP(Node *node, Token *myCommand[], int startCount, int tokenCount);
	
	// other things
	Scanner *scanner;
	ParseTree *parseTree;
	
};
