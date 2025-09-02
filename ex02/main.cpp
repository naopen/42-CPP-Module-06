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
#include <cstdlib>
#include <ctime>
#include <exception>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

// Randomly instantiates A, B, or C and returns as Base pointer
Base * generate(void)
{
	int choice = std::rand() % 3;
	
	switch (choice)
	{
		case 0:
			std::cout << "Generated: A" << std::endl;
			return new A();
		case 1:
			std::cout << "Generated: B" << std::endl;
			return new B();
		case 2:
			std::cout << "Generated: C" << std::endl;
			return new C();
		default:
			return NULL;
	}
}

// Identify type using pointer - MUST check if cast returns NULL
void identify(Base* p)
{
	// Using dynamic_cast with pointer - returns NULL if cast fails
	if (dynamic_cast<A*>(p) != NULL)
	{
		std::cout << "A";
	}
	else if (dynamic_cast<B*>(p) != NULL)
	{
		std::cout << "B";
	}
	else if (dynamic_cast<C*>(p) != NULL)
	{
		std::cout << "C";
	}
	else
	{
		std::cout << "Unknown";
	}
}

// Identify type using reference - MUST use try-catch for failed casts
void identify(Base& p)
{
	// Using dynamic_cast with reference - throws exception if cast fails
	// Try A
	try
	{
		A& a = dynamic_cast<A&>(p);
		(void)a;  // Avoid unused variable warning
		std::cout << "A";
		return;
	}
	catch (std::exception& e)
	{
		// Not type A, continue
	}
	
	// Try B
	try
	{
		B& b = dynamic_cast<B&>(p);
		(void)b;  // Avoid unused variable warning
		std::cout << "B";
		return;
	}
	catch (std::exception& e)
	{
		// Not type B, continue
	}
	
	// Try C
	try
	{
		C& c = dynamic_cast<C&>(p);
		(void)c;  // Avoid unused variable warning
		std::cout << "C";
		return;
	}
	catch (std::exception& e)
	{
		// Not type C
		std::cout << "Unknown";
	}
}

int main()
{
	// Initialize random seed
	std::srand(std::time(NULL));
	
	std::cout << "=== Type Identification Test ===" << std::endl << std::endl;
	
	// Test multiple times to show randomness
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Test " << i + 1 << ":" << std::endl;
		
		// Generate random instance
		Base* obj = generate();
		
		if (obj)
		{
			// Test pointer identification
			std::cout << "  Identify by pointer:   ";
			identify(obj);
			std::cout << std::endl;
			
			// Test reference identification
			std::cout << "  Identify by reference: ";
			identify(*obj);
			std::cout << std::endl;
			
			// Clean up
			delete obj;
		}
		
		std::cout << std::endl;
	}
	
	// Additional test: Manual creation and identification
	std::cout << "=== Manual Test ===" << std::endl;
	
	A* a = new A();
	B* b = new B();
	C* c = new C();
	
	std::cout << "Created A - Identify by pointer: ";
	identify(a);
	std::cout << ", by reference: ";
	identify(*a);
	std::cout << std::endl;
	
	std::cout << "Created B - Identify by pointer: ";
	identify(b);
	std::cout << ", by reference: ";
	identify(*b);
	std::cout << std::endl;
	
	std::cout << "Created C - Identify by pointer: ";
	identify(c);
	std::cout << ", by reference: ";
	identify(*c);
	std::cout << std::endl;
	
	delete a;
	delete b;
	delete c;
	
	// Test with NULL pointer
	std::cout << std::endl << "=== NULL Pointer Test ===" << std::endl;
	Base* nullPtr = NULL;
	std::cout << "NULL pointer identification: ";
	identify(nullPtr);
	std::cout << std::endl;
	
	return 0;
}
