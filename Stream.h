#pragma once
#include "Sequence.h"
#include "MutableArraySequence.h"
#include <stdexcept>
#include <string>

template <class T>
class ReadOnlyStream {
private:
    Sequence<T>* source;
    size_t position;
    bool ownsSource;

public:
    ReadOnlyStream(Sequence<T>* seq, bool own = true)
        : source(seq), position(0), ownsSource(own) {}

    ~ReadOnlyStream() {
        if (ownsSource) delete source;
    }

    bool IsEndOfStream() const {
        return position >= (size_t)source->GetLength();
    }

    T Read() {
        if (IsEndOfStream())
            throw std::out_of_range("EndOfStream: cannot read");
        return source->Get(position++);
    }

    size_t GetPosition() const {
        return position;
    }

    bool IsCanSeek() const {
        return true;
    }

    size_t Seek(size_t index) {
        if (index < (size_t)source->GetLength()) {
            position = index;
            return position;
        }
        throw std::out_of_range("Cannot seek: index out of range");
    }

    void Open() {}
    void Close() {}
};

template <class T>
class WriteOnlyStream {
private:
    Sequence<T>* dest;
    bool ownsDest;

public:
    WriteOnlyStream() : dest(new MutableArraySequence<T>()), ownsDest(true) {}

    WriteOnlyStream(Sequence<T>* seq, bool own = true)
        : dest(seq), ownsDest(own) {}

    ~WriteOnlyStream() {
        if (ownsDest) delete dest;
    }

    size_t Write(const T& item) {
        dest = dest->Append(item);
        return dest->GetLength();
    }

    size_t GetPosition() const {
        return dest->GetLength();
    }

    Sequence<T>* GetSequence() const {
        return dest;
    }

    void Open() {}
    void Close() {}
};
