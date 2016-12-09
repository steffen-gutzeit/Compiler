# Definition der Variablen

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib

SHAREDLIB = ../sharedlib


# Komponenten der Symboltabelle

AUTOMATDIR = ../Automat

BUFFERDIR = ../Buffer

SYMBOLTABLEDIR = ../Symboltable

# loeschen aller files im verzeichnis $(OBJDIR) und$(LIBDIR) und neu bauen

cleanScanner:
	@echo "Clean Scanner"
	rm -rf $(OBJDIR)/*
	rm -rf $(LIBDIR)/*
	$(MAKE) makeTestScanner

#
#		Targets zum Bauen des Tests
#

# Linken der Object-files
# Einfügen aller benötigten Shared Libraries (Reihenfolge ist wichtig!)

makeTestScanner: ScannerLib TestScannerTarget
	@echo "Linken der Scanner Files"
	g++ -L$(SHAREDLIB) -Wall -o $(BINDIR)/ScannerTest $(OBJDIR)/TestScanner.o -lScanner -lSymtable -lAutomat -lBuffer 


#TestScanner.o ist abhaengig von TestScanner.cpp und Scanner.h
TestScannerTarget :  $(SRCDIR)/TestScanner.cpp $(SRCDIR)/Scanner.h
	@echo "Kompiliere TestScanner"
	g++ -g  -c -Wall  -o $(OBJDIR)/TestScanner.o  $(SRCDIR)/TestScanner.cpp
	

#	
# Erstellen der shared library
#

ScannerLib: ScannerLibTarget
	@echo "Erstelle Shared Library libScanner"
	g++ -shared  -o $(SHAREDLIB)/libScanner.so $(LIBDIR)/Scanner.o

#
# Kompilieren der einzelnen Komponenten
#
	
ScannerLibTarget :  $(SRCDIR)/Scanner.cpp $(SRCDIR)/Scanner.h
	@echo "Kompiliere Scanner"
	g++ -g  -c -fPIC  -o $(LIBDIR)/Scanner.o  $(SRCDIR)/Scanner.cpp 

	
