#
#	Baut den kompletten Compiler und ruft alle notwendigen Makefiles auf
#



#
# Pfadangaben zu den einzelnen Komponenten
#

AUTOMATDIR = Automat

BUFFERDIR = Buffer

SYMTABLEDIR = Symtable

SCANNERDIR = Scanner

PARSERDIR = Parser



SHAREDLIB = sharedlib



all:	automat buffer symtable scanner
	@echo "Compiler fertig gebaut."

scanner: 
	$(MAKE) -C $(SCANNERDIR)

automat:
	$(MAKE) -C $(AUTOMATDIR)
	
buffer:
	$(MAKE) -C $(BUFFERDIR)

symtable:
	$(MAKE) -C $(SYMTABLEDIR)


# Parser Makefileaufruf	
#parser:
#	$(MAKE) -C $(PARSERDIR)

