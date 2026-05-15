#include "Queue.h"
#include "Deque.h"
#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"
#include "Stack.h"
#include "Boolean.h"

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


void demoStack() {
    std::cout << "\n=== Stack ===" << std::endl;

    Stack<int> stack;
    std::cout << "Created empty stack" << std::endl;
    std::cout << "IsEmpty: " << (stack.IsEmpty() ? "true" : "false") << std::endl;

    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    std::cout << "After Push(10, 20, 30): length = " << stack.GetLength()
              << ", peek = " << stack.Peek() << std::endl;

    std::cout << "Pop: " << stack.Pop() << std::endl;
    std::cout << "After Pop: length = " << stack.GetLength()
              << ", peek = " << stack.Peek() << std::endl;

    // Map
    Stack<int>* mapped = stack.Map([](const int& x) { return x * x; });
    std::cout << "Map (square): ";
    while (!mapped->IsEmpty())
        std::cout << mapped->Pop() << " ";
    std::cout << std::endl;
    delete mapped;

    // Where
    stack.Push(30);
    stack.Push(40);
    Stack<int>* filtered = stack.Where([](const int& x) { return x % 20 == 0; });
    std::cout << "Where (multiples of 20): ";
    while (!filtered->IsEmpty())
        std::cout << filtered->Pop() << " ";
    std::cout << std::endl;
    delete filtered;

    // Reduce
    int sum = stack.Reduce([](const int& x, const int& acc) { return acc + x; }, 0);
    std::cout << "Reduce (sum): " << sum << std::endl;

    // ContainsSubsequence
    int subItems[] = {10, 20};
    MutableArraySequence<int> sub(subItems, 2);
    std::cout << "Contains [10, 20]: "
              << (stack.ContainsSubsequence(&sub) ? "true" : "false") << std::endl;
}

void demoBoolean() {
    std::cout << "\n=== Boolean (Power Set) ===" << std::endl;

    int items[] = {1, 2, 3};
    MutableArraySequence<int> seq(items, 3);
    std::cout << "Original set: [1, 2, 3]" << std::endl;

    Sequence<Sequence<int>*>* result = BuildBoolean(&seq);
    std::cout << "Total subsets: " << result->GetLength() << std::endl;

    for (int i = 0; i < result->GetLength(); ++i) {
        Sequence<int>* sub = result->Get(i);
        std::cout << "  {";
        for (int j = 0; j < sub->GetLength(); ++j) {
            std::cout << sub->Get(j);
            if (j < sub->GetLength() - 1) std::cout << ", ";
        }
        std::cout << "}" << std::endl;
    }

    // Очистка
    for (int i = 0; i < result->GetLength(); ++i)
        delete result->Get(i);
    delete result;
}



void demoQueue() {
    std::cout << "\n=== Queue ===" << std::endl;

    Queue<int> q;
    std::cout << "Created empty queue" << std::endl;
    std::cout << "IsEmpty: " << (q.IsEmpty() ? "true" : "false") << std::endl;

    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);
    std::cout << "After Enqueue(10, 20, 30): length = " << q.GetLength()
              << ", peek = " << q.Peek() << std::endl;

    std::cout << "Dequeue: " << q.Dequeue() << std::endl;
    std::cout << "After Dequeue: length = " << q.GetLength()
              << ", peek = " << q.Peek() << std::endl;

    // Map
    Queue<int>* mapped = q.Map([](const int& x) { return x * 10; });
    std::cout << "Map (x10): ";
    while (!mapped->IsEmpty())
        std::cout << mapped->Dequeue() << " ";
    std::cout << std::endl;
    delete mapped;

    // Where
    q.Enqueue(40);
    q.Enqueue(50);
    Queue<int>* filtered = q.Where([](const int& x) { return x >= 30; });
    std::cout << "Where (>= 30): ";
    while (!filtered->IsEmpty())
        std::cout << filtered->Dequeue() << " ";
    std::cout << std::endl;
    delete filtered;

    // Reduce
    int sum = q.Reduce([](const int& x, const int& acc) { return acc + x; }, 0);
    std::cout << "Reduce (sum): " << sum << std::endl;
}

void demoDeque() {
    std::cout << "\n=== Deque ===" << std::endl;

    Deque<int> d;
    std::cout << "Created empty deque" << std::endl;

    d.PushFront(10);
    d.PushBack(20);
    d.PushFront(5);
    std::cout << "After PushFront(10), PushBack(20), PushFront(5): length = "
              << d.GetLength() << ", front = " << d.PeekFront()
              << ", back = " << d.PeekBack() << std::endl;

    std::cout << "PopFront: " << d.PopFront() << std::endl;
    std::cout << "PopBack: " << d.PopBack() << std::endl;
    std::cout << "Remaining: length = " << d.GetLength()
              << ", front = " << d.PeekFront() << std::endl;

    // Map
    d.PushBack(30);
    Deque<int>* mapped = d.Map([](const int& x) { return x * 2; });
    std::cout << "Map (x2): ";
    while (!mapped->IsEmpty())
        std::cout << mapped->PopFront() << " ";
    std::cout << std::endl;
    delete mapped;

    // Reduce
    int sum = d.Reduce([](const int& x, const int& acc) { return acc + x; }, 0);
    std::cout << "Reduce (sum): " << sum << std::endl;
}