#include <iostream>
#include "../../../Scanner/src/Scanner.h"
#include "Parser.h"

/*
 * Main Klasse für den Compiler
 */
int main(int argc, char* argv[], char* envp[])
{
	Scanner *s;
	Parser *p;

	// Überprüfe Kommandozeilen Parameter
	// argv[0] -> Programmname
	// argv[1] -> Engabedatei
	// argv[2] -> Ausgabedatei Scanner
	// argv[3] -> Asugabedatei Maschinencode
	if (argc <= 1)
	{
		std::cerr << "Syntax: " << argv[0] << " Inputfile [Outputfile] [Codefile]" << std::endl;
		return 1;
	}

	else if (argc <= 2)
	{
		std::cerr << "Keine Ausgabedatei angegeben. Benutze \"out.txt\" als Standard." << std::endl;
		s = new Scanner(argv[1], (char *)"out.txt");
	}

	else
	{
		s = new Scanner(argv[1], argv[2]);
	}

	// Prüfe ob der Pfad der Code Datei angegeben wurde, Ansonsten Standardpfad
	if(argv[3] != NULL)
	{
		p = new Parser(s, argv[1], argv[3]);
	}
	else
	{
		std::cerr << "Kein Codefile angegeben. Benutze \"out.code\" als Standard." << std::endl;
		p = new Parser(s, argv[1], (char *)"out.code");
	}


	//Rufe Hauptmethode des Parsers auf
	uint16_t value = p->processFile();


	delete p;
	delete s;

	return value;

}
