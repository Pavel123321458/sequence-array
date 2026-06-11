#pragma once
#include "Sequence.h"
#include "MutableListSequence.h"

template <class T>
class Deque {
private:
    Sequence<T>* data;

public:
    typename Sequence<T>::Iterator* begin() { return data->begin(); }
    typename Sequence<T>::Iterator* end() { return data->end(); }


    Deque(Sequence<T>* seq) : data(seq) {}

    ~Deque() { delete data; }

    void PushFront(const T& item) {
        data = data->Prepend(item);
    }
    void PushBack(const T& item) {
        data = data->Append(item);
    }

    T PopFront() {
        if (data->GetLength() == 0)
            throw std::out_of_range("Deque is empty");
        T value = data->GetFirst();
        int len = data->GetLength();
        if (len == 1) {
            delete data;
            data = new MutableListSequence<T>();
        } else {
            Sequence<T>* newData = data->GetSubsequence(1, len - 1);
            delete data;
            data = newData;
        }
        return value;
    }

    T PopBack() {
        if (data->GetLength() == 0)
            throw std::out_of_range("Deque is empty");
        T value = data->GetLast();
        int len = data->GetLength();
        if (len == 1) {
            delete data;
            data = new MutableListSequence<T>();
        } else {
            Sequence<T>* newData = data->GetSubsequence(0, len - 2);
            delete data;
            data = newData;
        }
        return value;
    }

    T PeekFront() const {
        if (data->GetLength() == 0)
            throw std::out_of_range("Deque is empty");
        return data->GetFirst();
    }
    T PeekBack() const {
        if (data->GetLength() == 0)
            throw std::out_of_range("Deque is empty");
        return data->GetLast();
    }

    bool IsEmpty() const { return data->GetLength() == 0; }
    int GetLength() const { return data->GetLength(); }

    Deque<T>* Map(T (*f)(const T&)) {
        return new Deque<T>(data->Map(f));
    }
    Deque<T>* Where(bool (*p)(const T&)) {
        return new Deque<T>(data->Where(p));
    }
    T Reduce(T (*f)(const T&, const T&), T init) {
        return data->Reduce(f, init);
    }
    Deque<T>* Concat(Deque<T>* other) {
        return new Deque<T>(data->Concat(other->data));
    }
    Deque<T>* GetSubsequence(int s, int e) {
        return new Deque<T>(data->GetSubsequence(s, e));
    }

    bool ContainsSubsequence(Sequence<T>* sub) {
        int sl = sub->GetLength(), len = data->GetLength();
        if (sl > len) return false;
        for (int i = 0; i <= len - sl; ++i) {
            bool f = true;
            for (int j = 0; j < sl; ++j)
                if (data->Get(i + j) != sub->Get(j)) { f = false; break; }
            if (f) return true;
        }
        return false;
    }
};