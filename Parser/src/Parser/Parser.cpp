#include "Parser.h"

Parser::Parser(Scanner *scanner, char *tempin, char *out2)
{
	this->scanner = scanner;
	this->token = scanner->getCurrentToken();
	parseTree = new ParseTree(scanner, tempin, out2);
}


void Parser::syntaxError(uint16_t expected[], int expectedCount, Token *t) {
	cerr << "Syntax Error: Expected Token #"<< expected[0];
	for (int i = 1; i < expectedCount; i++) {
		if (i == expectedCount - 1) std::cerr << " or '"; else std::cerr << ", '";
		std::cerr << this->token->getTokenType(expected[i]) << "'";
	}
	std::cerr << " at line " << t->getRow() << ", column " << t->getCol() << " instead of '" << t->getTokenType() << "'." << std::endl;
}

void Parser::syntaxError(uint16_t expected, Token *t)
{
	uint16_t tokens[] = {expected};
	this->syntaxError(tokens, 1, t);
}

uint16_t Parser::processFile()
{
	std::cout << "parsing ..." << std::endl << " " << std::endl;

	Token *myCommand[MAX_POSSIBLE_TOKENS] = {};
	Token *t;
	uint16_t tokenCount = 0;
	uint16_t tokenParsed;

	for (int i = 0; i < MAX_POSSIBLE_TOKENS; i++) {
		char test[] = " ";
		myCommand[i] = new Token( 0, 0, token->TT_ERROR, test);
	}

	// Token stehen hier zur Verfügung, keine Nacharbeit mehr nötig
//	int i = 0;
	while ((t = scanner->getNextToken())) {
		if((t->getTokenTypeInt() != Token::TT_BLANK) && (t->getTokenTypeInt() != Token::TT_DUMMY)){
			myCommand[tokenCount++] = t;
			//cout << "Speichere Token" << endl;
		}
//		cout << i++ << " " << "a: " << t->getLexem() <<
//				"\tb: " << t->getTokenType() <<
//				"\tc: " << t->getTokenTypeInt() <<
//				endl;
	}

	//printf("Ausgabe Symboltabelle.\n");

		//scanner->printSymbtable();

	//printf("Ende Ausgabe Symboltabelle.\n");

	std::cout << "syntax checking ..." << std::endl;

	tokenParsed = PROG(parseTree->getRootNode(), myCommand, 0, tokenCount);

	if (tokenCount == tokenParsed) {
		std::cout << "syntax checking done" << std::endl;
	} else {
		uint16_t tokens[] = {Token::TT_IDENTIFIER, Token::TT_WRITE, Token::TT_READ, Token::TT_BRACE_UPON, Token::TT_IF, Token::TT_WHILE};
		syntaxError(tokens, 6, myCommand[tokenParsed]);
	}
	
	parseTree->typeCheck();

	//std::cout << "Print XML ..." << std::endl;
	//parseTree->printXML();

	//std::cout << "Make Code ..." << std::endl;
	parseTree->makeCode();
	
	return 0;
}

uint16_t Parser::PROG(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount) {
	uint16_t where = startCount;
	Node *myNode = node->addChild(new Node(new NodeInfo(ParserConstant::NODE_PROG)));
	
	// DECLS
	where = DECLS(myNode, myCommand, where, tokenCount);
	
	// STATEMENTS
	where = STATEMENTS(myNode, myCommand, where, tokenCount);
	
	return where;
}

uint16_t Parser::DECLS(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount) {
	uint16_t where = startCount;
	Node *myNode = node->addChild(new Node(new NodeInfo(ParserConstant::NODE_DECLS)));
	
	switch (myCommand[where]->getTokenTypeInt()) {
			
		// int
		// TODO prüfen, ob Token::TT_INT richtig ist.
		case Token::TT_INT:
			// DECL
			where = DECL(myNode, myCommand, where, tokenCount);

			// ;
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_SEMICOLON)) syntaxError(Token::TT_SEMICOLON, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			// DECLS
			where = DECLS(myNode, myCommand, where, tokenCount);
			
			break;
			
		// €
		default:
			break;
	}

	return where;
}

uint16_t Parser::DECL(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount) {
	uint16_t where = startCount;
	Node *myNode = node->addChild(new Node(new NodeInfo(ParserConstant::NODE_DECL)));

	// int
	if ((myCommand[where]->getTokenTypeInt() != Token::TT_INT)) syntaxError(Token::TT_INT, myCommand[where]);
	myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
	where++;
	
	// ARRAY
	where = ARRAY(myNode, myCommand, where, tokenCount);

	// identifier
	if ((myCommand[where]->getTokenTypeInt() != Token::TT_IDENTIFIER)) syntaxError(Token::TT_IDENTIFIER, myCommand[where]);
//	myCommand[where]->setTypification(ParserConstant::intType);
//	cout << "[DECL] set Identifier: " << " col: " << myCommand[where]->getCol()  << " row: " << myCommand[where]->getRow()  << " lexem: " << myCommand[where]->getLexem() << " typification: " << myCommand[where]->getTypification() << endl;
	myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_IDENTIFIER, myCommand[where])));


	where++;
		
	return where;
}

uint16_t Parser::ARRAY(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount) {
	uint16_t where = startCount;
	Node *myNode = node->addChild(new Node(new NodeInfo(ParserConstant::NODE_ARRAY)));
	switch (myCommand[where]->getTokenTypeInt()) {
		
		// [
		case Token::TT_SQUARE_BRACKET_UPON:
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			// integer
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_INTEGER)) syntaxError(Token::TT_INTEGER, myCommand[where]);
//			myCommand[where]->setTypification(ParserConstant::intType);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_IDENTIFIER, myCommand[where])));

			where++;
	
			// ]
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_SQUARE_BRACKET_CLOSE)) syntaxError(Token::TT_SQUARE_BRACKET_CLOSE, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			break;

		// €
		default:
			break;
	}
	
	return where;
}

uint16_t Parser::STATEMENTS(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount) {
	uint16_t where = startCount;
	Node *myNode = node->addChild(new Node(new NodeInfo(ParserConstant::NODE_STATEMENTS)));
	
	switch (myCommand[where]->getTokenTypeInt()) {
		
		// identifier, write, read, {, if, while
		case Token::TT_IDENTIFIER:
		case Token::TT_WRITE:
		case Token::TT_READ:
		case Token::TT_BRACE_UPON:
		case Token::TT_IF:
		case Token::TT_WHILE:
			
			// STATEMENT
			where = STATEMENT(myNode, myCommand, where, tokenCount);

			// ;
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_SEMICOLON)) syntaxError(Token::TT_SEMICOLON, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;

			// STATEMENTS
			where = STATEMENTS(myNode, myCommand, where, tokenCount);

			break;
			
		// €
		default:
			break;
	}

	return where;
}

uint16_t Parser::STATEMENT(Node * node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount) {
	uint16_t where = startCount;
	Node *myNode = node->addChild(new Node(new NodeInfo(ParserConstant::NODE_STATEMENT)));

	switch (myCommand[where]->getTokenTypeInt()) {
			
		// identifier
		case Token::TT_IDENTIFIER:
//			myCommand[where]->setTypification(ParserConstant::intType);
//			cout << "[STATEMENT] set Identifier: " << " col: " << myCommand[where]->getCol()  << " row: " << myCommand[where]->getRow()  << " lexem: " << myCommand[where]->getLexem() << "t ypification: " << myCommand[where]->getTypification() << endl;
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_IDENTIFIER, myCommand[where])));
			where++;

			// INDEX
			where = INDEX(myNode, myCommand, where, tokenCount);

			// :=
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_COLON_EQUAL)) syntaxError(Token::TT_COLON_EQUAL, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;

			// EXP
			where = EXP(myNode, myCommand, where, tokenCount);

			break;
			
		// write
		case Token::TT_WRITE:
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			// (
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_BRACKET_UPON)) syntaxError(Token::TT_BRACKET_UPON, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			// EXP
			where = EXP(myNode, myCommand, where, tokenCount);
			
			// )
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_BRACKET_CLOSE)) syntaxError(Token::TT_BRACKET_CLOSE, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;

			break;
		
		// read
		case Token::TT_READ:
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			// (
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_BRACKET_UPON)) syntaxError(Token::TT_BRACKET_UPON, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			// identifier
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_IDENTIFIER)) syntaxError(Token::TT_IDENTIFIER, myCommand[where]);
//			myCommand[where]->setTypification(ParserConstant::intType);
//			cout << "[READ] set Identifier: " << " col: " << myCommand[where]->getCol()  << " row: " << myCommand[where]->getRow()  << " lexem: " << myCommand[where]->getLexem() << " typification: " << myCommand[where]->getTypification() << endl;
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_IDENTIFIER, myCommand[where])));
			where++;

			// INDEX
			where = INDEX(myNode, myCommand, where, tokenCount);
			
			// )
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_BRACKET_CLOSE)) syntaxError(Token::TT_BRACKET_CLOSE, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;

			break;

		// {
		case Token::TT_BRACE_UPON:
			// {
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			// STATEMENTS
			where = STATEMENTS(myNode, myCommand, where, tokenCount);
			
			// }
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_BRACE_CLOSE)) syntaxError(Token::TT_BRACE_CLOSE, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			break;
			
		// if
		case Token::TT_IF:
			// if
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			// (
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_BRACKET_UPON)) syntaxError(Token::TT_BRACKET_UPON, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;

			// EXP
			where = EXP(myNode, myCommand, where, tokenCount);
			
			// )
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_BRACKET_CLOSE)) syntaxError(Token::TT_BRACKET_CLOSE, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			// STATEMENT
			where = STATEMENT(myNode, myCommand, where, tokenCount);

			// else
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_ELSE)) syntaxError(Token::TT_ELSE, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;

			// STATEMENT
			where = STATEMENT(myNode, myCommand, where, tokenCount);
			
			break;
			
		// while
		case Token::TT_WHILE:
			// while
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			// (
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_BRACKET_UPON)) syntaxError(Token::TT_BRACKET_UPON, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;

			// EXP
			where = EXP(myNode, myCommand, where, tokenCount);
			
			// )
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_BRACKET_CLOSE)) syntaxError(Token::TT_BRACKET_CLOSE, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;

			// STATEMENT
			where = STATEMENT(myNode, myCommand, where, tokenCount);
			
			break;
			
		default:
			uint16_t tokens[] = {Token::TT_IDENTIFIER, Token::TT_WRITE, Token::TT_READ, Token::TT_BRACE_UPON, Token::TT_IF, Token::TT_WHILE};
			syntaxError(tokens, 6, myCommand[where]);
	}
			
	return where;
}

uint16_t Parser::EXP(Node * node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount) {
	uint16_t where = startCount;
	Node *myNode = node->addChild(new Node(new NodeInfo(ParserConstant::NODE_EXP)));

	// EXP2
	where = EXP2(myNode, myCommand, where, tokenCount);

	// OP_EXP
	where = OP_EXP(myNode, myCommand, where, tokenCount);

	return where;
}

uint16_t Parser::EXP2(Node * node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount) {
	uint16_t where = startCount;
	Node *myNode = node->addChild(new Node(new NodeInfo(ParserConstant::NODE_EXP2)));

	switch (myCommand[where]->getTokenTypeInt()) {
		
		// (
		case Token::TT_BRACKET_UPON:
			// (
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			// EXP
			where = EXP(myNode, myCommand, where, tokenCount);

			// )
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_BRACKET_CLOSE)) syntaxError(Token::TT_BRACKET_CLOSE, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			break;
			
		// identifier
		case Token::TT_IDENTIFIER:
			// identifier
//			myCommand[where]->setTypification(ParserConstant::intType);
//			cout << "[EXP2 TT_IDENTIFIER] set Identifier: " << " col: " << myCommand[where]->getCol()  << " row: " << myCommand[where]->getRow()  << " lexem: " << myCommand[where]->getLexem() << " typification: " << myCommand[where]->getTypification() << endl;
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_IDENTIFIER, myCommand[where])));
			where++;
			
			// INDEX
			where = INDEX(myNode, myCommand, where, tokenCount);
			
			break;
			
		// integer
		// TODO PRÜFEN!!!! WENN NICHT FUNKTIONIERT, DANN TT_INT
		case Token::TT_INTEGER:
			// integer
//			myCommand[where]->setTypification(ParserConstant::intType);
//			cout << "[EXP2 TT_INTEGER] set Identifier: " << " col: " << myCommand[where]->getCol()  << " row: " << myCommand[where]->getRow()  << " lexem: " << myCommand[where]->getLexem() << " typification: " << myCommand[where]->getTypification() << endl;
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_IDENTIFIER, myCommand[where])));
			where++;
			
			break;
			
		// -
		case Token::TT_MINUS:
			// -
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			// EXP2
			where = EXP2(myNode, myCommand, where, tokenCount);
			
			break;
			
		// !
		case Token::TT_EXCLAMATION_MARK:
			// !
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			// EXP2
			where = EXP2(myNode, myCommand, where, tokenCount);
			
			break;
			
		default:
			uint16_t tokens[] = {Token::TT_BRACKET_UPON, Token::TT_IDENTIFIER, Token::TT_INTEGER, Token::TT_MINUS, Token::TT_EXCLAMATION_MARK};
			syntaxError(tokens, 5, myCommand[where]);
	}

	return where;
}

uint16_t Parser::INDEX(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount) {
	uint16_t where = startCount;
	Node *myNode = node->addChild(new Node(new NodeInfo(ParserConstant::NODE_INDEX)));
	
	switch (myCommand[where]->getTokenTypeInt()) {
			
		// [
		case Token::TT_SQUARE_BRACKET_UPON:
			// [
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;
			
			// EXP
			where = EXP(myNode, myCommand, where, tokenCount);
			
			// ]
			if ((myCommand[where]->getTokenTypeInt() != Token::TT_SQUARE_BRACKET_CLOSE)) syntaxError(Token::TT_SQUARE_BRACKET_CLOSE, myCommand[where]);
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;

			break;
			
		// €
		default:
			break;
	}
	
	return where;
}

uint16_t Parser::OP_EXP(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount) {
	uint16_t where = startCount;
	Node *myNode = node->addChild(new Node(new NodeInfo(ParserConstant::NODE_OP_EXP)));
	
	switch (myCommand[where]->getTokenTypeInt()) {

		// +, -, *, :, <, >, =, =:=, &&
		case Token::TT_PLUS:
		case Token::TT_MINUS:
		case Token::TT_STAR:
		case Token::TT_COLON:
		case Token::TT_LESS:
		case Token::TT_MORE:
		case Token::TT_EQUAL:
		case Token::TT_MORE_COLON_MORE:
		case Token::TT_AND:
			where = OP(myNode, myCommand, where, tokenCount);

			// EXP
			where = EXP(myNode, myCommand, where, tokenCount);
			
			break;
			
		// €
		default:
			break;
	}
	
	return where;
}

uint16_t Parser::OP(Node *node, Token *myCommand[], uint16_t startCount, uint16_t tokenCount) {
	uint16_t where = startCount;
	Node *myNode = node->addChild(new Node(new NodeInfo(ParserConstant::NODE_OP)));
	
	switch (myCommand[where]->getTokenTypeInt()) {
		
	// +, -, *, :, <, >, =, =:=, &&
	case Token::TT_PLUS:
	case Token::TT_MINUS:
	case Token::TT_STAR:
	case Token::TT_COLON:
	case Token::TT_LESS:
	case Token::TT_MORE:
	case Token::TT_EQUAL:
	case Token::TT_MORE_COLON_MORE:
	case Token::TT_AND:
			myNode->addChild(new Node(new NodeInfo(ParserConstant::NODE_KEYWORD, myCommand[where])));
			where++;			
			break;
			
		default:
			uint16_t tokens[] = {Token::TT_PLUS, Token::TT_MINUS, Token::TT_STAR, Token::TT_COLON, Token::TT_LESS, Token::TT_MORE, Token::TT_EQUAL, Token::TT_MORE_COLON_MORE, Token::TT_AND};
			syntaxError(tokens, 9, myCommand[where]);
	}
	
	return where;
}
