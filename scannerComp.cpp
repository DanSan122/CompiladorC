#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "tokenComp.cpp"
#include "lexicalException.cpp"

class Scanner
{
private:
	int line;
	int column;
	std::string content;
	int pos;
	
public:
	Scanner(std::string);
	Token nextToken();
	bool isDigit(char);
	bool isChar(char);
	bool isOperator(char);
	bool isSpace(char);
	char nextChar();
	bool isEof();
	void back();
	bool isEofChar(char);
};

Scanner::Scanner(std::string fileName)
{
	line = 1;
	column = 0;
	std::ifstream file(fileName);
	
	if (file.is_open())
	{
		std::string txtContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		content = txtContent;
		pos = 0;
		file.close();
	}
	else
	{
		std::cerr << "Error al abrir el archivo\n";
	}
}

Token Scanner::nextToken()
{
	if (isEof())
	{
		return Token();
	}
	
	int estado = 0;
	std::string term;
	
	while (true)
	{
		char currentChar = nextChar();
		column++;
		
		if (estado == 0)
		{
			if (isChar(currentChar))
			{
				term += currentChar;
				estado = 1;
			}
			else if (isDigit(currentChar))
			{
				estado = 2;
				term += currentChar;
			}
			else if (isSpace(currentChar))
			{
				estado = 0;
			}
			else if (isOperator(currentChar))
			{
				term += currentChar;
				Token token;
				token.setType(Token::tkOperator);
				token.setText(term);
				token.setLine(line);
				token.setColumn(column - term.size());
				
				return token;
			}
			else
			{
				throw LexicalException("Simbolo no reconocido: " + currentChar);
			}
		}
		else if (estado == 1)
		{
			if (isChar(currentChar) || isDigit(currentChar))
			{
				estado = 1;
				term += currentChar;
			}
			else if (isSpace(currentChar) || isOperator(currentChar))
			{
				if (!isEofChar(currentChar))
				{
					back();
				}
				Token token;
				token.setType(Token::tkIdentifier);
				token.setText(term);
				token.setLine(line);
				token.setColumn(column - term.size());
				
				return token;
			}
			else
			{
				throw LexicalException("Identificador mal formado");
			}
		}
		else if (estado == 2)
		{
			if (isDigit(currentChar) || currentChar == '.')
			{
				estado = 2;
				term += currentChar;
			}
			else if (!isChar(currentChar) || isEofChar(currentChar))
			{
				if (!isEofChar(currentChar))
				{
					back();
				}
				Token token;
				token.setType(Token::tkNumber);
				token.setText(term);
				token.setLine(line);
				token.setColumn(column - term.size());
				
				return token;
			}
			else
			{
				throw LexicalException("Numero no reconocido");
			}
		}
	}
	return Token();
}

bool Scanner::isDigit(char c)
{
	return '0' <= c && c <= '9';
}

bool Scanner::isChar(char c)
{
	return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool Scanner::isOperator(char c)
{
	return c == '>' ||
		c == '<' ||
		c == '=' ||
		c == '!' ||
		c == '+' ||
		c == '-' ||
		c == '*' ||
		c == '/';
}

bool Scanner::isSpace(char c)
{
	if (c == '\n' || c == '\r')
	{
		line++;
		column = 0;
	}
	return c == ' ' ||
		c == '\t' ||
		c == '\n' ||
		c == '\r';
}

char Scanner::nextChar()
{
	if (isEof())
	{
		return '$';
	}
	return content[pos++];
}

bool Scanner::isEof()
{
	return pos >= content.size();
}

void Scanner::back()
{
	pos--;
	column--;
}

bool Scanner::isEofChar(char c)
{
	return c == '\0';
}
