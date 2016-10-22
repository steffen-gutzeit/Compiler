#include "ParseTree.h"

ParseTree::ParseTree(Scanner *myScanner)
{
	rootNode = new Node(new NodeInfo(ParserConstant::NODE_ROOT));
	this->scanner = myScanner;
}

Node *ParseTree::getRootNode()
{
	return rootNode;
}

void ParseTree::printXML()
{
	rootNode->print();
	std::cout << std::endl;
}

Scanner *ParseTree::getScanner()
{
	return scanner;
}


Token *ParseTree::getSymTableEntryForIdentifier(uint16_t type, char *lexem) {

	Symtable *symtable = new Symtable();
	char *key = symtable->insert(lexem, type);

	if (!(scanner->getSymTable()->lookUp(lexem))) {
		std::cerr << "Internal Error: Identifier " << lexem << " not found in Symbol Table." << std::endl;
	}
	Token *t = new Token(0, 0, type, lexem);
	return t;
}


ParserConstant::Typification ParseTree::getType(Node *myNode) {
	if (myNode->getNodeInfo()->getNodeType() == ParserConstant::NODE_IDENTIFIER) {
		// lookup in SymTable
//		Token *t = getSymTableEntryForIdentifier(myNode->getNodeInfo()->getToken()->getTokenTypeInt(),
//													myNode->getNodeInfo()->getToken()->getLexem());
//		return t->getTypification();
		return myNode->getNodeInfo()->getToken()->getTypification();
	} else {
		// lookup in NodeInfo
		return myNode->getNodeInfo()->getToken()->getTypification();
	}
}

void ParseTree::setType(Node *myNode, ParserConstant::Typification myType)
{
//	cout << myNode->getNodeInfo()->get
	if (myNode->getNodeInfo()->getNodeType() == ParserConstant::NODE_IDENTIFIER) {
		// set in SymTable
		//getSymTableEntryForIdentifier(myNode->getNodeInfo()->getToken()->getLexem())->setTypification(myType);
		Token *t = getSymTableEntryForIdentifier(myNode->getNodeInfo()->getToken()->getTokenTypeInt(),
													myNode->getNodeInfo()->getToken()->getLexem());
		t->setTypification(myType);

		myNode->getNodeInfo()->getToken()->setTypification(myType);
//		myNode->getNodeInfo()->setTypification(myType);

	} else {
		// set in NodeInfo
//		cout << "[MyType] " << myType << endl;
		myNode->getNodeInfo()->setToken(new Token(0, 0, Token::TT_DUMMY, ""));
		myNode->getNodeInfo()->getToken()->setTypification(myType);
//		cout << "[GetType] " << getType(myNode) << endl;
	}
}

void ParseTree::typeCheck(Node *myNode)
{
	// start with root node
	if (myNode == NULL) myNode = rootNode;
		
	// typecheck the node itself
	switch (myNode->getNodeInfo()->getNodeType()) {

		case ParserConstant::NODE_ROOT:
			// PROG
			std::cout << "type checking ..." << std::endl;
			typeCheck(myNode->getChild(0));
			setType(myNode, ParserConstant::noType);
			std::cout << "type checking done" << std::endl;
			break;
			
		case ParserConstant::NODE_PROG:
			// DECLS STATEMENTS
			typeCheck(myNode->getChild(0));
			typeCheck(myNode->getChild(1));
			setType(myNode, ParserConstant::noType);
			break;

		case ParserConstant::NODE_DECLS:
			if (myNode->getChild(0) != NULL) {
				// DECL ; DECLS
				typeCheck(myNode->getChild(0));
				typeCheck(myNode->getChild(2));
				setType(myNode, ParserConstant::noType);
			} else {
				// €
				setType(myNode, ParserConstant::noType);
			}
			break;

		case ParserConstant::NODE_DECL:
			// int ARRAY identifier
			typeCheck(myNode->getChild(1));
			if (getType(myNode->getChild(2)) != ParserConstant::intType || getType(myNode->getChild(1)) == ParserConstant::errorType) {
				std::cerr << "--Typification Error: identifier '" << myNode->getChild(2)->getNodeInfo()->getToken()->getLexem() << "' is already defined";
				std::cerr << " at line " << myNode->getChild(2)->getNodeInfo()->getToken()->getRow() << ", column " << myNode->getChild(2)->getNodeInfo()->getToken()->getCol() << "." << std::endl;
				setType(myNode, ParserConstant::errorType);
			} else {
				setType(myNode, ParserConstant::noType);
				if (getType(myNode->getChild(0)) == ParserConstant::noType) {
					if (getType(myNode->getChild(1)) == ParserConstant::arrayType) {
						setType(myNode->getChild(2), ParserConstant::intArrayType);
					} else {
						setType(myNode->getChild(2), ParserConstant::intType);
					}
				}
			}
			break;

		case ParserConstant::NODE_ARRAY:
			if (myNode->getChildrenCount() > 0) {

				// [ integer ]
				if (myNode->getChild(1)->getNodeInfo()->getToken()->getIntegerValue() > 0) {
					setType(myNode, ParserConstant::arrayType);
				} else {
					setType(myNode, ParserConstant::errorType);
				}
			} else {
				// €
				setType(myNode, ParserConstant::noType);
			}
			break;
			
		case ParserConstant::NODE_TYPE:
			setType(myNode, ParserConstant::intType);
			break;

		case ParserConstant::NODE_STATEMENTS:
			if (myNode->getChildrenCount() > 0) {
				// STATEMENT ; STATEMENTS
				typeCheck(myNode->getChild(0));
				typeCheck(myNode->getChild(2));
				setType(myNode, ParserConstant::noType);
			} else {
				// €
				setType(myNode, ParserConstant::noType);
			}
			break;
		
		case ParserConstant::NODE_STATEMENT:
			if (myNode->getChild(0)->getNodeInfo()->getNodeType() == ParserConstant::NODE_IDENTIFIER) {
				// identifier INDEX := EXP
				typeCheck(myNode->getChild(3));
				typeCheck(myNode->getChild(1));
				if (getType(myNode->getChild(0)) == ParserConstant::noType) {
					std::cerr << "Typification Error: identifier '" << myNode->getChild(2)->getNodeInfo()->getToken()->getLexem() << "' is not defined";
					std::cerr << " at line " << myNode->getChild(0)->getNodeInfo()->getToken()->getRow() << ", column " << myNode->getChild(0)->getNodeInfo()->getToken()->getCol() << "." << std::endl;
					setType(myNode, ParserConstant::errorType);
				} else {
					if ( (getType(myNode->getChild(3)) == ParserConstant::intType) && (
						  ( (getType(myNode->getChild(0)) == ParserConstant::intType) && (getType(myNode->getChild(1)) == ParserConstant::noType))
						  || ((getType(myNode->getChild(0)) == ParserConstant::intArrayType) && (getType(myNode->getChild(1)) == ParserConstant::arrayType))) )
						 {
						setType(myNode, ParserConstant::noType);
					} else {
						std::cerr << "Typification Error: identifier '" << myNode->getChild(0)->getNodeInfo()->getToken()->getLexem() << "' of type '" << ParserConstant::typificationAsString(getType(myNode->getChild(0))) << "' is incompatible to type '" << ParserConstant::typificationAsString(getType(myNode->getChild(3))) << "'";
						std::cerr << " at line " << myNode->getChild(0)->getNodeInfo()->getToken()->getRow() << ", column " << myNode->getChild(0)->getNodeInfo()->getToken()->getCol() << "." << std::endl;
						setType(myNode, ParserConstant::errorType);
					}
						
				}
			} else {
				// NODE_KEYWORD
				switch (myNode->getChild(0)->getNodeInfo()->getToken()->getTokenTypeInt()) {
					case Token::TT_WRITE:
						// write ( EXP )
						typeCheck(myNode->getChild(2));
						setType(myNode, ParserConstant::noType);
						break;
					case Token::TT_READ:
						// read ( identifier INDEX )
						if (getType(myNode->getChild(2)) == ParserConstant::noType) {
							std::cerr << "Typification Error: identifier '" << myNode->getChild(2)->getNodeInfo()->getToken()->getLexem() << "' is not defined";
							std::cerr << " at line " << myNode->getChild(0)->getNodeInfo()->getToken()->getRow() << ", column " << myNode->getChild(0)->getNodeInfo()->getToken()->getCol() << "." << std::endl;
							setType(myNode, ParserConstant::errorType);
						} else {
							if (
									(
											(getType(myNode->getChild(2)) == ParserConstant::intType) &&
											(getType(myNode->getChild(3)) == ParserConstant::noType)
									)
									||
									(
											(getType(myNode->getChild(2)) == ParserConstant::intArrayType) &&
											(getType(myNode->getChild(3)) == ParserConstant::arrayType)
									)
								) {
								setType(myNode, ParserConstant::noType);
							} else {
								std::cerr << "Typification Error: identifier '" << myNode->getChild(2)->getNodeInfo()->getToken()->getLexem() << "' of type '" << ParserConstant::typificationAsString(getType(myNode->getChild(3))) << "' is incompatible to type '" << ParserConstant::typificationAsString(getType(myNode->getChild(3))) << "'";
								std::cerr << " at line " << myNode->getChild(2)->getNodeInfo()->getToken()->getRow() << ", column " << myNode->getChild(2)->getNodeInfo()->getToken()->getCol() << "." << std::endl;
								setType(myNode, ParserConstant::errorType);
							}
						}
						break;
					case Token::TT_BRACE_UPON:
						// { STATEMENTS }
						typeCheck(myNode->getChild(1));
						setType(myNode, ParserConstant::noType);
						break;
					case Token::TT_IF:
						// if ( EXP ) STATEMENT else STATEMENT
						typeCheck(myNode->getChild(2));
						typeCheck(myNode->getChild(4));
						typeCheck(myNode->getChild(6));
						cout << getType(myNode->getChild(2)) << endl;
						if (getType(myNode->getChild(2)) != ParserConstant::intType) {
							std::cerr << "--Typification Error: integer required as expression for 'if' statement";
							std::cerr << " at line " << myNode->getChild(0)->getNodeInfo()->getToken()->getRow() << ", column " << myNode->getChild(0)->getNodeInfo()->getToken()->getCol() << "." << std::endl;
							setType(myNode, ParserConstant::errorType);
						} else {
							setType(myNode, ParserConstant::noType);
						}
						break;
					case Token::TT_WHILE:
						// while ( EXP ) STATEMENT
						typeCheck(myNode->getChild(2));
						typeCheck(myNode->getChild(4));
						if (getType(myNode->getChild(2)) == ParserConstant::intType) {
							std::cerr << "Typification Error: integer required as expression for 'while' statement";
							std::cerr << " at line " << myNode->getChild(0)->getNodeInfo()->getToken()->getRow() << ", column " << myNode->getChild(0)->getNodeInfo()->getToken()->getCol() << "." << std::endl;
							setType(myNode, ParserConstant::errorType);
						} else {
							setType(myNode, ParserConstant::noType);
						}
						break;
					default:
						setType(myNode, ParserConstant::errorType);
						break;
				}
					
			}
			break;

		case ParserConstant::NODE_INDEX:
			if (myNode->getChildrenCount() > 0) {
				// [ EXP ]
				typeCheck(myNode->getChild(1));
				if (getType(myNode->getChild(1)) == ParserConstant::intType) {
					setType(myNode, ParserConstant::arrayType);
				} else {
					std::cerr << "Typification Error: integer required as index";
					std::cerr << " at line " << myNode->getChild(0)->getNodeInfo()->getToken()->getRow() << ", column " << myNode->getChild(0)->getNodeInfo()->getToken()->getCol() << "." << std::endl;
					setType(myNode, ParserConstant::errorType);
				}
			} else {
				// €
				setType(myNode, ParserConstant::noType);
			}
			break;
		
		case ParserConstant::NODE_EXP:
			// EXP2 OP_EXP
			typeCheck(myNode->getChild(0));
			typeCheck(myNode->getChild(1));
			if (getType(myNode->getChild(1)) == ParserConstant::noType) {
				setType(myNode, getType(myNode->getChild(0)));
			} else if (getType(myNode->getChild(0)) != getType(myNode->getChild(1))) {
				// incompatible types
				std::cerr << "Typification Error: incompatible types" << std::endl;
				//TODO
				//std::cerr << "Typification Error: expression '" << myNode->getChild(0)->getInfo()->getToken()->getLexem() << "' of type '" << parserConst::typificationAsString(getType(myNode->getChild(0))) << "' is incompatible to type '" << parserConst::typificationAsString(getType(myNode->getChild(3))) << "'";
				//std::cerr << " at line " << myNode->getChild(2)->getInfo()->getToken()->getLine() << ", column " << myNode->getChild(2)->getInfo()->getToken()->getColumn() << "." << std::endl;
				setType(myNode, ParserConstant::errorType);
			} else if ((getType(myNode->getChild(1)->getChild(0)) == ParserConstant::opLess) || (getType(myNode->getChild(1)->getChild(0)) == ParserConstant::opEqual)) {
				setType(myNode, ParserConstant::intType);
			} else {
				setType(myNode, getType(myNode->getChild(0)));
			}
			break;
			
		case ParserConstant::NODE_EXP2:
			switch (myNode->getChild(0)->getNodeInfo()->getToken()->getTokenTypeInt()) {
				case Token::TT_BRACKET_UPON:
					// ( EXP )
					typeCheck(myNode->getChild(1));
					setType(myNode, getType(myNode->getChild(1)));
					break;
				case Token::TT_IDENTIFIER:
					// identifier INDEX
					typeCheck(myNode->getChild(1));
					if (getType(myNode->getChild(0)) == ParserConstant::noType) {
						std::cerr << "Typification Error: identifier '" << myNode->getChild(0)->getNodeInfo()->getToken()->getLexem() << "' is not defined";
						std::cerr << " at line " << myNode->getChild(0)->getNodeInfo()->getToken()->getRow() << ", column " << myNode->getChild(0)->getNodeInfo()->getToken()->getCol() << "." << std::endl;
						setType(myNode, ParserConstant::errorType);
					} else if ((getType(myNode->getChild(0)) == ParserConstant::intType) && (getType(myNode->getChild(1)) == ParserConstant::noType)) {
						setType(myNode, getType(myNode->getChild(0)));
					} else if ( (getType(myNode->getChild(0)) == ParserConstant::intArrayType) && (getType(myNode->getChild(1)) == ParserConstant::arrayType) ) {
						setType(myNode, ParserConstant::intType);
					} else {
						std::cerr << "no primitive type" << std::endl;;
						//std::cerr << "Typification Error: identifier '" << myNode->getChild(2)->getInfo()->getToken()->getLexem() << "' of type '" << parserConst::typificationAsString(getType(myNode->getChild(3))) << "' is incompatible to type '" << parserConst::typificationAsString(getType(myNode->getChild(3))) << "'";
						//std::cerr << " at line " << myNode->getChild(2)->getInfo()->getToken()->getLine() << ", column " << myNode->getChild(2)->getInfo()->getToken()->getColumn() << "." << std::endl;
						//TODO
						setType(myNode, ParserConstant::errorType);
					}
					break;
				case Token::TT_INTEGER:
					// integer
					setType(myNode, ParserConstant::intType);
					break;
				case Token::TT_MINUS:
					// - EXP2
					typeCheck(myNode->getChild(1));
					setType(myNode, getType(myNode->getChild(1)));
					break;
				case Token::TT_EXCLAMATION_MARK:
					// ! EXP2
					typeCheck(myNode->getChild(1));
					if (getType(myNode->getChild(1)) != ParserConstant::intType) {
						std::cerr << "'!' operator requires integer" << std::endl;
						//TODO
						//std::cerr << "Typification Error: expression '" << myNode->getChild(0)->getInfo()->getToken()->getLexem() << "' of type '" << parserConst::typificationAsString(getType(myNode->getChild(0))) << "' is incompatible to type '" << parserConst::typificationAsString(getType(myNode->getChild(3))) << "'";
						//std::cerr << " at line " << myNode->getChild(2)->getInfo()->getToken()->getLine() << ", column " << myNode->getChild(2)->getInfo()->getToken()->getColumn() << "." << std::endl;
						setType(myNode, ParserConstant::errorType);
					} else {
						setType(myNode, getType(myNode->getChild(1)));
					}
					break;
			}

			break;

		case ParserConstant::NODE_OP_EXP:
			if (myNode->getChildrenCount() > 0) {
				// OP EXP
				typeCheck(myNode->getChild(0));
				typeCheck(myNode->getChild(1));
				setType(myNode, myNode->getChild(1)->getNodeInfo()->getToken()->getTypification());
			} else {
				// €
				setType(myNode, ParserConstant::noType);
			}
			break;
			
		case ParserConstant::NODE_OP:
			// OP
			switch (myNode->getChild(0)->getNodeInfo()->getToken()->getTokenTypeInt()) {
				case Token::TT_PLUS:
					setType(myNode, ParserConstant::opPlus);
					break;
				case Token::TT_MINUS:
					setType(myNode, ParserConstant::opMinus);
					break;
				case Token::TT_STAR:
					setType(myNode, ParserConstant::opMult);
					break;
				case Token::TT_COLON:
					setType(myNode, ParserConstant::opDiv);
					break;
				case Token::TT_LESS:
					setType(myNode, ParserConstant::opLess);
					break;
				// TODO TT_ASSIGN?!?
				case Token::TT_COLON_EQUAL:
					setType(myNode, ParserConstant::opEqual);
					break;
				case Token::TT_AND:
					setType(myNode, ParserConstant::opAnd);
					break;
				default:
					setType(myNode, ParserConstant::errorType);
					break;
			}
			break;

		
		case ParserConstant::NODE_UNKNOWN:
		case ParserConstant::NODE_ERROR:
		case ParserConstant::NODE_EMPTY:
		case ParserConstant::NODE_IDENTIFIER:
		case ParserConstant::NODE_KEYWORD:
		default:
			break;
	}
}


void ParseTree::makeCode(Node *myNode)
{
	Marker *m1;
	Marker *m2;
	
	// start with root node
	if (myNode == NULL) myNode = rootNode;
		
	// typecheck the node itself
	switch (myNode->getNodeInfo()->getNodeType()) {

		case ParserConstant::NODE_ROOT:
			// PROG
			std::cout << "code generation ..." << std::endl;
			makeCode(myNode->getChild(0));
			std::cout << "code generation done" << std::endl;
			break;
			
		case ParserConstant::NODE_PROG:
			// DECLS STATEMENTS
			makeCode(myNode->getChild(0));
			makeCode(myNode->getChild(1));
			std::cout << "STP" << std::endl;
			break;

		case ParserConstant::NODE_DECLS:
			if (myNode->getChild(0) != NULL) {
				// DECL ; DECLS
				makeCode(myNode->getChild(0));
				makeCode(myNode->getChild(2));
			} else {
				// €
			}
			break;

		case ParserConstant::NODE_DECL:
			// TYPE ARRAY identifier
			std::cout << "DS $" << myNode->getChild(2)->getNodeInfo()->getToken()->getLexem() << " ";
			makeCode(myNode->getChild(1));
			break;

		case ParserConstant::NODE_ARRAY:
			if (myNode->getChildrenCount() > 0) {
				// [ integer ]
				std::cout << myNode->getChild(1)->getNodeInfo()->getToken()->getIntegerValue() << std::endl;
			} else {
				// €
				std::cout << "1" << std::endl;
			}
			break;
			
		case ParserConstant::NODE_TYPE:
			break;

		case ParserConstant::NODE_STATEMENTS:
			if (myNode->getChildrenCount() > 0) {
				// STATEMENT ; STATEMENTS
				makeCode(myNode->getChild(0));
				makeCode(myNode->getChild(2));
			} else {
				// €
				std::cout << "NOP" << std::endl;
			}
			break;
		
		case ParserConstant::NODE_STATEMENT:
			if (myNode->getChild(0)->getNodeInfo()->getNodeType() == ParserConstant::NODE_IDENTIFIER) {
				// identifier INDEX = EXP
				makeCode(myNode->getChild(3));
				std::cout << "LA $" << myNode->getChild(0)->getNodeInfo()->getToken()->getLexem() << std::endl;
				makeCode(myNode->getChild(1));
				std::cout << "STR" << std::endl;
			} else {
				// NODE_KEYWORD
				switch (myNode->getChild(0)->getNodeInfo()->getToken()->getTokenTypeInt()) {
					case Token::TT_WRITE:
						// write ( EXP )
						makeCode(myNode->getChild(2));
						std::cout << "PRI" << std::endl;
						break;
					case Token::TT_READ:
						// read ( identifier INDEX )
						std::cout << "REA" << std::endl;
						std::cout << "LA $" << myNode->getChild(2)->getNodeInfo()->getToken()->getLexem() << endl;
						makeCode(myNode->getChild(3));
						std::cout << "STR" << std::endl;
						break;
					case Token::TT_BRACE_UPON:
						// { STATEMENTS }
						makeCode(myNode->getChild(1));
						break;
					case Token::TT_IF:
						// if ( EXP ) STATEMENT else STATEMENT
						makeCode(myNode->getChild(2));
						m1 = new Marker();
						m2 = new Marker();
						std::cout << "JIN #" << m1->getName() << std::endl;
						makeCode(myNode->getChild(4));
						std::cout << "JMP #" << m2->getName() << std::endl;
						std::cout << "#" << m1->getName() << " NOP" << std::endl;
						makeCode(myNode->getChild(6));
						std::cout << "#" << m2->getName() << " NOP" << std::endl;
						break;
					case Token::TT_WHILE:
						// while ( EXP ) STATEMENT
						m1 = new Marker();
						m2 = new Marker();
						std::cout << "#" << m1->getName() << " NOP" << std::endl;
						makeCode(myNode->getChild(2));
						std::cout << "JIN #" << m2->getName() << std::endl;
						makeCode(myNode->getChild(4));
						std::cout << "JMP #" << m1->getName() << std::endl;
						std::cout << "#" << m2->getName() << " NOP" << std::endl;
						break;
					default:
						break;
				}
					
			}
			break;

		case ParserConstant::NODE_INDEX:
			if (myNode->getChildrenCount() > 0) {
				// [ EXP ]
				makeCode(myNode->getChild(1));
				std::cout << "ADD" << std::endl;
			} else {
				// €
			}
			break;
		
		case ParserConstant::NODE_EXP:
			// EXP2 OP_EXP
			makeCode(myNode->getChild(0));
			if (getType(myNode->getChild(1)) == ParserConstant::noType) break;
			makeCode(myNode->getChild(1));
			break;
			
		case ParserConstant::NODE_EXP2:
			switch (myNode->getChild(0)->getNodeInfo()->getToken()->getTokenTypeInt()) {
				case Token::TT_BRACKET_UPON:
					// ( EXP )
					makeCode(myNode->getChild(1));
					break;
				case Token::TT_IDENTIFIER:
					// identifier INDEX
					std::cout << "LA $" << myNode->getChild(0)->getNodeInfo()->getToken()->getLexem() << std::endl;
					makeCode(myNode->getChild(1));
					std::cout << "LV" << std::endl;
					break;
				case Token::TT_INTEGER:
					// integer
					std::cout << "LC " << myNode->getChild(0)->getNodeInfo()->getToken()->getIntegerValue() << std::endl;
					break;
				case Token::TT_MINUS:
					// - EXP2
					std::cout << "LC 0" << std::endl;
					makeCode(myNode->getChild(1));
					std::cout << "SUB" << std::endl;
					break;
				case Token::TT_EXCLAMATION_MARK:
					// ! EXP2
					makeCode(myNode->getChild(1));
					std::cout << "NOT" << std::endl;
					break;
			}

			break;

		case ParserConstant::NODE_OP_EXP:
			if (myNode->getChildrenCount() > 0) {
				// OP EXP
				makeCode(myNode->getChild(1));
				switch (getType(myNode->getChild(0))) {
					case ParserConstant::opPlus:
						std::cout << "ADD" << std::endl;
						break;
					case ParserConstant::opMinus:
						std::cout << "SUB" << std::endl;
						break;
					case ParserConstant::opMult:
						std::cout << "MUL" << std::endl;
						break;
					case ParserConstant::opDiv:
						std::cout << "DIV" << std::endl;
						break;
					case ParserConstant::opLess:
						std::cout << "LES" << std::endl;
						break;
					case ParserConstant::opEqual:
						std::cout << "EQ" << std::endl;
						break;
					case ParserConstant::opAnd:
						std::cout << "AND" << std::endl;
						break;
					case ParserConstant::opUnEqual:
						std::cout << "UNEQUAL?" << std::endl;
						break;
					default:
						std::cout << "EQU" << std::endl;
						break;
				}
			} else {
				// €
			}
			break;
			
		case ParserConstant::NODE_OP:
			// should never be reached
			break;

		
		case ParserConstant::NODE_UNKNOWN:
		case ParserConstant::NODE_ERROR:
		case ParserConstant::NODE_EMPTY:
		case ParserConstant::NODE_IDENTIFIER:
		case ParserConstant::NODE_KEYWORD:
		default:
			break;
	}
}

