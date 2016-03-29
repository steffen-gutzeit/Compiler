#include "Scanner.h"
#include <iostream>
#include <stdint.h>

//argv[0] beinhaltet den Namen des Programms, der Rest sind die Parameter
int main(int argc, char **argv) {
	Scanner* scanner;

	if(argc == 3){
		printf("Beginne ...\n");
		scanner = new Scanner(argv[1], argv[2]);
		    /*int i;
			for (i = 0; i < argc; i++){
				std::cout << argv[i] << endl;
			}*/

			scanner->getNextToken();

			delete scanner;
		printf("Vorgang Beendet.\n");
	}else{
		printf("Nicht genügend Parameter übergeben. \nEs werden 2 benötigt. Übergeben wurden nur %d Parameter.\n", argc - 1);
	}


	/*for (int i = 0; i < 500; i++) {
		scanner->getNextToken();
	}*/

	//std::cout << scanner->getTokenType("abc") << std::endl;


}
