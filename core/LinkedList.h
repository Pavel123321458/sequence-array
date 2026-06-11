#pragma once
#include <stdexcept>
#include "Sequence.h"

template <class T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& item) : data(item), next(nullptr) {}
    };

    Node* head;
    int length;

public:
    class Iterator : public Sequence<T>::Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}
        T& operator*() override { return current->data; }
        typename Sequence<T>::Iterator& operator++() override { current = current->next; return *this; }
        bool operator!=(const typename Sequence<T>::Iterator& other) const override {
            return current != static_cast<const Iterator&>(other).current;
        }
        Node* getNode() const { return current; }
    };

    Iterator* begin() { return new Iterator(head); }
    Iterator* end() { return new Iterator(nullptr); }

    LinkedList(T* items, int count) : head(nullptr), length(0) {
        for (int i = 0; i < count; ++i) Append(items[i]);
    }

    LinkedList() : head(nullptr), length(0) {}

    LinkedList(const LinkedList<T>& list) : head(nullptr), length(0) {
        Node* current = list.head;
        while (current) { Append(current->data); current = current->next; }
    }

    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            while (head) { Node* temp = head; head = head->next; delete temp; }
            head = nullptr; length = 0;
            Node* current = other.head;
            while (current) { Append(current->data); current = current->next; }
        }
        return *this;
    }

    ~LinkedList() { while (head) { Node* temp = head; head = head->next; delete temp; } }

    T GetFirst() const {
        if (!head) throw std::out_of_range("IndexOutOfRange: list is empty");
        return head->data;
    }

    T GetLast() const {
        if (!head) throw std::out_of_range("IndexOutOfRange: list is empty");
        Node* current = head;
        while (current->next) current = current->next;
        return current->data;
    }

    T Get(int index) const {
        if (index < 0 || index >= length) throw std::out_of_range("IndexOutOfRange");
        Node* current = head;
        for (int i = 0; i < index; ++i) current = current->next;
        return current->data;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex >= length || startIndex > endIndex)
            throw std::out_of_range("IndexOutOfRange");
        LinkedList<T>* sub = new LinkedList<T>();
        Node* current = head;
        for (int i = 0; i < startIndex; ++i) current = current->next;
        for (int i = startIndex; i <= endIndex; ++i) { sub->Append(current->data); current = current->next; }
        return sub;
    }

    int GetLength() const { return length; }

    void Append(T item) {
        Node* newNode = new Node(item);
        if (!head) head = newNode;
        else {
            Node* current = head;
            while (current->next) current = current->next;
            current->next = newNode;
        }
        ++length;
    }

    void Prepend(T item) {
        Node* newNode = new Node(item);
        newNode->next = head;
        head = newNode;
        ++length;
    }

    void InsertAt(T item, int index) {
        if (index < 0 || index > length) throw std::out_of_range("IndexOutOfRange");
        if (index == 0) { Prepend(item); return; }
        Node* newNode = new Node(item);
        Node* current = head;
        for (int i = 0; i < index - 1; ++i) current = current->next;
        newNode->next = current->next;
        current->next = newNode;
        ++length;
    }

    LinkedList<T>* Concat(LinkedList<T>* list) {
        LinkedList<T>* result = new LinkedList<T>(*this);
        Node* current = list->head;
        while (current) { result->Append(current->data); current = current->next; }
        return result;
    }

    LinkedList<T>* Map(T (*f)(const T&)) {
        LinkedList<T>* result = new LinkedList<T>();
        Node* current = head;
        while (current) { result->Append(f(current->data)); current = current->next; }
        return result;
    }

    LinkedList<T>* Where(bool (*pred)(const T&)) {
        LinkedList<T>* result = new LinkedList<T>();
        Node* current = head;
        while (current) {
            if (pred(current->data)) result->Append(current->data);
            current = current->next;
        }
        return result;
    }

    T Reduce(T (*f)(const T&, const T&), T init) {
        T result = init;
        Node* current = head;
        while (current) { result = f(current->data, result); current = current->next; }
        return result;
    }
};