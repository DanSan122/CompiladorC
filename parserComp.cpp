#pragma once
#include "scannerComp.cpp"
#include "tokenComp.cpp"
#include "syntaxException.cpp"

class Parser {
private:
	Scanner scanner;
	Token token;
	
public:
	Parser(Scanner scanner) : scanner(scanner) {}
	
	void E() {
		token = scanner.nextToken();
		if (token.getType() != Token::tkPunctuation) {
			T();
			El();
		}
	}
	
	void El() {
		if (token.getType() == Token::tkOperator) {
			OP();
			token = scanner.nextToken();
			if (token.getType() != Token::tkPunctuation) {
				T();
				El();
			}
		}
	}
	
	void T() {
		if (token.getType() != Token::tkIdentifier && token.getType() != Token::tkNumber) {
			std::cout << "Error: ID o NUMBER esperado, encontrado " << Token::tkText[token.getType()]
				<< " (" << token.getText() << ") en LINEA " << token.getLine()
				<< " y COLUMNA " << token.getColumn() << std::endl;
		}
	}
	
	void OP() {
		if (token.getType() != Token::tkOperator) {
			std::cout << "Error: Operador esperado, encontrado " << Token::tkText[token.getType()] 
				<< " (" << token.getText() << ") en LÍNEA " << token.getLine() 
				<< " y COLUMNA " << token.getColumn() << std::endl;
		}
	}
	
};
