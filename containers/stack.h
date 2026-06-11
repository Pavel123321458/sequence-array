#pragma once
#include "Sequence.h"
#include "MutableArraySequence.h"

template <class T>
class Stack {
private:
    Sequence<T>* data;

public:
    typename Sequence<T>::Iterator* begin() { return data->begin(); }
    typename Sequence<T>::Iterator* end() { return data->end(); }


    Stack(Sequence<T>* seq) : data(seq) {}

    Stack<T>& operator=(const Stack<T>& other) {
    if (this != &other) {
        delete data;
        int len = other.data->GetLength();
        T* items = new T[len];
        for (int i = 0; i < len; ++i)
            items[i] = other.data->Get(i);
        data = new MutableArraySequence<T>(items, len);
        delete[] items;
        }
        return *this;
    }

    ~Stack() {
        delete data;
    }

    void Push(const T& item) {
        data = data->Append(item);
    }

    T Pop() {
        if (data->GetLength() == 0)
            throw std::out_of_range("Stack is empty");
        T value = data->GetLast();
        int len = data->GetLength();
        if (len == 1) {
            delete data;
            data = new MutableArraySequence<T>();
        } else {
            Sequence<T>* newData = data->GetSubsequence(0, len - 2);
            delete data;
            data = newData;
        }
        return value;
    }

    T Peek() const {
        if (data->GetLength() == 0)
            throw std::out_of_range("Stack is empty");
        return data->GetLast();
    }

    bool IsEmpty() const {
        return data->GetLength() == 0;
    }

    int GetLength() const {
        return data->GetLength();
    }

    Stack<T>* Map(T (*f)(const T&)) {
        return new Stack<T>(data->Map(f));
    }

    Stack<T>* Where(bool (*pred)(const T&)) {
        return new Stack<T>(data->Where(pred));
    }

    T Reduce(T (*f)(const T&, const T&), T init) {
        return data->Reduce(f, init);
    }

    Stack<T>* Concat(Stack<T>* other) {
        int len1 = data->GetLength();
        int len2 = other->data->GetLength();
        T* items = new T[len1 + len2];
        for (int i = 0; i < len1; ++i)
            items[i] = data->Get(i);
        for (int i = 0; i < len2; ++i)
            items[len1 + i] = other->data->Get(i);
        Stack<T>* result = new Stack<T>(new MutableArraySequence<T>(items, len1 + len2));
        delete[] items;
        return result;
    }

    Stack<T>* GetSubsequence(int start, int end) {
        return new Stack<T>(data->GetSubsequence(start, end));
    }

    bool ContainsSubsequence(Sequence<T>* sub) {
        int subLen = sub->GetLength();
        int len = data->GetLength();
        if (subLen > len) return false;
        for (int i = 0; i <= len - subLen; ++i) {
            bool found = true;
            for (int j = 0; j < subLen; ++j) {
                if (data->Get(i + j) != sub->Get(j)) {
                    found = false;
                    break;
                }
            }
            if (found) return true;
        }
        return false;
    }
};