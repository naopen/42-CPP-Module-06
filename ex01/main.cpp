/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: na-kannan <na-kannan@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by na-kannan         #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by na-kannan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include "Serializer.hpp"
#include "Data.hpp"

int main()
{
	std::cout << "=== Serialization Test ===" << std::endl << std::endl;
	
	// Create a Data object with some values
	Data originalData(42, "Test Data", 3.14159);
	
	// Display original data
	std::cout << "Original Data:" << std::endl;
	std::cout << "  Address: " << &originalData << std::endl;
	std::cout << "  ID:      " << originalData.id << std::endl;
	std::cout << "  Name:    " << originalData.name << std::endl;
	std::cout << "  Value:   " << std::fixed << std::setprecision(5) << originalData.value << std::endl;
	std::cout << std::endl;
	
	// Serialize the pointer
	uintptr_t serialized = Serializer::serialize(&originalData);
	std::cout << "Serialized value (uintptr_t): " << serialized << std::endl;
	std::cout << "Serialized value (hex):       0x" << std::hex << serialized << std::dec << std::endl;
	std::cout << std::endl;
	
	// Deserialize back to pointer
	Data* deserializedPtr = Serializer::deserialize(serialized);
	std::cout << "Deserialized pointer: " << deserializedPtr << std::endl;
	std::cout << std::endl;
	
	// Verify that the pointers are equal
	std::cout << "=== Verification ===" << std::endl;
	std::cout << "Original pointer:     " << &originalData << std::endl;
	std::cout << "Deserialized pointer: " << deserializedPtr << std::endl;
	std::cout << "Pointers are equal:   " << ((&originalData == deserializedPtr) ? "YES ✓" : "NO ✗") << std::endl;
	std::cout << std::endl;
	
	// Verify that we can access the data through the deserialized pointer
	if (deserializedPtr)
	{
		std::cout << "Data accessed through deserialized pointer:" << std::endl;
		std::cout << "  ID:      " << deserializedPtr->id << std::endl;
		std::cout << "  Name:    " << deserializedPtr->name << std::endl;
		std::cout << "  Value:   " << std::fixed << std::setprecision(5) << deserializedPtr->value << std::endl;
		std::cout << std::endl;
		
		// Verify values match
		std::cout << "Values match original: " << 
			((deserializedPtr->id == originalData.id && 
			  deserializedPtr->name == originalData.name &&
			  deserializedPtr->value == originalData.value) ? "YES ✓" : "NO ✗") << std::endl;
	}
	
	std::cout << std::endl;
	
	// Test with NULL pointer
	std::cout << "=== NULL Pointer Test ===" << std::endl;
	Data* nullPtr = NULL;
	uintptr_t nullSerialized = Serializer::serialize(nullPtr);
	Data* nullDeserialized = Serializer::deserialize(nullSerialized);
	
	std::cout << "NULL pointer:              " << nullPtr << std::endl;
	std::cout << "Serialized NULL:           " << nullSerialized << std::endl;
	std::cout << "Deserialized NULL pointer: " << nullDeserialized << std::endl;
	std::cout << "NULL pointers match:       " << ((nullPtr == nullDeserialized) ? "YES ✓" : "NO ✗") << std::endl;
	
	return 0;
}
