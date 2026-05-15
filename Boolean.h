#pragma once
#include "Sequence.h"
#include "MutableArraySequence.h"

template <class T>
Sequence<Sequence<T>*>* BuildBoolean(Sequence<T>* seq) {
    int n = seq->GetLength();
    int total = 1 << n;

    Sequence<T>** subsets = new Sequence<T>*[total];

    for (int mask = 0; mask < total; ++mask) {
        int bits = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i)) bits++;

        T* items = new T[bits];
        int idx = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
                items[idx++] = seq->Get(i);

        subsets[mask] = new MutableArraySequence<T>(items, bits);
        delete[] items;
    }

    auto* result = new MutableArraySequence<Sequence<T>*>(subsets, total);
    delete[] subsets;
    return result;
}