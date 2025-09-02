/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: na-kannan <na-kannan@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by na-kannan         #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by na-kannan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
# define DATA_HPP

# include <string>

// Data structure must be non-empty (have data members)
struct Data
{
	int			id;
	std::string	name;
	double		value;
	
	// Constructor for easy initialization
	Data() : id(0), name(""), value(0.0) {}
	Data(int i, std::string const &n, double v) : id(i), name(n), value(v) {}
};

#endif
