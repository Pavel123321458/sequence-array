#pragma once
#include "LinkedList.h"

template <class T>
class Deque {
private:
    LinkedList<T>* list;

public:
    Deque() : list(new LinkedList<T>()) {}

    Deque(LinkedList<T>* l) : list(l) {}

    ~Deque() {
        delete list;
    }

    void PushFront(const T& item) {
        list->Prepend(item);
    }

    void PushBack(const T& item) {
        list->Append(item);
    }

    T PopFront() {
        if (list->GetLength() == 0)
            throw std::out_of_range("Deque is empty");
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

    T PopBack() {
        if (list->GetLength() == 0)
            throw std::out_of_range("Deque is empty");
        T value = list->GetLast();
        int len = list->GetLength();
        if (len == 1) {
            delete list;
            list = new LinkedList<T>();
        } else {
            LinkedList<T>* sub = list->GetSubList(0, len - 2);
            delete list;
            list = sub;
        }
        return value;
    }

    T PeekFront() const {
        if (list->GetLength() == 0)
            throw std::out_of_range("Deque is empty");
        return list->GetFirst();
    }

    T PeekBack() const {
        if (list->GetLength() == 0)
            throw std::out_of_range("Deque is empty");
        return list->GetLast();
    }

    bool IsEmpty() const {
        return list->GetLength() == 0;
    }

    int GetLength() const {
        return list->GetLength();
    }

    Deque<T>* Map(T (*f)(const T&)) {
        int len = list->GetLength();
        Deque<T>* result = new Deque<T>();
        for (int i = 0; i < len; ++i)
            result->PushBack(f(list->Get(i)));
        return result;
    }

    Deque<T>* Where(bool (*pred)(const T&)) {
        int len = list->GetLength();
        Deque<T>* result = new Deque<T>();
        for (int i = 0; i < len; ++i) {
            T val = list->Get(i);
            if (pred(val))
                result->PushBack(val);
        }
        return result;
    }

    T Reduce(T (*f)(const T&, const T&), T init) {
        T result = init;
        for (int i = 0; i < list->GetLength(); ++i)
            result = f(list->Get(i), result);
        return result;
    }

    Deque<T>* Concat(Deque<T>* other) {
        Deque<T>* result = new Deque<T>();
        for (int i = 0; i < list->GetLength(); ++i)
            result->PushBack(list->Get(i));
        for (int i = 0; i < other->list->GetLength(); ++i)
            result->PushBack(other->list->Get(i));
        return result;
    }

    Deque<T>* GetSubsequence(int start, int end) {
        LinkedList<T>* sub = list->GetSubList(start, end);
        return new Deque<T>(sub);
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