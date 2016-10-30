#pragma once

#include <sstream>
#include "../ParserConstant/ParserConstant.h"

#define _DEBUG
#define PARSER // leave here for SymTable.h/SymTable.cpp

static const int MAX_POSSIBLE_TOKENS		=	10000;
static const int MAX_CHILD_NODES			=	1000;

//#define codeType int
//
//// Arithmetik-Befehle ohne Argument
//static const codeType CODE_ADD	=	0;
//static const codeType CODE_SUB	=	CODE_ADD + 1;
//static const codeType CODE_MUL	=	CODE_SUB + 1;
//static const codeType CODE_DIV	=	CODE_MUL + 1;
//
//// Vergleich ohne Argument
//static const codeType CODE_LS	=	CODE_DIV + 1; // kleiner als
//static const codeType CODE_EQ	=	CODE_LS + 1;
//
//// Logische Operationen ohne Argument
//static const codeType CODE_AND	=	CODE_EQ + 1;
//static const codeType CODE_NOT	=	CODE_AND + 1;
//
//// Laden, Speichern
//static const codeType CODE_LA	=	CODE_NOT + 1; // Speicheradresse laden
//static const codeType CODE_LCI	=	CODE_LA + 1; // Konstante laden
//static const codeType CODE_LCF	=	CODE_LCI + 1; // Konstante laden
//static const codeType CODE_LV	=	CODE_LCF + 1; // gespeicherten Wert laden
//static const codeType CODE_STR	=	CODE_LV + 1; // Wert speichern
//
//// Einlesen und Drucken ohne Argument
//static const codeType CODE_PR	=	CODE_STR + 1; // drucken
//static const codeType CODE_RD	=	CODE_PR + 1; // einlesen
//
//// Sprünge mit Argument
//static const codeType CODE_JMP	=	CODE_RD + 1; // unbedingter Sprung
//static const codeType CODE_JIN	=	CODE_JMP + 1; // bedingter Sprung
//
//// sonstige
//static const codeType CODE_FLT	=	CODE_JIN + 1; // Konvertierung ohne Argument
//static const codeType CODE_DS	=	CODE_FLT + 1; // Speicher reservieren mit Argument
//static const codeType CODE_NOP	=	CODE_DS + 1; // nichts tun
//static const codeType CODE_STP	=	CODE_NOP + 1; // stoppen



class ParserConstant {

public:

	enum NodeType {
		NODE_ROOT		=	0,


		NODE_ERROR		=	2,
		NODE_EMPTY		=	3,

		NODE_PROG		=	4,
		NODE_DECLS		=	5,
		NODE_DECL		=	6,
		NODE_ARRAY		=	7,
		NODE_STATEMENTS	=	8,
		NODE_STATEMENT	=	9,
		NODE_EXP		=	10,
		NODE_EXP2		=	11,
		NODE_INDEX		=	12,
		NODE_OP_EXP		=	13,
		NODE_OP			=	14,

		NODE_IDENTIFIER	=	15,
		NODE_KEYWORD	=	16
	};

	enum Typification {
		noType			= 	0,
		errorType		= 	1,

		intType			=	2,
		intArrayType	=	3,
		arrayType		=	4,

		opPlus			=	5,
		opMinus			=	6,
		opMult			=	7,
		opDiv			=	8,
		opLess			=	9,
		opGreater		=	10,
		opEqual			=	11,
		opUnEqual		=	12,
		opAnd			=	13,

		unknownType		= 14
	};
	
	ParserConstant();
	
	
	static std::string nodeTypeAsString(NodeType myNodeType);
	static std::string typificationAsString(Typification myTypification);
	
};
