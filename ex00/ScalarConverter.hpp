/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: na-kannan <na-kannan@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by na-kannan         #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by na-kannan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <string>
# include <iostream>
# include <iomanip>
# include <cstdlib>
# include <cerrno>
# include <climits>
# include <cfloat>
# include <cmath>
# include <sstream>
# include <limits>

class ScalarConverter
{
private:
	// Private constructor to prevent instantiation
	ScalarConverter();
	ScalarConverter(ScalarConverter const &src);
	ScalarConverter &operator=(ScalarConverter const &rhs);
	~ScalarConverter();

	// Helper methods for type detection and conversion
	static bool	isChar(std::string const &str);
	static bool	isInt(std::string const &str);
	static bool	isFloat(std::string const &str);
	static bool	isDouble(std::string const &str);
	static bool	isPseudoLiteral(std::string const &str);

	// Conversion helpers
	static void	convertFromChar(char c);
	static void	convertFromInt(std::string const &str);
	static void	convertFromFloat(std::string const &str);
	static void	convertFromDouble(std::string const &str);
	static void	convertFromPseudoLiteral(std::string const &str);

	// Display helpers
	static void	displayChar(double value, bool impossible);
	static void	displayInt(double value, bool impossible);
	static void	displayFloat(double value, bool impossible);
	static void	displayDouble(double value, bool impossible);

public:
	// The only public static method
	static void	convert(std::string const &str);
};

#endif
