#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cerrno>
#include <climits>

class ScalarConverter {
public:
	static void convert(const std::string& literal);
private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter& other);
	ScalarConverter& operator=(const ScalarConverter& other);
	~ScalarConverter();
	static bool isSpecialLiteral(const std::string& literal);
	static bool isChar(const std::string& literal);
	static bool isInt(const std::string& literal);
	static bool isFloat(const std::string& literal);
	static bool isDouble(const std::string& literal);
	static void convertChar(const std::string& literal);
	static void convertInt(const std::string& literal);
	static void convertFloat(const std::string& literal);
	static void convertDouble(const std::string& literal);
};