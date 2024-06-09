#pragma once
#include <iostream>
#include <string>

using namespace std;

class Token
{
private:
	int type;
	string text;
	int line;
	int column;
	
public:
	static const int tkIdentifier = 0;
	static const int tkNumber = 1;
	static const int tkOperator = 2;
	static const int tkPunctuation = 3;
	static const int tkAssign = 4;
	
	static const string tkText[];
	
	Token();
	
	void setType(int);
	void setText(string);
	void setLine(int);
	void setColumn(int);
	
	int getType();
	string getText();
	int getLine();
	int getColumn();
	
	void toString();
};

const string Token::tkText[] = {
	"IDENTIFICADOR", "NUMERO", "OPERADOR", "PUNTUACION", "ASIGNACION"
};

Token::Token()
{
	type = -1;
	text = "";
	line = -1;
	column = -1;
}

void Token::setType(int _type)
{
	type = _type;
}

void Token::setText(string _text)
{
	text = _text;
}

void Token::setLine(int _line)
{
	line = _line;
}

void Token::setColumn(int _column)
{
	column = _column;
}

int Token::getType()
{
	return type;
}

string Token::getText()
{
	return text;
}

int Token::getLine()
{
	return line;
}

int Token::getColumn()
{
	return column;
}

void Token::toString()
{
	string typeText = type != -1 ? tkText[type] : "None";
	
	cout << "Token [type = " << typeText
		<< ", text = " << text
		<< ", line = " << line
		<< ", column = " << column
		<< "]\n";
}
