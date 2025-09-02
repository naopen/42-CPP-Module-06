/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: na-kannan <na-kannan@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by na-kannan         #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by na-kannan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

# include <stdint.h>  // For uintptr_t in C++98
# include "Data.hpp"

class Serializer
{
private:
	// Private constructor to prevent instantiation
	Serializer();
	Serializer(Serializer const &src);
	Serializer &operator=(Serializer const &rhs);
	~Serializer();

public:
	// Static methods for serialization
	static uintptr_t	serialize(Data* ptr);
	static Data*		deserialize(uintptr_t raw);
};

#endif
