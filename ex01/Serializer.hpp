#pragma once

#include <iostream>
#include <stdint.h>
#include <string.h>


struct Data {

	std::string name;
	int id;
	float value;
};

class Serializer {
	public:
		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);
	
	private:
		Serializer();
		Serializer(const Serializer& other);
		Serializer& operator=(const Serializer& other);
		~Serializer();
};

