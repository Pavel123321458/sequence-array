#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"
#include "Stack.h"
#include "Queue.h"
#include "Deque.h"
#include "Boolean.h"
#include <chrono>
#include <limits>
#include "LazySequenceFactory.h"
#include "Stream.h"

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
    try { arr.Get(10); }
    catch (const std::exception& e) { std::cout << "Exception: " << e.what() << std::endl; }
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
    Stack<int> stack(new MutableArraySequence<int>());
    std::cout << "Created empty stack" << std::endl;
    std::cout << "IsEmpty: " << (stack.IsEmpty() ? "true" : "false") << std::endl;
    stack.Push(10); stack.Push(20); stack.Push(30);
    std::cout << "After Push(10, 20, 30): length = " << stack.GetLength()
              << ", peek = " << stack.Peek() << std::endl;
    std::cout << "Pop: " << stack.Pop() << std::endl;
    std::cout << "After Pop: length = " << stack.GetLength()
              << ", peek = " << stack.Peek() << std::endl;
    Stack<int>* mapped = stack.Map([](const int& x) { return x * x; });
    std::cout << "Map (square): ";
    while (!mapped->IsEmpty()) std::cout << mapped->Pop() << " ";
    std::cout << std::endl;
    delete mapped;
    stack.Push(30); stack.Push(40);
    Stack<int>* filtered = stack.Where([](const int& x) { return x % 20 == 0; });
    std::cout << "Where (multiples of 20): ";
    while (!filtered->IsEmpty()) std::cout << filtered->Pop() << " ";
    std::cout << std::endl;
    delete filtered;
    int sum = stack.Reduce([](const int& x, const int& acc) { return acc + x; }, 0);
    std::cout << "Reduce (sum): " << sum << std::endl;
    int subItems[] = {10, 20};
    MutableArraySequence<int> sub(subItems, 2);
    std::cout << "Contains [10, 20]: "
              << (stack.ContainsSubsequence(&sub) ? "true" : "false") << std::endl;
}

void demoQueue() {
    std::cout << "\n=== Queue ===" << std::endl;
    Queue<int> q(new LinkedList<int>());
    std::cout << "Created empty queue" << std::endl;
    std::cout << "IsEmpty: " << (q.IsEmpty() ? "true" : "false") << std::endl;
    q.Enqueue(10); q.Enqueue(20); q.Enqueue(30);
    std::cout << "After Enqueue(10, 20, 30): length = " << q.GetLength()
              << ", peek = " << q.Peek() << std::endl;
    std::cout << "Dequeue: " << q.Dequeue() << std::endl;
    std::cout << "After Dequeue: length = " << q.GetLength()
              << ", peek = " << q.Peek() << std::endl;
    Queue<int>* mapped = q.Map([](const int& x) { return x * 10; });
    std::cout << "Map (x10): ";
    while (!mapped->IsEmpty()) std::cout << mapped->Dequeue() << " ";
    std::cout << std::endl;
    delete mapped;
    q.Enqueue(40); q.Enqueue(50);
    Queue<int>* filtered = q.Where([](const int& x) { return x >= 30; });
    std::cout << "Where (>= 30): ";
    while (!filtered->IsEmpty()) std::cout << filtered->Dequeue() << " ";
    std::cout << std::endl;
    delete filtered;
    int sum = q.Reduce([](const int& x, const int& acc) { return acc + x; }, 0);
    std::cout << "Reduce (sum): " << sum << std::endl;
}

void demoDeque() {
    std::cout << "\n=== Deque ===" << std::endl;
    Deque<int> d(new LinkedList<int>());
    std::cout << "Created empty deque" << std::endl;
    d.PushFront(10); d.PushBack(20); d.PushFront(5);
    std::cout << "After PushFront(10), PushBack(20), PushFront(5): length = "
              << d.GetLength() << ", front = " << d.PeekFront()
              << ", back = " << d.PeekBack() << std::endl;
    std::cout << "PopFront: " << d.PopFront() << std::endl;
    std::cout << "PopBack: " << d.PopBack() << std::endl;
    std::cout << "Remaining: length = " << d.GetLength()
              << ", front = " << d.PeekFront() << std::endl;
    d.PushBack(30);
    Deque<int>* mapped = d.Map([](const int& x) { return x * 2; });
    std::cout << "Map (x2): ";
    while (!mapped->IsEmpty()) std::cout << mapped->PopFront() << " ";
    std::cout << std::endl;
    delete mapped;
    int sum = d.Reduce([](const int& x, const int& acc) { return acc + x; }, 0);
    std::cout << "Reduce (sum): " << sum << std::endl;
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
    for (int i = 0; i < result->GetLength(); ++i) delete result->Get(i);
    delete result;
}


void demoLazySequence() {
    std::cout << "\n=== LazySequence ===" << std::endl;

    std::cout << "Fibonacci (first 10): ";
    LazySequence<int>* fib = FibonacciSequence();
    for (int i = 0; i < 10; ++i)
        std::cout << fib->Get(i) << " ";
    std::cout << std::endl;
    std::cout << "Materialized: " << fib->GetMaterializedCount() << std::endl;
    delete fib;

    std::cout << "Factorial (first 7): ";
    LazySequence<int>* fact = FactorialSequence();
    for (int i = 0; i < 7; ++i)
        std::cout << fact->Get(i) << " ";
    std::cout << std::endl;
    delete fact;

    std::cout << "Natural numbers (1, 50, 100): ";
    LazySequence<int>* nat = NaturalNumbers();
    std::cout << nat->Get(0) << ", " << nat->Get(49) << ", " << nat->Get(99);
    std::cout << " (materialized: " << nat->GetMaterializedCount() << ")" << std::endl;
    delete nat;
}

std::string EncodeRLE(ReadOnlyStream<char>* input) {
    std::string result;
    while (!input->IsEndOfStream()) {
        char c = input->Read();
        int count = 1;
        while (!input->IsEndOfStream() && count < 9) {
            size_t pos = input->GetPosition();
            char next = input->Read();
            if (next == c) {
                count++;
            } else {
                input->Seek(pos);
                break;
            }
        }
        result += std::to_string(count) + c;
    }
    return result;
}

void demoStream() {
    std::cout << "\n=== Stream ===" << std::endl;

    WriteOnlyStream<int> wstream;
    wstream.Write(10);
    wstream.Write(20);
    wstream.Write(30);
    wstream.Write(40);
    wstream.Write(50);
    std::cout << "Written 5 elements" << std::endl;

    ReadOnlyStream<int> rstream(wstream.GetSequence(), false);
    std::cout << "Reading: ";
    while (!rstream.IsEndOfStream())
        std::cout << rstream.Read() << " ";
    std::cout << std::endl;

    char items[] = {'A', 'A', 'A', 'B', 'B', 'C', 'C', 'C', 'C'};
    MutableArraySequence<char>* seq = new MutableArraySequence<char>(items, 9);
    ReadOnlyStream<char> charStream(seq);
    std::cout << "RLE encoding of ";
    for (int i = 0; i < 9; ++i) std::cout << items[i];
    std::cout << ": " << EncodeRLE(&charStream) << std::endl;
}


void demoLazySequenceManual() {
    std::cout << "\n=== LazySequence - Manual Test ===" << std::endl;
    std::cout << "Enter how many Fibonacci numbers to generate: ";
    int n;
    std::cin >> n;

    LazySequence<int>* fib = FibonacciSequence();
    std::cout << "First " << n << " Fibonacci numbers:" << std::endl;
    for (int i = 0; i < n; ++i)
        std::cout << fib->Get(i) << " ";
    std::cout << std::endl;
    std::cout << "Materialized: " << fib->GetMaterializedCount() << std::endl;
    delete fib;
}

void demoLazySequenceStress() {
    std::cout << "\n=== LazySequence - Stress Test ===" << std::endl;
    std::cout << "Computing 1 000 000th Fibonacci number..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    LazySequence<int>* fib = FibonacciSequence();
    // Берём 100000-й (миллионный может переполнить int)
    int val = fib->Get(100000);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time: " << duration.count() << " ms" << std::endl;
    std::cout << "Materialized: " << fib->GetMaterializedCount() << " elements" << std::endl;
    delete fib;
}

void demoLazySequenceAuto() {
    std::cout << "\n=== LazySequence - Automated Test ===" << std::endl;

    // Заготовленные эталонные значения
    int expectedFib[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
    int expectedFact[] = {1, 1, 2, 6, 24, 120, 720, 5040};

    LazySequence<int>* fib = FibonacciSequence();
    LazySequence<int>* fact = FactorialSequence();

    bool fibOk = true, factOk = true;

    for (int i = 0; i < 10; ++i) {
        if (fib->Get(i) != expectedFib[i]) fibOk = false;
    }
    for (int i = 0; i < 8; ++i) {
        if (fact->Get(i) != expectedFact[i]) factOk = false;
    }

    std::cout << "Fibonacci test: " << (fibOk ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Factorial test: " << (factOk ? "PASSED" : "FAILED") << std::endl;

    delete fib;
    delete fact;

    std::cout << "\nAuto test complete." << std::endl;
}