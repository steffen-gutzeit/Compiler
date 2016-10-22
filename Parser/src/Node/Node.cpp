#include "Node.h"

Node::Node(NodeInfo *nodeInfo)
{
	for(uint16_t x = 0; x < MAX_CHILD_NODES; x++){
		childNodes[x] = NULL;
	}
	this->nodeInfo = nodeInfo;
	this->childrenCount = 0;
}

NodeInfo *Node::getNodeInfo()
{
	return nodeInfo;
}

void Node::setNodeInfo(NodeInfo *nodeInfo)
{
	this->nodeInfo = nodeInfo;
}

uint16_t Node::getChildrenCount()
{
	return childrenCount;
}

Node *Node::addChild(Node* myChild)
{
	childNodes[childrenCount] = myChild;
	childrenCount++;
	return myChild;
}

Node *Node::getChild(int which)
{
	return childNodes[which];
}
	
void Node::print()
{
	if (nodeInfo->getNodeType() == ParserConstant::NODE_ROOT) {
		std::cout << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>";
	} else {
		std::cout << "<" << ParserConstant::nodeTypeAsString(nodeInfo->getNodeType());
		if (nodeInfo->getToken()->getTypification() != ParserConstant::noType) {
			std::cout << " typification=\"" << ParserConstant::typificationAsString(nodeInfo->getToken()->getTypification()) << "\"";
		}
		std::cout << ">";
	}
	
	if (childrenCount == 0) {
		if (nodeInfo->getToken() != NULL) {
			if (nodeInfo->getToken()->getTokenTypeInt() == Token::TT_IDENTIFIER) {
				// Identifier
				std::cout << nodeInfo->getToken()->getLexem();
			} else {
				// Keyword

				//TODO: reaktivieren
//				std::cout << Const::tokenTypeAsString(myInfo->getToken()->getTokenType());

			}
		}
	}

	for (uint16_t i = 0; i < childrenCount; i++) childNodes[i]->print();
	
	if (nodeInfo->getNodeType() != ParserConstant::NODE_ROOT) std::cout << "</" << ParserConstant::nodeTypeAsString(nodeInfo->getNodeType()) << ">";
}

bool Node::isLeave()
{
	return (childrenCount == 0);
}
