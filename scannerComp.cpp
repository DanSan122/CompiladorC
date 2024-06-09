#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "tokenComp.cpp"

class Scanner
{
private:
	int line;
	int column;
	string content;
	int pos;
public:
	Scanner(string);
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

Scanner::Scanner(string fileName)
{
	line = 1;
	column = 0;
	ifstream file(fileName);
	
	if (file.is_open())
	{
		string txtContent((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		content = txtContent;
		pos = 0;
		file.close();
	}
	else
	{
		cerr << "Error al abrir el archivo\n";
	}
}

Token Scanner::nextToken()
{
	if (isEof())
	{
		return Token();
	}
	
	int estado = 0;
	string term;
	
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
				token.setType(token.tkOperator);
				token.setText(term);
				token.setLine(line);
				token.setColumn(column - term.size());
				
				return token;
			}
			else
			{
				cout << "Simbolo no reconocido.";
				break;
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
				token.setType(token.tkIdentifier);
				token.setText(term);
				token.setLine(line);
				token.setColumn(column - term.size());
				
				return token;
			}
			else
			{
				cout << "Identificador mal formado";
				break;
			}
		}
		else if (estado == 2)
		{
			if (isDigit(currentChar) || !currentChar == '.')
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
				token.setType(token.tkNumber);
				token.setText(term);
				token.setLine(line);
				token.setColumn(column - term.size());
				
				return token;
			}
			else
			{
				cout << "Numero no reconocido";
				break;
			}
		}
	}
	return 	Token();
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
	return  c == '>' ||
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
	return  c == ' ' ||
		c == '\t' ||
		c == '\n' ||
		c == '\r';
}

/*bool Scanner::isKeywordStart(char c)
{
	return isChar(c); // Un identificador puede ser el comienzo de una palabra clave
}*/

/*bool Scanner::isStringStart(char c)
{
	return c == '"'; // Una cadena de texto comienza con "
}*/

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
/*Token Scanner::recognizeKeyword()
{
	string word;
	while (isChar(currentChar) || isDigit(currentChar))
	{
		word += currentChar;
		currentChar = nextChar();
	}
	if (isKeyword(word))
	{
		Token token;
		token.setType(Token::tkKeyword);
		token.setText(word);
		token.setLine(line);
		token.setColumn(column - word.size());
		return token;
	}
	else
	{
		// Si la palabra no es una palabra clave, se trata como un identificador
		Token token;
		token.setType(Token::tkIdentifier);
		token.setText(word);
		token.setLine(line);
		token.setColumn(column - word.size());
		return token;
	}
}

Token Scanner::recognizeString()
{
	string text;
	currentChar = nextChar(); // Ignora el primer "
	while (currentChar != '"' && !isEofChar(currentChar))
	{
		text += currentChar;
		currentChar = nextChar();
	}
	if (currentChar == '"')
	{
		Token token;
		token.setType(Token::tkString);
		token.setText(text);
		token.setLine(line);
		token.setColumn(column - text.size());
		// Avanza al siguiente carácter después de "
		currentChar = nextChar();
		return token;
	}
	else
	{
		// Manejo de error: La cadena de texto no tiene un cierre
		cout << "Error: Cadena de texto sin cierre." << endl;
		exit(1);
	}
}*/
