/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: na-kannan <na-kannan@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by na-kannan         #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by na-kannan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

// Private constructors and destructor (never called)
Serializer::Serializer() {}
Serializer::Serializer(Serializer const &src) { (void)src; }
Serializer &Serializer::operator=(Serializer const &rhs) { (void)rhs; return *this; }
Serializer::~Serializer() {}

// Serialize: converts Data* to uintptr_t
// MUST use reinterpret_cast as per evaluation criteria
uintptr_t Serializer::serialize(Data* ptr)
{
	// First use of reinterpret_cast: Data* to uintptr_t
	return reinterpret_cast<uintptr_t>(ptr);
}

// Deserialize: converts uintptr_t back to Data*
// MUST use reinterpret_cast as per evaluation criteria
Data* Serializer::deserialize(uintptr_t raw)
{
	// Second use of reinterpret_cast: uintptr_t to Data*
	return reinterpret_cast<Data*>(raw);
}
