#pragma once
#include <stdexcept>

template <class T>
class Sequence {
public:
    virtual ~Sequence() = default;

    class Iterator {
    public:
        virtual ~Iterator() = default;
        virtual T& operator*() = 0;
        virtual Iterator& operator++() = 0;
        virtual bool operator!=(const Iterator& other) const = 0;
    };

    virtual Iterator* begin() = 0;
    virtual Iterator* end() = 0;

    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual int GetLength() const = 0;

    virtual Sequence<T>* Append(const T& item) = 0;
    virtual Sequence<T>* Prepend(const T& item) = 0;
    virtual Sequence<T>* InsertAt(const T& item, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;

    virtual Sequence<T>* Map(T (*f)(const T&)) {
        int len = GetLength();
        T* items = new T[len];
        for (int i = 0; i < len; ++i)
            items[i] = f(Get(i));
        Sequence<T>* result = CreateInstance(items, len);
        delete[] items;
        return result;
    }

    virtual Sequence<T>* Where(bool (*pred)(const T&)) {
        int len = GetLength();
        T* items = new T[len];
        int newLen = 0;
        for (int i = 0; i < len; ++i) {
            T val = Get(i);
            if (pred(val))
                items[newLen++] = val;
        }
        Sequence<T>* result = CreateInstance(items, newLen);
        delete[] items;
        return result;
    }

    virtual T Reduce(T (*f)(const T&, const T&), T init) {
        T result = init;
        for (int i = 0; i < GetLength(); ++i)
            result = f(Get(i), result);
        return result;
    }

protected:
    virtual Sequence<T>* CreateInstance(T* items, int count) const = 0;
};