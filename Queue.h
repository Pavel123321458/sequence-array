#pragma once
#include "LinkedList.h"

template <class T>
class Queue {
private:
    LinkedList<T>* list;

public:
    Queue() : list(new LinkedList<T>()) {}

    Queue(LinkedList<T>* l) : list(l) {}

    ~Queue() {
        delete list;
    }

    void Enqueue(const T& item) {
        list->Append(item);
    }

    T Dequeue() {
        if (list->GetLength() == 0)
            throw std::out_of_range("Queue is empty");
        T value = list->GetFirst();
        int len = list->GetLength();
        if (len == 1) {
            delete list;
            list = new LinkedList<T>();
        } else {
            LinkedList<T>* sub = list->GetSubList(1, len - 1);
            delete list;
            list = sub;
        }
        return value;
    }

    T Peek() const {
        if (list->GetLength() == 0)
            throw std::out_of_range("Queue is empty");
        return list->GetFirst();
    }

    bool IsEmpty() const {
        return list->GetLength() == 0;
    }

    int GetLength() const {
        return list->GetLength();
    }

    Queue<T>* Map(T (*f)(const T&)) {
        int len = list->GetLength();
        Queue<T>* result = new Queue<T>();
        for (int i = 0; i < len; ++i)
            result->Enqueue(f(list->Get(i)));
        return result;
    }

    Queue<T>* Where(bool (*pred)(const T&)) {
        int len = list->GetLength();
        Queue<T>* result = new Queue<T>();
        for (int i = 0; i < len; ++i) {
            T val = list->Get(i);
            if (pred(val))
                result->Enqueue(val);
        }
        return result;
    }

    T Reduce(T (*f)(const T&, const T&), T init) {
        T result = init;
        for (int i = 0; i < list->GetLength(); ++i)
            result = f(list->Get(i), result);
        return result;
    }

    Queue<T>* Concat(Queue<T>* other) {
        Queue<T>* result = new Queue<T>();
        for (int i = 0; i < list->GetLength(); ++i)
            result->Enqueue(list->Get(i));
        for (int i = 0; i < other->list->GetLength(); ++i)
            result->Enqueue(other->list->Get(i));
        return result;
    }

    Queue<T>* GetSubsequence(int start, int end) {
        LinkedList<T>* sub = list->GetSubList(start, end);
        return new Queue<T>(sub);
    }

    bool ContainsSubsequence(LinkedList<T>* sub) {
        int subLen = sub->GetLength();
        int len = list->GetLength();
        if (subLen > len) return false;
        for (int i = 0; i <= len - subLen; ++i) {
            bool found = true;
            for (int j = 0; j < subLen; ++j) {
                if (list->Get(i + j) != sub->Get(j)) {
                    found = false;
                    break;
                }
            }
            if (found) return true;
        }
        return false;
    }
};