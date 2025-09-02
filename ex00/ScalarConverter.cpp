/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: na-kannan <na-kannan@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by na-kannan         #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by na-kannan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

// Private constructors and destructor (never called)
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(ScalarConverter const &src) { (void)src; }
ScalarConverter &ScalarConverter::operator=(ScalarConverter const &rhs) { (void)rhs; return *this; }
ScalarConverter::~ScalarConverter() {}

// Type detection methods
bool ScalarConverter::isChar(std::string const &str)
{
	// Single character in single quotes: 'c', 'a', etc.
	// But shell removes quotes, so we also accept single non-digit characters
	if (str.length() == 3 && str[0] == '\'' && str[2] == '\'')
		return true;
	// Single character that is not a digit (handles shell removing quotes)
	if (str.length() == 1 && !std::isdigit(str[0]))
		return true;
	return false;
}

bool ScalarConverter::isInt(std::string const &str)
{
	if (str.empty())
		return false;
	
	size_t i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	
	if (i >= str.length())
		return false;
	
	for (; i < str.length(); i++)
	{
		if (!std::isdigit(str[i]))
			return false;
	}
	
	// Check for overflow
	errno = 0;
	char *endptr;
	long value = std::strtol(str.c_str(), &endptr, 10);
	if (errno == ERANGE || value < INT_MIN || value > INT_MAX)
		return false;
	
	return true;
}

bool ScalarConverter::isFloat(std::string const &str)
{
	if (str == "-inff" || str == "+inff" || str == "nanf")
		return true;
	
	if (str.empty() || str[str.length() - 1] != 'f')
		return false;
	
	// Remove the 'f' suffix for validation
	std::string num = str.substr(0, str.length() - 1);
	
	if (num.empty())
		return false;
	
	size_t i = 0;
	if (num[i] == '+' || num[i] == '-')
		i++;
	
	bool hasDigit = false;
	bool hasDot = false;
	
	for (; i < num.length(); i++)
	{
		if (num[i] == '.')
		{
			if (hasDot)
				return false;
			hasDot = true;
		}
		else if (std::isdigit(num[i]))
		{
			hasDigit = true;
		}
		else
		{
			return false;
		}
	}
	
	return hasDigit && hasDot;
}

bool ScalarConverter::isDouble(std::string const &str)
{
	if (str == "-inf" || str == "+inf" || str == "nan")
		return true;
	
	if (str.empty())
		return false;
	
	size_t i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	
	bool hasDigit = false;
	bool hasDot = false;
	
	for (; i < str.length(); i++)
	{
		if (str[i] == '.')
		{
			if (hasDot)
				return false;
			hasDot = true;
		}
		else if (std::isdigit(str[i]))
		{
			hasDigit = true;
		}
		else
		{
			return false;
		}
	}
	
	// Double must have a decimal point to distinguish from int
	return hasDigit && hasDot;
}

bool ScalarConverter::isPseudoLiteral(std::string const &str)
{
	return (str == "nan" || str == "nanf" || 
			str == "+inf" || str == "-inf" ||
			str == "+inff" || str == "-inff");
}

// Display methods
void ScalarConverter::displayChar(double value, bool impossible)
{
	std::cout << "char: ";
	if (impossible || std::isnan(value) || std::isinf(value) || 
		value < 0 || value > 127)
	{
		std::cout << "impossible" << std::endl;
	}
	else
	{
		// Using static_cast explicitly as required
		char c = static_cast<char>(value);
		if (std::isprint(c))
			std::cout << "'" << c << "'" << std::endl;
		else
			std::cout << "Non displayable" << std::endl;
	}
}

void ScalarConverter::displayInt(double value, bool impossible)
{
	std::cout << "int: ";
	if (impossible || std::isnan(value) || std::isinf(value) ||
		value < INT_MIN || value > INT_MAX)
	{
		std::cout << "impossible" << std::endl;
	}
	else
	{
		// Using static_cast explicitly as required
		std::cout << static_cast<int>(value) << std::endl;
	}
}

void ScalarConverter::displayFloat(double value, bool impossible)
{
	std::cout << "float: ";
	if (impossible)
	{
		std::cout << "impossible" << std::endl;
	}
	else if (std::isnan(value))
	{
		std::cout << "nanf" << std::endl;
	}
	else if (std::isinf(value))
	{
		if (value < 0)
			std::cout << "-inff" << std::endl;
		else
			std::cout << "+inff" << std::endl;
	}
	else
	{
		// Using static_cast explicitly as required
		float f = static_cast<float>(value);
		// Check if float overflows
		if (value > std::numeric_limits<float>::max() || 
		    value < -std::numeric_limits<float>::max())
		{
			std::cout << "impossible" << std::endl;
		}
		else
		{
			// Display with decimal point if it's a whole number
			if (f == static_cast<int>(f) && f >= INT_MIN && f <= INT_MAX)
				std::cout << f << ".0f" << std::endl;
			else
				std::cout << f << "f" << std::endl;
		}
	}
}

void ScalarConverter::displayDouble(double value, bool impossible)
{
	std::cout << "double: ";
	if (impossible)
	{
		std::cout << "impossible" << std::endl;
	}
	else if (std::isnan(value))
	{
		std::cout << "nan" << std::endl;
	}
	else if (std::isinf(value))
	{
		if (value < 0)
			std::cout << "-inf" << std::endl;
		else
			std::cout << "+inf" << std::endl;
	}
	else
	{
		// Display with decimal point if it's a whole number
		if (value == static_cast<int>(value) && value >= INT_MIN && value <= INT_MAX)
			std::cout << value << ".0" << std::endl;
		else
			std::cout << value << std::endl;
	}
}

// Conversion methods
void ScalarConverter::convertFromChar(char c)
{
	// Using static_cast explicitly for all conversions
	double value = static_cast<double>(c);
	
	displayChar(value, false);
	displayInt(value, false);
	displayFloat(value, false);
	displayDouble(value, false);
}

void ScalarConverter::convertFromInt(std::string const &str)
{
	char *endptr;
	long longValue = std::strtol(str.c_str(), &endptr, 10);
	
	// Using static_cast explicitly
	double value = static_cast<double>(longValue);
	
	displayChar(value, false);
	displayInt(value, false);
	displayFloat(value, false);
	displayDouble(value, false);
}

void ScalarConverter::convertFromFloat(std::string const &str)
{
	double value;
	
	if (str == "nanf")
		value = std::numeric_limits<double>::quiet_NaN();
	else if (str == "+inff")
		value = std::numeric_limits<double>::infinity();
	else if (str == "-inff")
		value = -std::numeric_limits<double>::infinity();
	else
	{
		char *endptr;
		// Remove 'f' suffix and use strtod for C++98 compatibility
		std::string numStr = str.substr(0, str.length() - 1);
		value = std::strtod(numStr.c_str(), &endptr);
	}
	
	displayChar(value, false);
	displayInt(value, false);
	displayFloat(value, false);
	displayDouble(value, false);
}

void ScalarConverter::convertFromDouble(std::string const &str)
{
	double value;
	
	if (str == "nan")
		value = std::numeric_limits<double>::quiet_NaN();
	else if (str == "+inf")
		value = std::numeric_limits<double>::infinity();
	else if (str == "-inf")
		value = -std::numeric_limits<double>::infinity();
	else
	{
		char *endptr;
		value = std::strtod(str.c_str(), &endptr);
	}
	
	displayChar(value, false);
	displayInt(value, false);
	displayFloat(value, false);
	displayDouble(value, false);
}

// Main conversion method
void ScalarConverter::convert(std::string const &str)
{
	if (str.empty())
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	
	// Check type and convert - order matters!
	if (isChar(str))
	{
		char c;
		// Handle both 'a' format and a format
		if (str.length() == 3 && str[0] == '\'' && str[2] == '\'')
			c = str[1];
		else
			c = str[0];
		convertFromChar(c);
	}
	else if (isFloat(str))  // Check float before int/double
	{
		convertFromFloat(str);
	}
	else if (isDouble(str))  // Check double before int
	{
		convertFromDouble(str);
	}
	else if (isInt(str))  // Check int last
	{
		convertFromInt(str);
	}
	else
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	}
}
