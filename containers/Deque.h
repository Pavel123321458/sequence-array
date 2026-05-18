#pragma once
#include "LinkedList.h"

template <class T>
class Deque {
private:
    LinkedList<T>* list;

public:
    Deque(LinkedList<T>* l) : list(l) {}

    ~Deque() { delete list; }

    Deque<T>& operator=(const Deque<T>& other) {
    if (this != &other) {
        delete list;
        list = new LinkedList<T>(*other.list);
        }
        return *this;
    }

    void PushFront(const T& item) { list->Prepend(item); }
    void PushBack(const T& item) { list->Append(item); }

    T PopFront() {
        if (list->GetLength() == 0) throw std::out_of_range("Deque is empty");
        T v = list->GetFirst();
        int len = list->GetLength();
        if (len == 1) { delete list; list = new LinkedList<T>(); }
        else { auto* s = list->GetSubList(1, len - 1); delete list; list = s; }
        return v;
    }

    T PopBack() {
        if (list->GetLength() == 0) throw std::out_of_range("Deque is empty");
        T v = list->GetLast();
        int len = list->GetLength();
        if (len == 1) { delete list; list = new LinkedList<T>(); }
        else { auto* s = list->GetSubList(0, len - 2); delete list; list = s; }
        return v;
    }

    T PeekFront() const {
        if (list->GetLength() == 0) throw std::out_of_range("Deque is empty");
        return list->GetFirst();
    }
    T PeekBack() const {
        if (list->GetLength() == 0) throw std::out_of_range("Deque is empty");
        return list->GetLast();
    }

    bool IsEmpty() const { return list->GetLength() == 0; }
    int GetLength() const { return list->GetLength(); }

    Deque<T>* Map(T (*f)(const T&)) { return new Deque<T>(list->Map(f)); }
    Deque<T>* Where(bool (*p)(const T&)) { return new Deque<T>(list->Where(p)); }
    T Reduce(T (*f)(const T&, const T&), T init) { return list->Reduce(f, init); }
    Deque<T>* Concat(Deque<T>* other) { return new Deque<T>(list->Concat(other->list)); }

    Deque<T>* GetSubsequence(int s, int e) { return new Deque<T>(list->GetSubList(s, e)); }

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