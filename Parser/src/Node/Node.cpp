#include "Node.h"

Node::Node(NodeInfo *nodeInfo)
{
	for(uint16_t x = 0; x < MAX_CHILD_NODES; x++){
		childNodes[x] = NULL;
	}
	this->nodeInfo = nodeInfo;
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
	if (nodeInfo->getNodeInfoType() == NODE_ROOT) {
		std::cout << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>";
	} else {
		std::cout << "<" << parserConst::nodeTypeAsString(nodeInfo->getNodeInfoType());
		if (nodeInfo->getTypification() != TYPIFICATION_NONE) {
			std::cout << " typification=\"" << parserConst::typificationAsString(nodeInfo->getTypification()) << "\"";
		}
		std::cout << ">";
	}
	
	if (childrenCount == 0) {
		if (nodeInfo->getToken() != NULL) {
			if (nodeInfo->getToken()->getTokenType() == Token::TT_IDENTIFIER) {
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
	
	if (nodeInfo->getNodeInfoType() != NODE_ROOT) std::cout << "</" << parserConst::nodeTypeAsString(nodeInfo->getNodeInfoType()) << ">";
}

bool Node::isLeave()
{
	return (childrenCount == 0);
}
