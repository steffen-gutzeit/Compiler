# Definition der Variablen

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib

SHAREDLIB = ../sharedlib


# Komponenten der Symboltabelle

MARKERDIR = Marker

NODEDIR = Node

NODEINFODIR = NodeInfo

PARSERDIR = Parser

PARSERCONSTANTDIR = ParserConstant

TREEDIR = Tree

# loeschen aller files im verzeichnis $(OBJDIR) und$(LIBDIR) und neu bauen

cleanParser:
	@echo "Clean Parser"
	rm -rf $(OBJDIR)/*
	rm -rf $(LIBDIR)/*
	$(MAKE) makeTestParser

#
#		Targets zum Bauen des Tests
#

# Linken der Object-files

makeTestParser: ParserLib TestParserTarget
	@echo "Linken der Parser Files"
	g++ -L$(SHAREDLIB) -Wall -o $(BINDIR)/ParserTest $(OBJDIR)/TestParser.o -lParser -lScanner -lSymtable -lAutomat -lBuffer 


#TestParser.o ist abhaengig von TestParser.cpp und Parser.h
TestParserTarget :  $(SRCDIR)/$(PARSERDIR)/TestParser.cpp $(SRCDIR)/$(PARSERDIR)/Parser.h
	@echo "Kompiliere TestParser"
	g++ -g  -c -Wall  -o $(OBJDIR)/TestParser.o  $(SRCDIR)/$(PARSERDIR)/TestParser.cpp
	

#	
# Erstellen der shared library
#

ParserLib: ParserLibTarget NodeLibTarget NodeInfoLibTarget MarkerLibTarget ParserConstantLibTarget TreeLibTarget 
	@echo "Erstelle Shared Library libParser"
	g++ -shared  -o $(SHAREDLIB)/libParser.so $(LIBDIR)/Parser.o $(LIBDIR)/Node.o $(LIBDIR)/NodeInfo.o $(LIBDIR)/Marker.o $(LIBDIR)/ParserConstant.o $(LIBDIR)/ParseTree.o

#
# Kompilieren der einzelnen Komponenten
#
	
ParserLibTarget :  $(SRCDIR)/$(PARSERDIR)/Parser.cpp $(SRCDIR)/$(PARSERDIR)/Parser.h
	@echo "Kompiliere Parser"
	g++ -g  -c -fPIC  -o $(LIBDIR)/Parser.o  $(SRCDIR)/$(PARSERDIR)/Parser.cpp

NodeLibTarget :  $(SRCDIR)/$(NODEDIR)/Node.cpp $(SRCDIR)/$(NODEDIR)/Node.h
	@echo "Kompiliere Node"
	g++ -g  -c -fPIC  -o $(LIBDIR)/Node.o  $(SRCDIR)/$(NODEDIR)/Node.cpp

NodeInfoLibTarget :  $(SRCDIR)/$(NODEINFODIR)/NodeInfo.cpp $(SRCDIR)/$(NODEINFODIR)/NodeInfo.h
	@echo "Kompiliere NodeInfo"
	g++ -g  -c -fPIC  -o $(LIBDIR)/NodeInfo.o  $(SRCDIR)/$(NODEINFODIR)/NodeInfo.cpp

MarkerLibTarget :  $(SRCDIR)/$(MARKERDIR)/Marker.cpp $(SRCDIR)/$(MARKERDIR)/Marker.h
	@echo "Kompiliere Marker"
	g++ -g  -c -fPIC  -o $(LIBDIR)/Marker.o  $(SRCDIR)/$(MARKERDIR)/Marker.cpp

ParserConstantLibTarget :  $(SRCDIR)/$(PARSERCONSTANTDIR)/ParserConstant.cpp $(SRCDIR)/$(PARSERCONSTANTDIR)/ParserConstant.h
	@echo "Kompiliere ParserConstant"
	g++ -g  -c -fPIC  -o $(LIBDIR)/ParserConstant.o  $(SRCDIR)/$(PARSERCONSTANTDIR)/ParserConstant.cpp

TreeLibTarget :  $(SRCDIR)/$(TREEDIR)/ParseTree.cpp $(SRCDIR)/$(TREEDIR)/ParseTree.h
	@echo "Kompiliere ParseTree"
	g++ -g  -c -fPIC  -o $(LIBDIR)/ParseTree.o  $(SRCDIR)/$(TREEDIR)/ParseTree.cpp
	
