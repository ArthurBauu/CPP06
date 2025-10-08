#include "Base.hpp"

class Wrong : public Base {};

Base *generate() {
	std::srand(time(NULL));
	int r = std::rand() % 3;

	if (r == 0) {
		std::cout << "Generated instance of A" << std::endl;
		return new A();
	}
	else if (r == 1) {
		std::cout << "Generated instance of B" << std::endl;
		return new B();
	}
	else {
		std::cout << "Generated instance of C" << std::endl;
		return new C();
	}
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p)) {
		std::cout << "Identified type: A" << std::endl;
		return;
	}
	else if (dynamic_cast<B*>(p)) {
		std::cout << "Identified type: B" << std::endl;
		return;
	}
	else if (dynamic_cast<C*>(p)) {
		std::cout << "Identified type: C" << std::endl;
		return;
	}
	else 
		std::cout << "Identified type: Unknown" << std::endl;
}

void identify(Base& p) {
	try {
		A& a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << "Identified type: A" << std::endl;
		return;
	}
	catch (std::bad_cast&) {}

	try {
		B& b = dynamic_cast<B&>(p);
		(void)b;
		std::cout << "Identified type: B" << std::endl;
		return;
	}
	catch (std::bad_cast&) {}

	try {
		C& c = dynamic_cast<C&>(p);
		(void)c;
		std::cout << "Identified type: C" << std::endl;
		return;
	}
	catch (std::bad_cast&) {}

	std::cout << "Identified type: Unknown" << std::endl;
}

int main() {
	Base* base = generate();

	std::cout << "\nIdentifying using pointer:" << std::endl;
	identify(base);

	std::cout << "\nIdentifying using reference:" << std::endl;
	identify(*base);

	Base& wrong = *(new Wrong());
	std::cout << "\nIdentifying wrong type using reference:" << std::endl;
	identify(wrong);
	std::cout << "\nIdentifying wrong type using pointer:" << std::endl;
	identify(&wrong);
	delete &wrong;

	delete base;
	return 0;
}