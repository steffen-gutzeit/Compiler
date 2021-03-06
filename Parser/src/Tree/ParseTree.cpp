#include "ParseTree.h"

#include <stdlib.h>
#include <stdio.h>

/*
 * Konstruktor
 */
ParseTree::ParseTree(Scanner *myScanner, char *tempin, char *out2) {
	rootNode = new Node(new NodeInfo(ParserConstant::NODE_ROOT));
	this->scanner = myScanner;

	//Erzeuge Buffer für die Ausgabedatei
	buffer = new Buffer(tempin, out2);
	result = NULL;
}

/*
 * Destruktor
 */
ParseTree::~ParseTree(){
	delete buffer;
	destroyTree(rootNode);
}

/*
 * Gibt den Speicher des Baums wieder frei
 */
void ParseTree::destroyTree(Node*node){
    if(node){
    	uint16_t childrenCount = node->getChildrenCount();

    	for(int i=0; i<childrenCount; i++){
    		destroyTree(node->getChild(i));
    	}

        delete node;
    }
}

/*
 * Gibt den Wurzelknoten zurück
 */
Node *ParseTree::getRootNode() {
	return rootNode;
}

/*
 * Gibt den Scanner zurück
 */
Scanner *ParseTree::getScanner() {
	return scanner;
}

/*
 * Sucht in der Symboltabelle nach einem Identifier
 */
Token *ParseTree::getSymTableEntryForIdentifier(Token *token)
{
	Token *myToken = NULL;
	if (token != NULL) {
		myToken = scanner->getSymTable()->lookup(token->getLexem());
	} else {
		std::cerr << "Internal Error: Identifier " << token->getLexem() << " not found in Symbol Table." << std::endl;
	}

	return myToken;
}

/*
 * Gibt den Typ eines Knoten zurück
 */
ParserConstant::Typification ParseTree::getType(Node *myNode)
{
	//cout << "Get Type" << endl;
	if (myNode->getNodeInfo()->getNodeType() == ParserConstant::NODE_IDENTIFIER) {
		// lookup in SymTable
		//cout << "Get Type Sym " << myNode->getNodeInfo()->getNodeType() << endl;
		return getSymTableEntryForIdentifier(myNode->getNodeInfo()->getToken())->getTypification();

	} else {
		// lookup in NodeInfo
		//cout << "Get Type Node " << myNode->getNodeInfo()->getNodeType() << endl;
		return myNode->getNodeInfo()->getTypification();
	}
}

/*
 * Setzt den Typ in einem Knoten oder der Symboltabelle
 */
void ParseTree::setType(Node *myNode, ParserConstant::Typification myType)
{
	//cout << "Set Type" << endl;
	if (myNode->getNodeInfo()->getNodeType() == ParserConstant::NODE_IDENTIFIER) {
		// set in SymTable
		getSymTableEntryForIdentifier(myNode->getNodeInfo()->getToken())->setTypification(myType);
		myNode->getNodeInfo()->setTypification(myType);
	} else {
		// set in NodeInfo
		myNode->getNodeInfo()->setTypification(myType);
	}
}

/*
 * Hauptmethode für die Typprüfung
 */
void ParseTree::typeCheck(Node *myNode) {
	// Starte mit dem Wurzelknoten
	if (myNode == NULL)
		myNode = rootNode;

	// Typprüfung auf den Knoten
	switch (myNode->getNodeInfo()->getNodeType()) {



	case ParserConstant::NODE_ROOT:
		// PROG
		std::cout << "type checking ..." << std::endl;
		typeCheck(myNode->getChild(0));
		setType(myNode, ParserConstant::noType);
		std::cout << "type checking done" << std::endl;
		break;

	case ParserConstant::NODE_PROG:
		//std::cout << "type checking PROG ..." << std::endl;
		// DECLS STATEMENTS
		typeCheck(myNode->getChild(0));
		typeCheck(myNode->getChild(1));
		setType(myNode, ParserConstant::noType);
		break;

	case ParserConstant::NODE_DECLS:
		//std::cout << "type checking DECLS ..." << std::endl;
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
		//std::cout << "type checking DECL ..." << std::endl;
		// int ARRAY identifier
		typeCheck(myNode->getChild(1));
		if (getType(myNode->getChild(2)) != ParserConstant::noType) {
			std::cerr << "--Typification Error: identifier '"
					<< myNode->getChild(2)->getNodeInfo()->getToken()->getLexem()
					<< "' is already defined";
			std::cerr << " at line "
					<< myNode->getChild(2)->getNodeInfo()->getToken()->getRow()
					<< ", column "
					<< myNode->getChild(2)->getNodeInfo()->getToken()->getCol()
					<< "." << std::endl;
			setType(myNode, ParserConstant::errorType);
		} else if (getType(myNode->getChild(1)) == ParserConstant::errorType) {
			setType(myNode, ParserConstant::errorType);
		} else {
			setType(myNode, ParserConstant::noType);
			if (getType(myNode->getChild(1)) == ParserConstant::arrayType) {
				setType(myNode->getChild(2), ParserConstant::intArrayType);
			} else {
				setType(myNode->getChild(2), ParserConstant::intType);
			}
		}
		break;

	case ParserConstant::NODE_ARRAY:
		//std::cout << "type checking ARRAY ..." << std::endl;
		if (myNode->getChildrenCount() > 0) {
			// [ integer ]
			if (myNode->getChild(1)->getNodeInfo()->getToken()->getIntegerValue() > 0) {
				setType(myNode, ParserConstant::arrayType);
			} else {
				cout << "No valid dimension" << endl;
				setType(myNode, ParserConstant::errorType);
			}
		} else {

			// €
			setType(myNode, ParserConstant::noType);
		}
		break;

	case ParserConstant::NODE_STATEMENTS:
		//std::cout << "type checking STATEMENTS ..." << std::endl;
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
		//std::cout << "type checking STATEMENT ..." << std::endl;
		if (myNode->getChild(0)->getNodeInfo()->getNodeType()
				== ParserConstant::NODE_IDENTIFIER) {
			// identifier INDEX := EXP
			typeCheck(myNode->getChild(3));
			typeCheck(myNode->getChild(1));
			if (getType(myNode->getChild(0)) == ParserConstant::noType) {
				std::cerr << "Typification Error: identifier '"
						<< myNode->getChild(2)->getNodeInfo()->getToken()->getLexem()
						<< "' is not defined";
				std::cerr << " at line "
						<< myNode->getChild(0)->getNodeInfo()->getToken()->getRow()
						<< ", column "
						<< myNode->getChild(0)->getNodeInfo()->getToken()->getCol()
						<< "." << std::endl;
				setType(myNode, ParserConstant::errorType);
			} else if ((getType(myNode->getChild(3)) == ParserConstant::intType)
					&& ((getType(myNode->getChild(0)) == ParserConstant::intType && getType(myNode->getChild(1)) == ParserConstant::noType)
							|| (getType(myNode->getChild(0)) == ParserConstant::intArrayType && getType(myNode->getChild(1)) == ParserConstant::arrayType))) {
				setType(myNode, ParserConstant::noType);
			} else {
				std::cerr << "Typification Error: identifier '"
						<< myNode->getChild(0)->getNodeInfo()->getToken()->getLexem()
						<< "' of type '"
						<< ParserConstant::typificationAsString(
								getType(myNode->getChild(0)))
						<< "' is incompatible to type '"
						<< ParserConstant::typificationAsString(
								getType(myNode->getChild(3))) << "'";
				std::cerr << " at line "
						<< myNode->getChild(0)->getNodeInfo()->getToken()->getRow()
						<< ", column "
						<< myNode->getChild(0)->getNodeInfo()->getToken()->getCol()
						<< "." << std::endl;
				setType(myNode, ParserConstant::errorType);
			}
		} else {
			// NODE_KEYWORD
			switch (myNode->getChild(0)->getNodeInfo()->getToken()->getTokenTypeInt()) {
			case Token::TT_WRITE:
				//std::cout << "type checking WRITE ..." << std::endl;
				// write ( EXP )
				typeCheck(myNode->getChild(2));
				setType(myNode, ParserConstant::noType);
				break;
			case Token::TT_READ:
				//std::cout << "type checking READ ..." << std::endl;
				// read ( identifier INDEX )
				typeCheck(myNode->getChild(3));
				if (getType(myNode->getChild(2)) == ParserConstant::noType) {
					std::cerr << "Typification Error: identifier '"
							<< myNode->getChild(2)->getNodeInfo()->getToken()->getLexem()
							<< "' is not defined";
					std::cerr << " at line "
							<< myNode->getChild(0)->getNodeInfo()->getToken()->getRow()
							<< ", column "
							<< myNode->getChild(0)->getNodeInfo()->getToken()->getCol()
							<< "." << std::endl;
					setType(myNode, ParserConstant::errorType);
				} else if (((getType(myNode->getChild(2))
						== ParserConstant::intType)
						&& getType(myNode->getChild(3))
								== ParserConstant::noType)
						|| ((getType(myNode->getChild(2))
								== ParserConstant::intArrayType)
								&& getType(myNode->getChild(3))
										== ParserConstant::arrayType)) {
					setType(myNode, ParserConstant::noType);
				} else {
					std::cerr << "Typification Error: identifier '"
							<< myNode->getChild(2)->getNodeInfo()->getToken()->getLexem()
							<< "' of type '"
							<< ParserConstant::typificationAsString(
									getType(myNode->getChild(3)))
							<< "' is incompatible to type '"
							<< ParserConstant::typificationAsString(
									getType(myNode->getChild(3))) << "'";
					std::cerr << " at line "
							<< myNode->getChild(2)->getNodeInfo()->getToken()->getRow()
							<< ", column "
							<< myNode->getChild(2)->getNodeInfo()->getToken()->getCol()
							<< "." << std::endl;
					setType(myNode, ParserConstant::errorType);
				}
				break;
			case Token::TT_BRACE_UPON:
				//std::cout << "type checking BRACE_UPON ..." << std::endl;
				// { STATEMENTS }
				typeCheck(myNode->getChild(1));
				setType(myNode, ParserConstant::noType);
				break;
			case Token::TT_IF:
				//std::cout << "type checking IF ..." << std::endl;
				// if ( EXP ) STATEMENT else STATEMENT
				typeCheck(myNode->getChild(2));
				typeCheck(myNode->getChild(4));
				typeCheck(myNode->getChild(6));
				if (getType(myNode->getChild(2)) == ParserConstant::errorType) {
					std::cerr
							<< "--Typification Error: integer required as expression for 'if' statement";
					std::cerr << " at line "
							<< myNode->getChild(0)->getNodeInfo()->getToken()->getRow()
							<< ", column "
							<< myNode->getChild(0)->getNodeInfo()->getToken()->getCol()
							<< "." << std::endl;
					setType(myNode, ParserConstant::errorType);
				} else {
					setType(myNode, ParserConstant::noType);
				}
				break;
			case Token::TT_WHILE:
				//std::cout << "type checking WHILE ..." << std::endl;
				// while ( EXP ) STATEMENT
				typeCheck(myNode->getChild(2));
				typeCheck(myNode->getChild(4));
				if (getType(myNode->getChild(2)) == ParserConstant::errorType) {
					std::cerr
							<< "Typification Error: integer required as expression for 'while' statement";
					std::cerr << " at line "
							<< myNode->getChild(0)->getNodeInfo()->getToken()->getRow()
							<< ", column "
							<< myNode->getChild(0)->getNodeInfo()->getToken()->getCol()
							<< "." << std::endl;
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
		//std::cout << "type checking INDEX ..." << std::endl;
		if (myNode->getChildrenCount() > 0) {
			// [ EXP ]
			typeCheck(myNode->getChild(1));
			if (getType(myNode->getChild(1)) == ParserConstant::errorType) {
				std::cerr << "Typification Error: integer required as index";
				std::cerr << " at line "
						<< myNode->getChild(0)->getNodeInfo()->getToken()->getRow()
						<< ", column "
						<< myNode->getChild(0)->getNodeInfo()->getToken()->getCol()
						<< "." << std::endl;
				setType(myNode, ParserConstant::errorType);
			} else {
				setType(myNode, ParserConstant::arrayType);
			}
		} else {
			// €
			setType(myNode, ParserConstant::noType);
		}
		break;

	case ParserConstant::NODE_EXP:
		//std::cout << "type checking EXP ..." << std::endl;
		// EXP2 OP_EXP
		typeCheck(myNode->getChild(0));
		typeCheck(myNode->getChild(1));
		//cout << "EXP aufruf " << endl;
		if (getType(myNode->getChild(1)) == ParserConstant::noType) {
			//cout << "Pruefe Epsilon" << endl;
			setType(myNode, getType(myNode->getChild(0)));
			//cout << "Get Type Epsilon" << endl;
		} else if (getType(myNode->getChild(0))
				!= getType(myNode->getChild(1))) {
			// incompatible types
			std::cerr << "Typification Error: incompatible types" << std::endl;
			//TODO
			//std::cerr << "Typification Error: expression '" << myNode->getChild(0)->getInfo()->getToken()->getLexem() << "' of type '" << parserConst::typificationAsString(getType(myNode->getChild(0))) << "' is incompatible to type '" << parserConst::typificationAsString(getType(myNode->getChild(3))) << "'";
			//std::cerr << " at line " << myNode->getChild(2)->getInfo()->getToken()->getLine() << ", column " << myNode->getChild(2)->getInfo()->getToken()->getColumn() << "." << std::endl;
			setType(myNode, ParserConstant::errorType);
		} else {
			//std::cout << "Set Type EXP" << std::endl;
			setType(myNode, getType(myNode->getChild(0)));
		}
		break;

	case ParserConstant::NODE_EXP2:
		//std::cout << "type checking EXP2 ..." << std::endl;
		switch (myNode->getChild(0)->getNodeInfo()->getToken()->getTokenTypeInt()) {
		case Token::TT_BRACKET_UPON:
			//std::cout << "type checking BRACKET_UPON ..." << std::endl;
			// ( EXP )
			typeCheck(myNode->getChild(1));
			setType(myNode, getType(myNode->getChild(1)));
			break;
		case Token::TT_IDENTIFIER:
			//std::cout << "type checking IDENTIFIER ..." << std::endl;
			// identifier INDEX
			typeCheck(myNode->getChild(1));
			if (getType(myNode->getChild(0)) == ParserConstant::noType) {
				std::cerr << "Typification Error: identifier '"
						<< myNode->getChild(0)->getNodeInfo()->getToken()->getLexem()
						<< "' is not defined";
				std::cerr << " at line "
						<< myNode->getChild(0)->getNodeInfo()->getToken()->getRow()
						<< ", column "
						<< myNode->getChild(0)->getNodeInfo()->getToken()->getCol()
						<< "." << std::endl;
				setType(myNode, ParserConstant::errorType);
			} else if ((getType(myNode->getChild(0)) == ParserConstant::intType)
					&& (getType(myNode->getChild(1)) == ParserConstant::noType)) {
				setType(myNode, getType(myNode->getChild(0)));
			} else if ((getType(myNode->getChild(0))
					== ParserConstant::intArrayType)
					&& (getType(myNode->getChild(1))
							== ParserConstant::arrayType)) {
				setType(myNode, ParserConstant::intType);
			} else {
				std::cerr << "no primitive type" << std::endl;
				//std::cerr << "Typification Error: identifier '" << myNode->getChild(2)->getInfo()->getToken()->getLexem() << "' of type '" << parserConst::typificationAsString(getType(myNode->getChild(3))) << "' is incompatible to type '" << parserConst::typificationAsString(getType(myNode->getChild(3))) << "'";
				//std::cerr << " at line " << myNode->getChild(2)->getInfo()->getToken()->getLine() << ", column " << myNode->getChild(2)->getInfo()->getToken()->getColumn() << "." << std::endl;
				//TODO
				setType(myNode, ParserConstant::errorType);
			}
			break;
		case Token::TT_INTEGER:
			//std::cout << "type checking INTEGER ..." << std::endl;
			// integer
			setType(myNode, ParserConstant::intType);
			break;
		case Token::TT_MINUS:
			//std::cout << "type checking MINUS ..." << std::endl;
			// - EXP2
			typeCheck(myNode->getChild(1));
			setType(myNode, getType(myNode->getChild(1)));
			break;
		case Token::TT_EXCLAMATION_MARK:
			//std::cout << "type checking EXCLAMATION_MARK ..." << std::endl;
			// ! EXP2
			typeCheck(myNode->getChild(1));
			if (getType(myNode->getChild(1)) != ParserConstant::intType) {
				std::cerr << "'!' operator requires integer" << std::endl;
				//TODO
				//std::cerr << "Typification Error: expression '" << myNode->getChild(0)->getInfo()->getToken()->getLexem() << "' of type '" << parserConst::typificationAsString(getType(myNode->getChild(0))) << "' is incompatible to type '" << parserConst::typificationAsString(getType(myNode->getChild(3))) << "'";
				//std::cerr << " at line " << myNode->getChild(2)->getInfo()->getToken()->getLine() << ", column " << myNode->getChild(2)->getInfo()->getToken()->getColumn() << "." << std::endl;
				setType(myNode, ParserConstant::errorType);
			} else {
				setType(myNode, ParserConstant::intType);
			}
			break;
		}

		break;

	case ParserConstant::NODE_OP_EXP:
		//std::cout << "type checking OP_EXP ..." << std::endl;
		if (myNode->getChildrenCount() > 0) {
			// OP EXP
			typeCheck(myNode->getChild(0));
			typeCheck(myNode->getChild(1));
			//cout << "Set Type OP_EXP  v" << myNode->getChild(1)->getNodeInfo()->getTypification() << endl;
			setType(myNode, myNode->getChild(1)->getNodeInfo()->getTypification());
		} else {
			// €
			setType(myNode, ParserConstant::noType);
		}
		break;

	case ParserConstant::NODE_OP:
		//std::cout << "type checking OP ..." << std::endl;
		// OP
		switch (myNode->getChild(0)->getNodeInfo()->getToken()->getTokenTypeInt()) {
		case Token::TT_PLUS:
			//std::cout << "type checking PLUS ..." << std::endl;
			setType(myNode, ParserConstant::opPlus);
			break;
		case Token::TT_MINUS:
			//std::cout << "type checking MINUS ..." << std::endl;
			setType(myNode, ParserConstant::opMinus);
			break;
		case Token::TT_STAR:
			//std::cout << "type checking STAR ..." << std::endl;
			setType(myNode, ParserConstant::opMult);
			break;
		case Token::TT_COLON:
			//std::cout << "type checking COLON ..." << std::endl;
			setType(myNode, ParserConstant::opDiv);
			break;
		case Token::TT_LESS:
			//std::cout << "type checking LESS ..." << std::endl;
			setType(myNode, ParserConstant::opLess);
			break;
		case Token::TT_MORE:
			//std::cout << "type checking MORE ..." << std::endl;
			setType(myNode, ParserConstant::opGreater);
			break;
		case Token::TT_COLON_EQUAL:
			//std::cout << "type checking COLON_EQUAL ..." << std::endl;
			setType(myNode, ParserConstant::opEqual);
			break;
		case Token::TT_MORE_COLON_MORE:
			//std::cout << "type checking MORE ..." << std::endl;
			setType(myNode, ParserConstant::opUnEqual);
			break;
		case Token::TT_AND:
			//std::cout << "type checking AND ..." << std::endl;
			setType(myNode, ParserConstant::opAnd);
			break;
		default:
			setType(myNode, ParserConstant::errorType);
			break;
		}
		break;

	case ParserConstant::NODE_ERROR:
	case ParserConstant::NODE_EMPTY:
	case ParserConstant::NODE_IDENTIFIER:
	case ParserConstant::NODE_KEYWORD:
	default:
		break;
	}
}


/*
 * Erzeugung des Maschinencode
 */
void ParseTree::makeCode(Node *myNode) {
	Marker *m1;
	Marker *m2;

	int size = 0;

	// Starte mit dem Wurzelknoten
	if (myNode == NULL)
		myNode = rootNode;

	// Typcheck auf den Knoten
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
		writeCode((char *)"STP\n");

		//Beende Ausgabedatei
		//writeCode((char *)"\0");
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
		// int ARRAY identifier
		std::cout << "DS $"
				<< myNode->getChild(2)->getNodeInfo()->getToken()->getLexem()
				<< " ";
		writeCode((char *)"DS $");
		writeCode(myNode->getChild(2)->getNodeInfo()->getToken()->getLexem());
		writeCode((char *)" ");

		makeCode(myNode->getChild(1));
		break;

	case ParserConstant::NODE_ARRAY:
		if (myNode->getChildrenCount() > 0) {
			// [ integer ]
			std::cout
					<< myNode->getChild(1)->getNodeInfo()->getToken()->getIntegerValue()
					<< std::endl;
			writeCode(intToChar(myNode->getChild(1)->getNodeInfo()->getToken()->getIntegerValue()));
			free (result);
			writeCode((char *)"\n");

		} else {
			// €
			std::cout << "1" << std::endl;
			writeCode((char *)"1\n");
		}
		break;

	case ParserConstant::NODE_STATEMENTS:
		if (myNode->getChildrenCount() > 0) {
			// STATEMENT ; STATEMENTS
			makeCode(myNode->getChild(0));
			makeCode(myNode->getChild(2));
		} else {
			// €
			std::cout << "NOP" << std::endl;
			writeCode((char *)"NOP\n");
		}
		break;

	case ParserConstant::NODE_STATEMENT:
		if (myNode->getChild(0)->getNodeInfo()->getNodeType()
				== ParserConstant::NODE_IDENTIFIER) {
			// identifier INDEX = EXP
			makeCode(myNode->getChild(3));

			std::cout << "LA $"
					<< myNode->getChild(0)->getNodeInfo()->getToken()->getLexem()
					<< std::endl;
			writeCode((char *)"LA $");
			writeCode(myNode->getChild(0)->getNodeInfo()->getToken()->getLexem());
			writeCode((char *)"\n");

			makeCode(myNode->getChild(1));

			std::cout << "STR" << std::endl;
			writeCode((char *)"STR\n");

		} else {
			// NODE_KEYWORD
			switch (myNode->getChild(0)->getNodeInfo()->getToken()->getTokenTypeInt()) {
			case Token::TT_WRITE:
				// write ( EXP )
				makeCode(myNode->getChild(2));

				std::cout << "PRI" << std::endl;
				writeCode((char *)"PRI\n");

				break;
			case Token::TT_READ:
				// read ( identifier INDEX )

				std::cout << "REA" << std::endl;
				writeCode((char *)"REA\n");

				std::cout << "LA $"
						<< myNode->getChild(2)->getNodeInfo()->getToken()->getLexem()
						<< endl;
				writeCode((char *)"LA $");
				writeCode(myNode->getChild(2)->getNodeInfo()->getToken()->getLexem());
				writeCode((char *)"\n");

				makeCode(myNode->getChild(3));

				std::cout << "STR" << std::endl;
				writeCode((char *)"STR\n");

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

				std::cout << "JIN #m" << m1->getName() << std::endl;
				writeCode((char *)"JIN #m");
				writeCode(intToChar(m1->getName()));
				free (result);
				writeCode((char *)"\n");

				makeCode(myNode->getChild(4));

				std::cout << "JMP #m" << m2->getName() << std::endl;
				writeCode((char *)"JMP #m");
				writeCode(intToChar(m2->getName()));
				free (result);
				writeCode((char *)"\n");

				std::cout << "#m" << m1->getName() << " NOP" << std::endl;
				writeCode((char *)"#m");
				writeCode(intToChar(m1->getName()));
				free (result);
				writeCode((char *)" NOP\n");

				makeCode(myNode->getChild(6));

				std::cout << "#m" << m2->getName() << " NOP" << std::endl;
				writeCode((char *)"#m");
				writeCode(intToChar(m2->getName()));
				free (result);
				writeCode((char *)" NOP\n");

				//Test wegen Memory Leak
				delete m1;
				delete m2;

				break;
			case Token::TT_WHILE:
				// while ( EXP ) STATEMENT
				m1 = new Marker();
				m2 = new Marker();

				std::cout << "#m" << m1->getName() << " NOP" << std::endl;
				writeCode((char *)"#m");
				writeCode(intToChar(m1->getName()));
				free (result);
				writeCode((char *)" NOP\n");

				makeCode(myNode->getChild(2));

				std::cout << "JIN #m" << m2->getName() << std::endl;
				writeCode((char *)"JIN #m");
				writeCode(intToChar(m2->getName()));
				free (result);
				writeCode((char *)"\n");

				makeCode(myNode->getChild(4));

				std::cout << "JMP #m" << m1->getName() << std::endl;
				writeCode((char *)"JMP #m");
				writeCode(intToChar(m1->getName()));
				free (result);
				writeCode((char *)"\n");

				std::cout << "#m" << m2->getName() << " NOP" << std::endl;
				writeCode((char *)"#m");
				writeCode(intToChar(m2->getName()));
				free (result);
				writeCode((char *)" NOP\n");

				//Test wegen Memory Leak
				delete m1;
				delete m2;

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
			writeCode((char *)"ADD\n");

		} else {
			// €
		}
		break;

	case ParserConstant::NODE_EXP:
		// EXP2 OP_EXP
		if (getType(myNode->getChild(1)) == ParserConstant::noType) {
			makeCode(myNode->getChild(0));
		} else if (getType(myNode->getChild(1)) == ParserConstant::opGreater) {
			makeCode(myNode->getChild(1));
			makeCode(myNode->getChild(0));

			std::cout << "LES ";
			writeCode((char *)"LES ");

		} else if (getType(myNode->getChild(1)) == ParserConstant::opUnEqual) {
			makeCode(myNode->getChild(0));
			makeCode(myNode->getChild(1));

			std::cout << "NOT ";
			writeCode((char *)"NOT ");

		} else {
			makeCode(myNode->getChild(0));
			makeCode(myNode->getChild(1));
		}
		break;

	case ParserConstant::NODE_EXP2:
		switch (myNode->getChild(0)->getNodeInfo()->getToken()->getTokenTypeInt()) {
		case Token::TT_BRACKET_UPON:
			// ( EXP )
			makeCode(myNode->getChild(1));
			break;
		case Token::TT_IDENTIFIER:
			// identifier INDEX

			std::cout << "LA $"
					<< myNode->getChild(0)->getNodeInfo()->getToken()->getLexem()
					<< std::endl;
			writeCode((char *)"LA $");
			writeCode(myNode->getChild(0)->getNodeInfo()->getToken()->getLexem());
			writeCode((char *)"\n");


			makeCode(myNode->getChild(1));

			std::cout << "LV" << std::endl;
			writeCode((char *)"LV\n");

			break;
		case Token::TT_INTEGER:
			// integer

			std::cout << "LC "
					<< myNode->getChild(0)->getNodeInfo()->getToken()->getIntegerValue()
					<< std::endl;
			writeCode((char *)"LC ");
			//cout << "Integer: " << myNode->getChild(0)->getNodeInfo()->getToken()->getIntegerValue() << endl;
			writeCode(intToChar(myNode->getChild(0)->getNodeInfo()->getToken()->getIntegerValue()));
			free (result);
			writeCode((char *)"\n");

			break;
		case Token::TT_MINUS:
			// - EXP2

			std::cout << "LC 0" << std::endl;
			writeCode((char *)"LC 0\n");

			makeCode(myNode->getChild(1));

			std::cout << "SUB" << std::endl;
			writeCode((char *)"SUB\n");

			break;
		case Token::TT_EXCLAMATION_MARK:
			// ! EXP2
			makeCode(myNode->getChild(1));

			std::cout << "NOT" << std::endl;
			writeCode((char *)"NOT\n");

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
				writeCode((char *)"ADD\n");

				break;
			case ParserConstant::opMinus:
				std::cout << "SUB" << std::endl;
				writeCode((char *)"SUB\n");

				break;
			case ParserConstant::opMult:
				std::cout << "MUL" << std::endl;
				writeCode((char *)"MUL\n");

				break;
			case ParserConstant::opDiv:
				std::cout << "DIV" << std::endl;
				writeCode((char *)"DIV\n");

				break;
			case ParserConstant::opLess:
				std::cout << "LES" << std::endl;
				writeCode((char *)"LES\n");

				break;
			case ParserConstant::opEqual:
				std::cout << "EQU" << std::endl;
				writeCode((char *)"EQU\n");

				break;
			case ParserConstant::opAnd:
				std::cout << "AND" << std::endl;
				writeCode((char *)"AND\n");

				break;
			case ParserConstant::opUnEqual:
				std::cout << "EQU" << std::endl;
				writeCode((char *)"EQU\n");

				break;
			default:
				std::cout << "EQU" << std::endl;
				writeCode((char *)"EQU\n");

				break;
			}
		} else {
			// €
		}
		break;

	case ParserConstant::NODE_OP:
		// sollte nie erreicht werden
		break;

	case ParserConstant::NODE_ERROR:
	case ParserConstant::NODE_EMPTY:
	case ParserConstant::NODE_IDENTIFIER:
	case ParserConstant::NODE_KEYWORD:
	default:
		break;
	}

}

/*
 * Schreibt die Maschinenbefehle in eine Ausgabedatei
 */
void ParseTree::writeCode(char *command){
	//Übergebe zu schreibenden Maschinencode an Buffer
	buffer->addCharsToOutBuffer(command);
}

/*
 * Ermittelt die Stellenanzahl eines Integerwertes
 */
int ParseTree::sizeOfNumber(int digit){

	int count = 0;

	//Bestimme Stellenanzahl
	while(digit != 0){
		digit = digit / 10;
		count++;
	}

	return count;
}

/*
 * Wandelt einen Integerwert in ein Chararray um
 */
char *ParseTree::intToChar(int digit){
	//cout << "Digit first: " << digit << endl;
	int size = sizeOfNumber(digit);

	result = (char *) malloc((size + 1) * sizeof(char));

	//Fange ab falls 0 übergeben wurde, sollte 0 direkt übergeben werden terminiert der OutBuffer --> daher Leerzeichen
	if(digit == 0){
		//cout << "Digit: " << digit << endl;
		char *temp = (char *)"0 ";
		return  temp;

	}else{
	//Modulo Rechnung zur Umwandlung
	for(int i = 0; i < size; i++){
		//Hier
		result[(size - 1) - i] = digit % 10 + '0';
		//cout << result[(size - 1) - i] << endl;
		digit = digit / 10;
	}

	result[size] = '\0';
	return result;
	}

}

