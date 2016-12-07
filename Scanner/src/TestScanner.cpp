#include "Scanner.h"
#include <iostream>
#include <stdint.h>
#include <time.h>

//argv[0] beinhaltet den Namen des Programms, der Rest sind die Parameter
int main(int argc, char **argv) {

	//Zeitberechnung Anfang
	double timeProcess=0.0, tstart; ; //Definierung der Variablen
	tstart = clock(); //CPU-Zeit zu Beginn des Programmes

	time_t start = time(0);

	Scanner* scanner;

	if(argc == 3){
		printf("Beginne ...\n");
		scanner = new Scanner(argv[1], argv[2]);

			bool eof = false;

			while(eof == false){
				Token *token = scanner->getNextToken();

				if(token == NULL){
					eof = true;
				}else{
					//std::cout << token->getTokenType() << endl;
				}
			}


			printf("Vorgang Beendet.\n");


			//Gebe Symboltabelle aus

			printf("Ausgabe Symboltabelle.\n");

				scanner->printSymbtable();

			printf("Ende Ausgabe Symboltabelle.\n");


			//Test ob die Suche funktioniert

			/*printf("Ausgabe Suche in Symboltabelle.\n");

				bool found;
				char lexem[] = "write";
				found = scanner->testSymbtable(lexem);
				cout << "Suche Lexem: " << lexem << " Gefunden: " << found << endl;
				char lexem1[] = "m";
				found = scanner->testSymbtable(lexem1);
				cout << "Suche Lexem: " << lexem1 << " Gefunden: " << found << endl;

			printf("Ende Ausgabe Suche in Symboltabelle.\n");*/


			//Aufrufen der Dekonstruktoren

			delete scanner;

	}else{
		printf("Nicht genügend Parameter übergeben. \nEs werden 2 benötigt. Übergeben wurden nur %d Parameter.\n", argc - 1);
	}

	//Zeitberechnung Ende
	timeProcess += clock() - tstart;     // end
	timeProcess = timeProcess/CLOCKS_PER_SEC;  // rescale to seconds

	time_t end = time(0);
	double timeReal = difftime(end, start);

	cout << "Prozesslaufzeit: \t\t" << timeProcess << " Sekunden." << endl;
	cout << "Wirklich benoetigte Zeit: \t" << timeReal << " Sekunden." << endl;


}
