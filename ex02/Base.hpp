#pragma once

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <typeinfo>

class Base {
	public:
		virtual ~Base();

	
};

class A : public Base {};
class B : public Base {};
class C : public Base {};