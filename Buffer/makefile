# Definition der Variablen

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib

SHAREDLIB = ../sharedlib

# loeschen aller files im verzeichnis $(OBJDIR) und$(LIBDIR) und neu bauen

cleanBuffer:
	@echo "Clean Buffer"
	rm -rf $(OBJDIR)/*
	rm -rf $(LIBDIR)/*
	$(MAKE) makeTestBuffer

#
#		Targets zum Bauen des Tests
#

# Linken der Object-files

makeTestBuffer: BufferLib TestBufferTarget
	@echo "Linken der Buffer Files"
	g++ -L$(SHAREDLIB) -Wall -o $(BINDIR)/BufferTest $(OBJDIR)/TestBuffer.o -lBuffer

#TestBuffer.o ist abhaengig von TestBuffer.cpp und Buffer.h
TestBufferTarget :  $(SRCDIR)/TestBuffer.cpp $(SRCDIR)/Buffer.h
	@echo "Kompiliere TestBuffer"
	g++ -g  -c -Wall  -o $(OBJDIR)/TestBuffer.o  $(SRCDIR)/TestBuffer.cpp
	

#	
# Erstellen der Shared library libBuffer
#

BufferLib: BufferLibTarget
	@echo "Erstelle Shared Library libBuffer"
	g++ -shared  -o $(SHAREDLIB)/libBuffer.so $(LIBDIR)/Buffer.o 

	
BufferLibTarget :  $(SRCDIR)/Buffer.cpp $(SRCDIR)/Buffer.h
	@echo "Kompiliere Buffer"
	g++ -g  -c -fPIC  -o $(LIBDIR)/Buffer.o  $(SRCDIR)/Buffer.cpp 

	
