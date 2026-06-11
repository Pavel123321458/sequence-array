#pragma once
#include "Sequence.h"
#include "MutableListSequence.h"

template <class T>
class Queue {
private:
    Sequence<T>* data;
public:
    typename Sequence<T>::Iterator* begin() { return data->begin(); }
    typename Sequence<T>::Iterator* end() { return data->end(); }


    Queue(Sequence<T>* seq) : data(seq) {}

    ~Queue() { delete data; }

    void Enqueue(const T& item) {
        data = data->Append(item);
    }

    T Dequeue() {
        if (data->GetLength() == 0)
            throw std::out_of_range("Queue is empty");
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

    T Peek() const {
        if (data->GetLength() == 0)
            throw std::out_of_range("Queue is empty");
        return data->GetFirst();
    }

    bool IsEmpty() const { return data->GetLength() == 0; }
    int GetLength() const { return data->GetLength(); }

    Queue<T>* Map(T (*f)(const T&)) {
        return new Queue<T>(data->Map(f));
    }
    Queue<T>* Where(bool (*p)(const T&)) {
        return new Queue<T>(data->Where(p));
    }
    T Reduce(T (*f)(const T&, const T&), T init) {
        return data->Reduce(f, init);
    }
    Queue<T>* Concat(Queue<T>* other) {
        return new Queue<T>(data->Concat(other->data));
    }
    Queue<T>* GetSubsequence(int s, int e) {
        return new Queue<T>(data->GetSubsequence(s, e));
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