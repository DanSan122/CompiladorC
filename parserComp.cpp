// parserComp.cpp
#pragma once
#include "scannerComp.cpp"
#include "tokenComp.cpp"

class Parser {
private:
	Scanner scanner;
	Token token;
	
public:
	Parser(Scanner scanner) : scanner(scanner) {}
	
	// M todo para iniciar el an lisis sint ctico
	void parse() {
		token = scanner.nextToken();
		E(); // Llamada al m todo para analizar la cadena principal
		// Agregamos el an lisis de otra cadena
		if (!scanner.isEof()) {
			std::cout << "Otra cadena encontrada despu s de la cadena principal." << std::endl;
			E(); // Llamada al m todo para analizar la otra cadena
		}
	}
	
private:
		// M todo para analizar la cadena principal
		void E() {
			token = scanner.nextToken();
			if (token.getType() != Token::tkPunctuation) {
				T();
				El();
			}
		}
		
		// M todo para analizar el resto de la cadena principal
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
		
		// M todo para analizar un t rmino
		void T() {
			if (token.getType() != Token::tkIdentifier && token.getType() != Token::tkNumber) {
				std::cout << "ID or NUMBER Expected!, found " << Token::tkText[token.getType()] << " (" << token.getText() << ") at LINE " << token.getLine() << " and COLUMN " << token.getColumn() << std::endl;
			}
		}
		
		// M todo para analizar un operador
		void OP() {
			if (token.getType() != Token::tkOperator) {
				std::cout << "Operator Expected, found " << Token::tkText[token.getType()] << " (" << token.getText() << ") at LINE " << token.getLine() << " and COLUMN " << token.getColumn() << std::endl;
			}
		}
};
