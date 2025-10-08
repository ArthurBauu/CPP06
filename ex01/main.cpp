#include "Serializer.hpp"

int main() {
    Data d;
    d.id = 42;
    d.name = "Example";
    d.value = 3.14f;

    std::cout << "=== Original Data ===\n";
    std::cout << "Address: " << &d << "\n";
    std::cout << "id: " << d.id << "\n";
    std::cout << "name: " << d.name << "\n";
    std::cout << "value: " << d.value << "\n\n";

    uintptr_t raw = Serializer::serialize(&d);
    std::cout << "Serialized value (raw uintptr_t): " << raw << "\n\n";

    Data* ptr = Serializer::deserialize(raw);
    std::cout << "=== Deserialized Data ===\n";
    std::cout << "Address: " << ptr << "\n";
    std::cout << "id: " << ptr->id << "\n";
    std::cout << "name: " << ptr->name << "\n";
    std::cout << "value: " << ptr->value << "\n";

	raw = Serializer::serialize(&d);
	d.id = 84;
	d.name = "Changed";
	d.value = 6.28f;

	std::cout << "\n=== Modified Original Data ===\n";
	std::cout << "Address: " << &d << "\n";
	std::cout << "id: " << d.id << "\n";
	std::cout << "name: " << d.name << "\n";
	std::cout << "value: " << d.value << "\n";

	ptr = Serializer::deserialize(raw);
	std::cout << "\n=== Deserialized Data After Original Modification ===\n";
	std::cout << "Address: " << ptr << "\n";
	std::cout << "id: " << ptr->id << "\n";
	std::cout << "name: " << ptr->name << "\n";
	std::cout << "value: " << ptr->value << "\n";

	

    return 0;
}
