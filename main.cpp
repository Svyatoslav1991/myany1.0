#include <iostream>
#include <vector>
#include <string>

#include "myany.h"


int main() {
	std::cout << "\tMYANY 1.0\n\n";

	try
	{
		std::vector<MyAny> vec = { 42, 3.14, static_cast<std::string>("qwerty") };

		for (const auto& item : vec)
		{
			if (item.isType<int>())
			{
				std::cout << "int " << item.cast<int>() << "\n";
			}
			else if (item.isType<double>())
			{
				std::cout << "double " << item.cast<double>() << "\n";
			}
			else if (item.isType<std::string>())
			{
				std::cout << "string " << item.cast<std::string>() << "\n";
			}
		}

		MyAny a;
		a = 5;
		std::cout << a.cast<int>() << "\n";
		a = 3.5;
		std::cout << a.cast<double>() << "\n";
		a = 'a';
		std::cout << a.cast<char>() << "\n";
	}
	catch (const std::bad_cast&)
	{
		std::cout << "Failed to cast the value\n";
	}
	catch (...)
	{
		std::cout << "Somethong went wrong\n";
	}




	return 0;
}