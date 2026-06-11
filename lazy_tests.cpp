#include <gtest/gtest.h>
#include "LazySequence.h"
#include "LazySequenceFactory.h"
#include "Stream.h"


// =============================================
// LazySequence
// =============================================
TEST(LazySequenceTest, Factorial) {
    LazySequence<int>* seq = FactorialSequence();
    EXPECT_EQ(seq->Get(0), 1);
    EXPECT_EQ(seq->Get(1), 1);
    EXPECT_EQ(seq->Get(2), 2);
    EXPECT_EQ(seq->Get(3), 6);
    EXPECT_EQ(seq->Get(4), 24);
    EXPECT_EQ(seq->Get(5), 120);
    delete seq;
}

TEST(LazySequenceTest, Fibonacci) {
    LazySequence<int>* seq = FibonacciSequence();
    EXPECT_EQ(seq->Get(0), 0);
    EXPECT_EQ(seq->Get(1), 1);
    EXPECT_EQ(seq->Get(2), 1);
    EXPECT_EQ(seq->Get(3), 2);
    EXPECT_EQ(seq->Get(4), 3);
    EXPECT_EQ(seq->Get(5), 5);
    EXPECT_EQ(seq->Get(6), 8);
    delete seq;
}

TEST(LazySequenceTest, NaturalNumbers) {
    LazySequence<int>* seq = NaturalNumbers();
    EXPECT_EQ(seq->Get(0), 1);
    EXPECT_EQ(seq->Get(9), 10);
    EXPECT_EQ(seq->Get(99), 100);
    delete seq;
}

TEST(LazySequenceTest, Memoization) {
    LazySequence<int>* seq = FibonacciSequence();
    EXPECT_EQ(seq->GetMaterializedCount(), 2);
    seq->Get(5);
    EXPECT_EQ(seq->GetMaterializedCount(), 6);
    seq->Get(5);
    EXPECT_EQ(seq->GetMaterializedCount(), 6);
    delete seq;
}

// =============================================
// Stream
// =============================================
TEST(StreamTest, ReadOnlyStream) {
    int items[] = {10, 20, 30, 40, 50};
    MutableArraySequence<int>* seq = new MutableArraySequence<int>(items, 5);
    ReadOnlyStream<int> stream(seq);

    EXPECT_FALSE(stream.IsEndOfStream());
    EXPECT_EQ(stream.GetPosition(), 0);
    EXPECT_EQ(stream.Read(), 10);
    EXPECT_EQ(stream.Read(), 20);
    EXPECT_EQ(stream.GetPosition(), 2);
    EXPECT_EQ(stream.Read(), 30);
    EXPECT_EQ(stream.Read(), 40);
    EXPECT_FALSE(stream.IsEndOfStream());
    EXPECT_EQ(stream.Read(), 50);
    EXPECT_TRUE(stream.IsEndOfStream());
}

TEST(StreamTest, ReadEndOfStreamThrows) {
    int items[] = {1};
    MutableArraySequence<int>* seq = new MutableArraySequence<int>(items, 1);
    ReadOnlyStream<int> stream(seq);
    stream.Read();
    EXPECT_THROW(stream.Read(), std::out_of_range);
}

TEST(StreamTest, Seek) {
    int items[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int>* seq = new MutableArraySequence<int>(items, 5);
    ReadOnlyStream<int> stream(seq);
    stream.Seek(3);
    EXPECT_EQ(stream.GetPosition(), 3);
    EXPECT_EQ(stream.Read(), 4);
}

TEST(StreamTest, WriteOnlyStream) {
    WriteOnlyStream<int> stream;
    EXPECT_EQ(stream.GetPosition(), 0);
    stream.Write(100);
    EXPECT_EQ(stream.GetPosition(), 1);
    stream.Write(200);
    EXPECT_EQ(stream.GetPosition(), 2);
    Sequence<int>* seq = stream.GetData();    EXPECT_EQ(seq->Get(0), 100);
    EXPECT_EQ(seq->Get(1), 200);
}

TEST(StreamTest, RLEEncoding) {
    char items[] = {'A', 'A', 'A', 'B', 'B', 'C', 'C', 'C', 'C'};
    MutableArraySequence<char>* seq = new MutableArraySequence<char>(items, 9);
    ReadOnlyStream<char> stream(seq);
    std::string encoded = EncodeRLE(&stream);
    EXPECT_EQ(encoded, "3A2B4C");
}