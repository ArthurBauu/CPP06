#include "ScalarConverter.hpp"

void ScalarConverter::convert(const std::string& literal) {

	if (isSpecialLiteral(literal))
		return;
	if (isChar(literal))
		convertChar(literal);
	else if (isInt(literal))
		convertInt(literal);
	else if (isFloat(literal))
		convertFloat(literal);
	else if (isDouble(literal))
		convertDouble(literal);
	else {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	}
}

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter()
{
}

bool ScalarConverter::isSpecialLiteral(const std::string& literal) {
	// Cas spéciaux pour les pseudo-littéraux
	if (literal == "nan" || literal == "nanf") {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
		return true;
	}
	if (literal == "+inf" || literal == "+inff" || literal == "inf" || literal == "inff") {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
		return true;
	}
	if (literal == "-inf" || literal == "-inff") {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
		return true;
	}
	return false;
}

bool ScalarConverter::isChar(const std::string& literal) {
	// Un caractère : soit un seul caractère non-numérique, soit un caractère quoté
	if (literal.length() == 1 && !std::isdigit(literal[0]) && std::isprint(literal[0]))
		return true;
	// Cas spéciaux pour les caractères non-affichables
	if (literal.length() == 1 && literal[0] >= 0 && literal[0] <= 127)
		return !std::isdigit(literal[0]);
	return false;
}

bool ScalarConverter::isInt(const std::string& literal) {
	size_t i = 0;
	if (literal[i] == '-' || literal[i] == '+')
		i++;
	if (i == literal.length())
		return false;
	for (; i < literal.length(); i++) {
		if (!std::isdigit(literal[i]))
			return false;
	}
	return true;
}

bool ScalarConverter::isFloat(const std::string& literal) {
	size_t i = 0;
	bool hasDecimal = false;
	if (literal[i] == '-' || literal[i] == '+')
		i++;
	if (i == literal.length())
		return false;
	for (; i < literal.length(); i++) {
		if (literal[i] == '.') {
			if (hasDecimal)
				return false;
			hasDecimal = true;
		} else if (literal[i] == 'f' && i == literal.length() - 1) {
			return hasDecimal;
		} else if (!std::isdigit(literal[i])) {
			return false;
		}
	}
	return false;
}

bool ScalarConverter::isDouble(const std::string& literal) {
	size_t i = 0;
	bool hasDecimal = false;
	if (literal[i] == '-' || literal[i] == '+')
		i++;
	if (i == literal.length())
		return false;
	for (; i < literal.length(); i++) 
	{
		if (literal[i] == '.') {
			if (hasDecimal)
				return false;
			hasDecimal = true;
		} else if (!std::isdigit(literal[i])) {
			return false;
		}
	}
	return hasDecimal;
}

void ScalarConverter::convertChar(const std::string& literal) {
	char c = literal[0];
	std::cout << "char: '" << c << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

void ScalarConverter::convertInt(const std::string& literal) {
	errno = 0;
	char* endptr;
	long value = std::strtol(literal.c_str(), &endptr, 10);
	
	if (errno == ERANGE || value > INT_MAX || value < INT_MIN || *endptr != '\0') {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	
	int i = static_cast<int>(value);
	if (i >= 32 && i <= 126)
		std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << static_cast<float>(i) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(i) << ".0" << std::endl;
}

void ScalarConverter::convertFloat(const std::string& literal) {
	errno = 0;
	char* endptr;
	std::string temp = literal;
	if (temp.length() > 0 && temp[temp.length() - 1] == 'f')
		temp = temp.substr(0, temp.length() - 1);
	
	double value = std::strtod(temp.c_str(), &endptr);
	
	if (errno == ERANGE || *endptr != '\0') {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	
	float f = static_cast<float>(value);
	
	if (f >= 32 && f <= 126 && std::floor(f) == f)
		std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;
	else if (f != f || f == std::numeric_limits<float>::infinity() || f == -std::numeric_limits<float>::infinity() || f < 0 || f > 127)
		std::cout << "char: impossible" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
		
	if (f >= std::numeric_limits<int>::min() && f <= std::numeric_limits<int>::max() && f == f)
		std::cout << "int: " << static_cast<int>(f) << std::endl;
	else
		std::cout << "int: impossible" << std::endl;
		
	std::cout << "float: " << f;
	if (f == static_cast<int>(f))
		std::cout << ".0";
	std::cout << "f" << std::endl;
	
	std::cout << "double: " << static_cast<double>(f);
	if (f == static_cast<int>(f))
		std::cout << ".0";
	std::cout << std::endl;
}

void ScalarConverter::convertDouble(const std::string& literal) {
	errno = 0;
	char* endptr;
	double d = std::strtod(literal.c_str(), &endptr);
	
	if (errno == ERANGE || *endptr != '\0') {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	
	if (d >= 32 && d <= 126 && std::floor(d) == d)
		std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
	else if (d != d || d == std::numeric_limits<double>::infinity() || d == -std::numeric_limits<double>::infinity() || d < 0 || d > 127)
		std::cout << "char: impossible" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
		
	if (d >= std::numeric_limits<int>::min() && d <= std::numeric_limits<int>::max() && d == d)
		std::cout << "int: " << static_cast<int>(d) << std::endl;
	else
		std::cout << "int: impossible" << std::endl;
		
	std::cout << "float: " << static_cast<float>(d);
	if (d == static_cast<int>(d))
		std::cout << ".0";
	std::cout << "f" << std::endl;
	
	std::cout << "double: " << d;
	if (d == static_cast<int>(d))
		std::cout << ".0";
	std::cout << std::endl;
}