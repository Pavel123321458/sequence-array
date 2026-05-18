#pragma once
#include "LinkedList.h"

template <class T>
class Queue {
private:
    LinkedList<T>* list;

public:
    Queue(LinkedList<T>* l) : list(l) {}

    ~Queue() { delete list; }
    
    Queue<T>& operator=(const Queue<T>& other) {
    if (this != &other) {
        delete list;
        list = new LinkedList<T>(*other.list);
        }
        return *this;
    }

    void Enqueue(const T& item) { list->Append(item); }

    T Dequeue() {
        if (list->GetLength() == 0) throw std::out_of_range("Queue is empty");
        T value = list->GetFirst();
        int len = list->GetLength();
        if (len == 1) { delete list; list = new LinkedList<T>(); }
        else { auto* sub = list->GetSubList(1, len - 1); delete list; list = sub; }
        return value;
    }

    T Peek() const {
        if (list->GetLength() == 0) throw std::out_of_range("Queue is empty");
        return list->GetFirst();
    }

    bool IsEmpty() const { return list->GetLength() == 0; }
    int GetLength() const { return list->GetLength(); }

    Queue<T>* Map(T (*f)(const T&)) { return new Queue<T>(list->Map(f)); }
    Queue<T>* Where(bool (*p)(const T&)) { return new Queue<T>(list->Where(p)); }
    T Reduce(T (*f)(const T&, const T&), T init) { return list->Reduce(f, init); }
    Queue<T>* Concat(Queue<T>* other) { return new Queue<T>(list->Concat(other->list)); }

    Queue<T>* GetSubsequence(int s, int e) { return new Queue<T>(list->GetSubList(s, e)); }

    bool ContainsSubsequence(LinkedList<T>* sub) {
        int sl = sub->GetLength(), len = list->GetLength();
        if (sl > len) return false;
        for (int i = 0; i <= len - sl; ++i) {
            bool f = true;
            for (int j = 0; j < sl; ++j)
                if (list->Get(i + j) != sub->Get(j)) { f = false; break; }
            if (f) return true;
        }
        return false;
    }
};