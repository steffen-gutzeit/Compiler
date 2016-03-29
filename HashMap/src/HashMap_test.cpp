#include "HashMap.h"
#include <iostream>

int main() {
	HashMap *hashMap;
	hashMap = new HashMap(128);

	//hashMap->addHashValue("123");
	//hashMap->addHashValue("132");
	//hashMap->addHashValue("213");

	std::cout << "TEST1";

	delete hashMap;
}
