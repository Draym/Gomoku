#include "Utils\Exception.h"

Exception::Exception(std::string const& type, std::string const& context, std::string const& function) throw()
{
	this->type = type;
	this->context = context;
	this->function = function;
}

char const	*Exception::what() const throw()
{
	return this->context.c_str();
}

std::string const	&Exception::where() const throw()
{
	return this->function;
}

void    Exception::showError() const
{
	std::cerr << type << " : " << context << std::endl;
	std::cerr << "---> " << this->where() << std::endl;
}

void	Exception::log(std::string const& type, std::string const& context, std::string const& function)
{
	std::cerr << type << " : " << context << std::endl;
	std::cerr << "--> " << function << std::endl;
}
