# Definition der Variablen

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib

SHAREDLIB = ../sharedlib


# Komponenten der Symboltabelle

TOKENDIR = ../Token

HASHMAPDIR = ../HashMap

LINKEDLISTDIR = ../LinkedList

# loeschen aller files im verzeichnis $(OBJDIR) und$(LIBDIR) und neu bauen

cleanSymtable:
	@echo "Clean Symtable"
	rm -rf $(OBJDIR)/*
	rm -rf $(LIBDIR)/*
	rm -rf $(TOKENDIR)/$(OBJDIR)/*
	rm -rf $(TOKENDIR)/$(LIBDIR)/*
	rm -rf $(HASHMAPDIR)/$(OBJDIR)/*
	rm -rf $(HASHMAPDIR)/$(LIBDIR)/*
	rm -rf $(LINKEDLISTDIR)/$(OBJDIR)/*
	rm -rf $(LINKEDLISTDIR)/$(LIBDIR)/*
	$(MAKE) makeTestSymtable

#
#		Targets zum Bauen des Tests
#

# Linken der Object-files

makeTestSymtable: SymtableLib TestSymtableTarget
	@echo "Linken der Symtable Files"
	g++ -L$(SHAREDLIB) -Wall -o $(BINDIR)/SymtableTest $(OBJDIR)/TestSymtable.o -lSymtable


#TestSymtable.o ist abhaengig von TestSymtable.cpp und Symtable.h
TestSymtableTarget :  $(SRCDIR)/TestSymtable.cpp $(SRCDIR)/Symtable.h
	@echo "Kompiliere TestSymtable"
	g++ -g  -c -Wall  -o $(OBJDIR)/TestSymtable.o  $(SRCDIR)/TestSymtable.cpp
	

#	
# Erstellen der shared library
#

SymtableLib: SymtableLibTarget TokenLibTarget HashMapLibTarget LinkedListLibTarget
	@echo "Erstelle Shared Library libSymtable"
	g++ -shared  -o $(SHAREDLIB)/libSymtable.so $(LIBDIR)/Symtable.o $(TOKENDIR)/$(LIBDIR)/Token.o $(HASHMAPDIR)/$(LIBDIR)/HashMap.o $(LINKEDLISTDIR)/$(LIBDIR)/LinkedList.o

#
# Kompilieren der einzelnen Komponenten
#
	
SymtableLibTarget :  $(SRCDIR)/Symtable.cpp $(SRCDIR)/Symtable.h
	@echo "Kompiliere Symtable"
	g++ -g  -c -fPIC  -o $(LIBDIR)/Symtable.o  $(SRCDIR)/Symtable.cpp 

TokenLibTarget :  $(TOKENDIR)/$(SRCDIR)/Token.cpp $(TOKENDIR)/$(SRCDIR)/Token.h
	@echo "Kompiliere Token"
	g++ -g  -c -fPIC  -o $(TOKENDIR)/$(LIBDIR)/Token.o  $(TOKENDIR)/$(SRCDIR)/Token.cpp 

HashMapLibTarget :  $(HASHMAPDIR)/$(SRCDIR)/HashMap.cpp $(HASHMAPDIR)/$(SRCDIR)/HashMap.h
	@echo "Kompiliere HashMap"
	g++ -g  -c -fPIC  -o $(HASHMAPDIR)/$(LIBDIR)/HashMap.o  $(HASHMAPDIR)/$(SRCDIR)/HashMap.cpp 

LinkedListLibTarget :  $(LINKEDLISTDIR)/$(SRCDIR)/LinkedList.cpp $(LINKEDLISTDIR)/$(SRCDIR)/LinkedList.h
	@echo "Kompiliere LinkedList"
	g++ -g  -c -fPIC  -o $(LINKEDLISTDIR)/$(LIBDIR)/LinkedList.o  $(LINKEDLISTDIR)/$(SRCDIR)/LinkedList.cpp 

	
