#
#		Targets zum Bauen des Tests
#

# Linken der Object-files, abhaengig von AutomatTarget und TestAutomatTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

#Wichtig für Shared Librarys
#makeCompiler: AutomatTarget ScannerTarget BufferTarget TestScannerTarget ScannerLib
#	 g++ -g Automat/debug/Automat.o Scanner/debug/Scanner.o Buffer/debug/Buffer.o Scanner/debug/TestScanner.o -Lsharedlib -lScanner -o Compiler 

##makeCompiler: BufferTarget AutomatTarget ScannerTarget SymTableTarget TokenTarget TestScannerTarget 
##	g++ -g  Automat/debug/Automat.o Scanner/debug/Scanner.o Buffer/debug/Buffer.o Scanner/debug/TestScanner.o -o Compiler

#makeCompiler: BufferTarget AutomatTarget ScannerTarget SymTableTarget TokenTarget LinkedListTarget 
#	g++ -g  Automat/debug/Automat.o Scanner/debug/Scanner.o Buffer/debug/Buffer.o LinkedList/debug/LinkedList.o -o Compiler
 
makeCompiler: ParserConstTarget MarkerTarget NodeTarget NodeInfoTarget ParserTarget ParseTreeTarget AutomatTarget BufferTarget HashMapTarget LinkedListTarget ScannerTarget SymTableTarget TokenTarget TestScannerTarget 
	g++ -g -Ofast Parser/debug/ParserConstant.o Parser/debug/Marker.o Parser/debug/Node.o Parser/debug/NodeInfo.o Parser/debug/Parser.o Parser/debug/ParseTree.o Automat/debug/Automat.o Scanner/debug/Scanner.o Buffer/debug/Buffer.o HashMap/debug/HashMap.o Symtable/debug/Symtable.o Token/debug/Token.o LinkedList/debug/LinkedList.o Scanner/debug/TestScanner.o -o Compiler
	

# compilieren des Files Automat.cpp zu Automat.o, 
# das Objekt-File ist abhängig von src/Automat.cpp und src/Automat.h
# flag:
# -c --> compilieren
# -Wall --> alle meldungen erzeugen

AutomatTarget :  Automat/src/Automat.cpp Automat/src/Automat.h 
	g++ -g -Ofast -c -Wall Automat/src/Automat.cpp -o Automat/debug/Automat.o  
	
ScannerTarget :  Scanner/src/Scanner.cpp Scanner/src/Scanner.h 
	g++ -g -Ofast -c -Wall Scanner/src/Scanner.cpp -o Scanner/debug/Scanner.o  
	
BufferTarget :  Buffer/src/Buffer.cpp Buffer/src/Buffer.h 
	g++ -g -Ofast -c -Wall Buffer/src/Buffer.cpp -o Buffer/debug/Buffer.o  
	
SymTableTarget :  Symtable/src/Symtable.cpp Symtable/src/Symtable.h 
	g++ -g -Ofast -c -Wall Symtable/src/Symtable.cpp -o Symtable/debug/Symtable.o 
	
TokenTarget :  Token/src/Token.cpp Token/src/Token.h 
	g++ -g -Ofast -c -Wall Token/src/Token.cpp -o Token/debug/Token.o 

HashMapTarget : HashMap/src/HashMap.cpp HashMap/src/HashMap.h
	g++ -g -Ofast -c -Wall HashMap/src/HashMap.cpp -o HashMap/debug/HashMap.o 

LinkedListTarget : LinkedList/src/LinkedList.cpp LinkedList/src/LinkedList.h
	g++ -g -Ofast -c -Wall LinkedList/src/LinkedList.cpp -o LinkedList/debug/LinkedList.o 

TestScannerTarget :  Scanner/src/TestScanner.cpp
	g++ -g -Ofast -c -Wall Scanner/src/TestScanner.cpp -o Scanner/debug/TestScanner.o  	

#TestHashMapTarget :  HashMap/src/HashMap_test.cpp
#	g++ -g  -c -Wall HashMap/src/HashMap_test.cpp -o HashMap/debug/HashMap_test.o  

ParserConstTarget : Parser/src/ParserConstant/ParserConstant.cpp
	g++ -g -Ofast -c -Wall Parser/src/ParserConstant/ParserConstant.cpp -o Parser/debug/ParserConstant.o 

MarkerTarget : Parser/src/Marker/Marker.cpp
	g++ -g -Ofast -c -Wall Parser/src/Marker/Marker.cpp -o Parser/debug/Marker.o 

NodeTarget : Parser/src/Node/Node.cpp
	g++ -g -Ofast -c -Wall Parser/src/Node/Node.cpp -o Parser/debug/Node.o 

NodeInfoTarget : Parser/src/NodeInfo/NodeInfo.cpp
	g++ -g -Ofast -c -Wall Parser/src/NodeInfo/NodeInfo.cpp -o Parser/debug/NodeInfo.o 

ParserTarget : Parser/src/Parser/Parser.cpp
	g++ -g -Ofast -c -Wall Parser/src/Parser/Parser.cpp -o Parser/debug/Parser.o 

ParseTreeTarget : Parser/src/Tree/ParseTree.cpp
	g++ -g -Ofast -c -Wall Parser/src/Tree/ParseTree.cpp -o Parser/debug/ParseTree.o 

#TestParserTarget : Parser/src/Parse/TestParser.cpp	
#	g++ -g -Ofast -c -Wall Parser/src/Parse/TestParser.cpp -o Parser/src/Parse/debug/TestParser.o  


# loeschen aller files im verzeichnis obj und lib und neu bauen

cleanAutomat:
	rm -rf obj/*
	rm -rf lib/*
	$(MAKE) makeCompiler
	
	
#
# erstellen der shared library
#
#*.so Shared Library
#*.a  Staic Library

#utomatLib: AutomatLibTarget
#	g++ -shared Automat/lib/Automat.o -o sharedlib/libAutomat.so 
	
#BufferLib: BufferLibTarget
#	g++ -shared Buffer/lib/Buffer.o -o sharedlib/libBuffer.so

#ScannerLib: ScannerLibTarget BufferLibTarget AutomatLibTarget
#	g++ -o sharedlib/libScanner.so -shared Scanner/lib/Scanner.o 
	
# compilieren des Files Automat.cpp zu Automat.o mit dem Flag -fPIC (Position Independant Code)
#AutomatLibTarget :  Automat/src/Automat.cpp Automat/src/Automat.h
#	g++ -g  -c -fPIC  Automat/src/Automat.cpp -o Automat/lib/Automat.o   
	
#BufferLibTarget :  Buffer/src/Buffer.cpp Buffer/src/Buffer.h
#	g++ -g  -c -fPIC  Buffer/src/Buffer.cpp -o Buffer/lib/Buffer.o  
	
#ScannerLibTarget :  Scanner/src/Scanner.cpp Scanner/src/Scanner.h
#	g++ -g  -c -fPIC Scanner/src/Scanner.cpp -o Scanner/lib/Scanner.o  
	
	
	
	
