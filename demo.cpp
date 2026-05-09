#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"

void printArray(DynamicArray<int>& arr) {
    std::cout << "[";
    for (int i = 0; i < arr.GetSize(); ++i) {
        std::cout << arr.Get(i);
        if (i < arr.GetSize() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

void printList(LinkedList<int>& list) {
    std::cout << "[";
    for (int i = 0; i < list.GetLength(); ++i) {
        std::cout << list.Get(i);
        if (i < list.GetLength() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

void printSequence(Sequence<int>* seq) {
    std::cout << "[";
    for (int i = 0; i < seq->GetLength(); ++i) {
        std::cout << seq->Get(i);
        if (i < seq->GetLength() - 1) std::cout << ", ";
    }
    std::cout << "] (length: " << seq->GetLength() << ")" << std::endl;
}

void demoDynamicArray() {
    std::cout << "\n=== DynamicArray ===" << std::endl;
    
    int items[] = {1, 2, 3, 4, 5};
    DynamicArray<int> arr(items, 5);
    std::cout << "Created array: ";
    printArray(arr);

    std::cout << "Get(2): " << arr.Get(2) << std::endl;
    
    arr.Set(2, 99);
    std::cout << "After Set(2, 99): ";
    printArray(arr);

    arr.Resize(7);
    std::cout << "After Resize(7): ";
    printArray(arr);

    arr.Resize(3);
    std::cout << "After Resize(3): ";
    printArray(arr);

    try {
        arr.Get(10);
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void demoLinkedList() {
    std::cout << "\n=== LinkedList ===" << std::endl;
    
    int items[] = {10, 20, 30};
    LinkedList<int> list(items, 3);
    std::cout << "Created list: ";
    printList(list);

    list.Append(40);
    std::cout << "After Append(40): ";
    printList(list);

    list.Prepend(0);
    std::cout << "After Prepend(0): ";
    printList(list);

    list.InsertAt(99, 2);
    std::cout << "After InsertAt(99, 2): ";
    printList(list);

    LinkedList<int>* sub = list.GetSubList(1, 3);
    std::cout << "GetSubList(1, 3): ";
    printList(*sub);
    delete sub;

    std::cout << "GetFirst(): " << list.GetFirst() << std::endl;
    std::cout << "GetLast(): " << list.GetLast() << std::endl;
}

void demoMutableArraySequence() {
    std::cout << "\n=== MutableArraySequence ===" << std::endl;
    
    int items[] = {1, 2, 3};
    MutableArraySequence<int> seq(items, 3);
    std::cout << "Created: ";
    printSequence(&seq);

    seq.Append(4);
    std::cout << "After Append(4): ";
    printSequence(&seq);

    seq.Prepend(0);
    std::cout << "After Prepend(0): ";
    printSequence(&seq);

    seq.InsertAt(99, 2);
    std::cout << "After InsertAt(99, 2): ";
    printSequence(&seq);

    int items2[] = {100, 200};
    MutableArraySequence<int> other(items2, 2);
    seq.Concat(&other);
    std::cout << "After Concat([100,200]): ";
    printSequence(&seq);

    Sequence<int>* sub = seq.GetSubsequence(2, 4);
    std::cout << "GetSubsequence(2,4): ";
    printSequence(sub);
    delete sub;
}

void demoImmutableArraySequence() {
    std::cout << "\n=== ImmutableArraySequence ===" << std::endl;
    
    int items[] = {1, 2, 3};
    ImmutableArraySequence<int> seq(items, 3);
    std::cout << "Original: ";
    printSequence(&seq);

    Sequence<int>* app = seq.Append(4);
    std::cout << "After Append(4) - new object: ";
    printSequence(app);
    std::cout << "Original NOT changed: ";
    printSequence(&seq);
    delete app;

    Sequence<int>* pre = seq.Prepend(0);
    std::cout << "After Prepend(0) - new object: ";
    printSequence(pre);
    std::cout << "Original NOT changed: ";
    printSequence(&seq);
    delete pre;
}

void demoMutableListSequence() {
    std::cout << "\n=== MutableListSequence ===" << std::endl;
    
    int items[] = {10, 20, 30};
    MutableListSequence<int> seq(items, 3);
    std::cout << "Created: ";
    printSequence(&seq);

    seq.Append(40);
    std::cout << "After Append(40): ";
    printSequence(&seq);

    seq.InsertAt(25, 2);
    std::cout << "After InsertAt(25, 2): ";
    printSequence(&seq);
}

void demoImmutableListSequence() {
    std::cout << "\n=== ImmutableListSequence ===" << std::endl;
    
    int items[] = {5, 10, 15};
    ImmutableListSequence<int> seq(items, 3);
    std::cout << "Original: ";
    printSequence(&seq);

    Sequence<int>* app = seq.Append(20);
    std::cout << "After Append(20) - new object: ";
    printSequence(app);
    std::cout << "Original NOT changed: ";
    printSequence(&seq);
    delete app;
}