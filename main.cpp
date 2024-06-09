#include <iostream>
#include "scannerComp.cpp"
#include "parserComp.cpp"


int main()
{
	Scanner sc("imput.isi");
	/*Token token;
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
	}*/
	
	Parser parser(sc);
	
	try {
		parser.parse(); 
		std::cout << "Por fin compilo!" << std::endl;
	} catch (...) {
		std::cout << "Puros errores!" << std::endl;
	}
}
