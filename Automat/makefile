# Definition der Variablen

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib

SHAREDLIB = ../sharedlib

# loeschen aller files im verzeichnis $(OBJDIR) und$(LIBDIR) und neu bauen

cleanAutomat:
	@echo "Clean Automat"
	rm -rf $(OBJDIR)/*
	rm -rf $(LIBDIR)/*
	$(MAKE) makeTestAutomat

#
#		Targets zum Bauen des Tests
#

# Linken der Object-files

makeTestAutomat: AutomatLib TestAutomatTarget
	@echo "Linken der Automat Files"
	g++ -L$(SHAREDLIB) -Wall -o $(BINDIR)/AutomatTest $(OBJDIR)/TestAutomat.o -lAutomat


#TestBuffer.o ist abhaengig von TestBuffer.cpp und Buffer.h
TestAutomatTarget :  $(SRCDIR)/TestAutomat.cpp $(SRCDIR)/Automat.h
	@echo "Kompiliere TestAutomat"
	g++ -g  -c -Wall  -o $(OBJDIR)/TestAutomat.o  $(SRCDIR)/TestAutomat.cpp
	

#	
# Erstellen der shared library
#

AutomatLib: AutomatLibTarget
	@echo "Erstelle Shared Library libAutomat"
	g++ -shared  -o $(SHAREDLIB)/libAutomat.so $(LIBDIR)/Automat.o 

	
AutomatLibTarget :  $(SRCDIR)/Automat.cpp $(SRCDIR)/Automat.h
	@echo "Kompiliere Automat"
	g++ -g  -c -fPIC  -o $(LIBDIR)/Automat.o  $(SRCDIR)/Automat.cpp 

	
