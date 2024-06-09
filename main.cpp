#include <iostream>
#include "scannerComp.cpp"
#include "parserComp.cpp"
#include "lexicalException.cpp"
#include "syntaxException.cpp"

int main()
{
	Scanner sc("input.isi");
	Token token;
	while (true)
	{
		token = sc.nextToken();
		if (token.getType() != -1)
		{
			token.toString();
		}
		else
		{
			break;
		}
	}
	
	Parser parser(sc);
	
	try
	{
		parser.E();
		std::cout << "�Compilaci�n exitosa!" << std::endl;
	}
	catch (const LexicalException& e)
	{
		std::cout << "Error l�xico: " << e.what() << std::endl;
	}
	catch (const SyntaxException& e)
	{
		std::cout << "Error sint�ctico: " << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error gen�rico: " << e.what() << std::endl;
	}
	
	return 0;
}
