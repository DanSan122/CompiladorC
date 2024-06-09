#include <stdexcept>
#include <string>

class LexicalException : public std::runtime_error
{
public:
	LexicalException(const std::string& message) : std::runtime_error(message) {}
};
