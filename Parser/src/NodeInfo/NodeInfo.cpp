#include "NodeInfo.h"

/*
 * Konstruktor
 */
NodeInfo::NodeInfo(ParserConstant::NodeType nodeType,
		Token *token, ParserConstant::Typification typification)
{
	this->nodeType = nodeType;
	this->token = token;
	this->typification = typification;
}

/*
 * Setzt den Knotentyp
 */
void NodeInfo::setNodeType(ParserConstant::NodeType nodeType) {
	this->nodeType = nodeType;
}

/*
 * Setzt das Token für den aktuellen Knoten
 */
void NodeInfo::setToken(Token *token) {
	this->token = token;
}

/*
 * Setzt den Typ für den aktuellen Knoten
 */
void NodeInfo::setTypification(ParserConstant::Typification typification) {
	this->typification = typification;
}

/*
 * Gibt den aktuellen Typ des Knoten zurück
 */
ParserConstant::NodeType NodeInfo::getNodeType() {
	return this->nodeType;
}

/*
 * Gibt das Token des aktuellen Koten zurück
 */
Token *NodeInfo::getToken() {
	return this->token;
}

/*
 * Gibt das Lexem des Tokens im aktuellen Knoten zurück
 */
char *NodeInfo::getLexem(){

	return this->token->getLexem();
}

/*
 * Gibt den Typ des aktuellen Knoten zurück
 */
ParserConstant::Typification NodeInfo::getTypification() {
	return this->typification;
}

