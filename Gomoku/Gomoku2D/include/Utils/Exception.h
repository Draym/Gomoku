#pragma once

#include <exception>
#include <utility>
#include <iostream>
#include <iomanip>
#include <string>

class Exception : public std::exception
{
public:
	Exception(std::string const& type, std::string const& context, std::string const& function) throw();
	virtual ~Exception() throw() {}
public:
	virtual char const	*what() const throw();
	std::string const	&where() const throw();
	void			showError() const;
	static void		log(std::string const& type, std::string const& context,
		std::string const& function);
private:
	std::string		type;
	std::string		context;
	std::string		function;
};
