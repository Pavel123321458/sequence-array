#pragma once
#include "Sequence.h"
#include "MutableArraySequence.h"
#include <stdexcept>
#include <string>

template <class T>
class Stream {
protected:
    size_t position;
    bool isOpen;
    Sequence<T>* data;       // общий указатель на данные (источник или приёмник)
    bool ownsData;

public:
    Stream() : position(0), isOpen(false), data(nullptr), ownsData(false) {}
    Stream(Sequence<T>* seq, bool own = true) : position(0), isOpen(false), data(seq), ownsData(own) {}
    virtual ~Stream() { if (ownsData) delete data; }

    size_t GetPosition() const { return position; }
    bool IsOpen() const { return isOpen; }
    Sequence<T>* GetData() const { return data; }

    virtual void Open() { isOpen = true; }
    virtual void Close() { isOpen = false; }
    virtual bool IsEndOfStream() const = 0;
};

template <class T>
class ReadOnlyStream : public Stream<T> {
public:
    ReadOnlyStream(Sequence<T>* seq, bool own = true) : Stream<T>(seq, own) {}

    bool IsEndOfStream() const override {
        return this->position >= (size_t)this->data->GetLength();
    }

    T Read() {
        if (IsEndOfStream()) throw std::out_of_range("EndOfStream");
        return this->data->Get(this->position++);
    }

    bool IsCanSeek() const { return true; }

    size_t Seek(size_t index) {
        if (index < (size_t)this->data->GetLength()) {
            this->position = index;
            return this->position;
        }
        throw std::out_of_range("Cannot seek");
    }
};

template <class T>
class WriteOnlyStream : public Stream<T> {
public:
    WriteOnlyStream() : Stream<T>(new MutableArraySequence<T>(), true) {}

    WriteOnlyStream(Sequence<T>* seq, bool own = true) : Stream<T>(seq, own) {}

    bool IsEndOfStream() const override { return false; }

    size_t Write(const T& item) {
        this->data = this->data->Append(item);
        this->position = this->data->GetLength();
        return this->position;
    }
};

// RLE кодирование
std::string EncodeRLE(ReadOnlyStream<char>* input) {
    std::string result;
    while (!input->IsEndOfStream()) {
        char c = input->Read();
        int count = 1;
        while (!input->IsEndOfStream() && count < 9) {
            size_t pos = input->GetPosition();
            char next = input->Read();
            if (next == c) { count++; }
            else { input->Seek(pos); break; }
        }
        result += std::to_string(count) + c;
    }
    return result;
}