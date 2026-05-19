#include <iostream>
#include <limits>
#include "demo.h"

int main() {
    int choice = 0;
    while (choice != 16) {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "DATA STRUCTURES DEMONSTRATION" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "1. DynamicArray" << std::endl;
        std::cout << "2. LinkedList" << std::endl;
        std::cout << "3. MutableArraySequence" << std::endl;
        std::cout << "4. ImmutableArraySequence" << std::endl;
        std::cout << "5. MutableListSequence" << std::endl;
        std::cout << "6. ImmutableListSequence" << std::endl;
        std::cout << "7. Stack" << std::endl;
        std::cout << "8. Queue" << std::endl;
        std::cout << "9. Deque" << std::endl;
        std::cout << "10. Boolean (Power Set)" << std::endl;
        std::cout << "11. LazySequence (demo)" << std::endl;
        std::cout << "12. LazySequence (manual)" << std::endl;
        std::cout << "13. LazySequence (stress test)" << std::endl;
        std::cout << "14. LazySequence (auto test)" << std::endl;
        std::cout << "15. Stream" << std::endl;
        std::cout << "16. Exit" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Choose option: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input! Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: demoDynamicArray(); break;
            case 2: demoLinkedList(); break;
            case 3: demoMutableArraySequence(); break;
            case 4: demoImmutableArraySequence(); break;
            case 5: demoMutableListSequence(); break;
            case 6: demoImmutableListSequence(); break;
            case 7: demoStack(); break;
            case 8: demoQueue(); break;
            case 9: demoDeque(); break;
            case 10: demoBoolean(); break;
            case 11: demoLazySequence(); break;
            case 12: demoLazySequenceManual(); break;
            case 13: demoLazySequenceStress(); break;
            case 14: demoLazySequenceAuto(); break;
            case 15: demoStream(); break;
            case 16: std::cout << "Exiting." << std::endl; break;
            default: std::cout << "Invalid choice!" << std::endl;
        }
    }

    return 0;
}