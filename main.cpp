#include <iostream>
#include "demo.h"

int main() {
    int choice = 0;
    while (choice != 7) {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "DATA STRUCTURES DEMONSTRATION" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "1. DynamicArray" << std::endl;
        std::cout << "2. LinkedList" << std::endl;
        std::cout << "3. MutableArraySequence" << std::endl;
        std::cout << "4. ImmutableArraySequence" << std::endl;
        std::cout << "5. MutableListSequence" << std::endl;
        std::cout << "6. ImmutableListSequence" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Choose option: ";
        std::cin >> choice;

        switch (choice) {
            case 1: demoDynamicArray(); break;
            case 2: demoLinkedList(); break;
            case 3: demoMutableArraySequence(); break;
            case 4: demoImmutableArraySequence(); break;
            case 5: demoMutableListSequence(); break;
            case 6: demoImmutableListSequence(); break;
            case 7: std::cout << "Exiting." << std::endl; break;
            default: std::cout << "Invalid choice!" << std::endl;
        }
    }

    return 0;
}