#include <stdexcept>
#include <string>

class SyntaxException 
{
public:
	std::runtime_error
	SyntaxException(const std::string& message) : std::runtime_error(message) {}
};
