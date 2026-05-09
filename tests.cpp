#include <gtest/gtest.h>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"

// =============================================
// DynamicArray
// =============================================
TEST(DynamicArrayTest, ConstructorFromArray) {
    int items[] = {10, 20, 30};
    DynamicArray<int> a(items, 3);
    EXPECT_EQ(a.GetSize(), 3);
    EXPECT_EQ(a.Get(0), 10);
    EXPECT_EQ(a.Get(2), 30);
}

TEST(DynamicArrayTest, ConstructorSize) {
    DynamicArray<int> a(3);
    EXPECT_EQ(a.GetSize(), 3);
}

TEST(DynamicArrayTest, CopyConstructor) {
    int items[] = {1, 2, 3};
    DynamicArray<int> a(items, 3);
    DynamicArray<int> b(a);
    EXPECT_EQ(b.GetSize(), 3);
    EXPECT_EQ(b.Get(1), 2);
}

TEST(DynamicArrayTest, GetThrowsOnNegativeIndex) {
    int items[] = {1, 2};
    DynamicArray<int> a(items, 2);
    EXPECT_THROW(a.Get(-1), std::out_of_range);
}

TEST(DynamicArrayTest, GetThrowsOnTooLargeIndex) {
    int items[] = {1, 2};
    DynamicArray<int> a(items, 2);
    EXPECT_THROW(a.Get(2), std::out_of_range);
}

TEST(DynamicArrayTest, Set) {
    int items[] = {1, 2, 3};
    DynamicArray<int> a(items, 3);
    a.Set(0, 100);
    EXPECT_EQ(a.Get(0), 100);
}

TEST(DynamicArrayTest, SetThrows) {
    int items[] = {1, 2};
    DynamicArray<int> a(items, 2);
    EXPECT_THROW(a.Set(-1, 0), std::out_of_range);
    EXPECT_THROW(a.Set(2, 0), std::out_of_range);
}

TEST(DynamicArrayTest, ResizeGrow) {
    int items[] = {1, 2};
    DynamicArray<int> a(items, 2);
    a.Resize(4);
    EXPECT_EQ(a.GetSize(), 4);
    EXPECT_EQ(a.Get(0), 1);
    EXPECT_EQ(a.Get(1), 2);
}

TEST(DynamicArrayTest, ResizeShrink) {
    int items[] = {1, 2, 3};
    DynamicArray<int> a(items, 3);
    a.Resize(1);
    EXPECT_EQ(a.GetSize(), 1);
    EXPECT_EQ(a.Get(0), 1);
}

// =============================================
// LinkedList
// =============================================
TEST(LinkedListTest, ConstructorFromArray) {
    int items[] = {1, 2, 3};
    LinkedList<int> l(items, 3);
    EXPECT_EQ(l.GetLength(), 3);
}

TEST(LinkedListTest, EmptyConstructor) {
    LinkedList<int> l;
    EXPECT_EQ(l.GetLength(), 0);
}

TEST(LinkedListTest, CopyConstructor) {
    int items[] = {1, 2, 3};
    LinkedList<int> l(items, 3);
    LinkedList<int> copy(l);
    EXPECT_EQ(copy.GetLength(), 3);
    EXPECT_EQ(copy.Get(1), 2);
}

TEST(LinkedListTest, GetFirst) {
    int items[] = {10, 20};
    LinkedList<int> l(items, 2);
    EXPECT_EQ(l.GetFirst(), 10);
}

TEST(LinkedListTest, GetFirstThrowsOnEmpty) {
    LinkedList<int> l;
    EXPECT_THROW(l.GetFirst(), std::out_of_range);
}

TEST(LinkedListTest, GetLast) {
    int items[] = {10, 20, 30};
    LinkedList<int> l(items, 3);
    EXPECT_EQ(l.GetLast(), 30);
}

TEST(LinkedListTest, GetLastThrowsOnEmpty) {
    LinkedList<int> l;
    EXPECT_THROW(l.GetLast(), std::out_of_range);
}

TEST(LinkedListTest, Get) {
    int items[] = {10, 20, 30};
    LinkedList<int> l(items, 3);
    EXPECT_EQ(l.Get(0), 10);
    EXPECT_EQ(l.Get(2), 30);
}

TEST(LinkedListTest, GetThrows) {
    int items[] = {1, 2};
    LinkedList<int> l(items, 2);
    EXPECT_THROW(l.Get(-1), std::out_of_range);
    EXPECT_THROW(l.Get(2), std::out_of_range);
}

TEST(LinkedListTest, GetSubList) {
    int items[] = {1, 2, 3, 4, 5};
    LinkedList<int> l(items, 5);
    LinkedList<int>* sub = l.GetSubList(1, 3);
    EXPECT_EQ(sub->GetLength(), 3);
    EXPECT_EQ(sub->Get(0), 2);
    EXPECT_EQ(sub->Get(2), 4);
    delete sub;
}

TEST(LinkedListTest, GetSubListThrows) {
    int items[] = {1, 2};
    LinkedList<int> l(items, 2);
    EXPECT_THROW(l.GetSubList(-1, 1), std::out_of_range);
    EXPECT_THROW(l.GetSubList(0, 5), std::out_of_range);
}

TEST(LinkedListTest, Append) {
    LinkedList<int> l;
    l.Append(10);
    EXPECT_EQ(l.GetLength(), 1);
    EXPECT_EQ(l.GetFirst(), 10);
    l.Append(20);
    EXPECT_EQ(l.GetLength(), 2);
    EXPECT_EQ(l.GetLast(), 20);
}

TEST(LinkedListTest, Prepend) {
    LinkedList<int> l;
    l.Prepend(10);
    EXPECT_EQ(l.GetFirst(), 10);
    l.Prepend(5);
    EXPECT_EQ(l.GetFirst(), 5);
    EXPECT_EQ(l.GetLength(), 2);
}

TEST(LinkedListTest, InsertAt) {
    int items[] = {1, 3};
    LinkedList<int> l(items, 2);
    l.InsertAt(2, 1);
    EXPECT_EQ(l.GetLength(), 3);
    EXPECT_EQ(l.Get(1), 2);
    l.InsertAt(0, 0);
    EXPECT_EQ(l.GetFirst(), 0);
    EXPECT_EQ(l.GetLength(), 4);
}

TEST(LinkedListTest, InsertAtThrows) {
    LinkedList<int> l;
    EXPECT_THROW(l.InsertAt(0, -1), std::out_of_range);
    EXPECT_THROW(l.InsertAt(0, 1), std::out_of_range);
}

TEST(LinkedListTest, Concat) {
    int items1[] = {1, 2};
    int items2[] = {3, 4};
    LinkedList<int> l1(items1, 2);
    LinkedList<int> l2(items2, 2);
    LinkedList<int>* cat = l1.Concat(&l2);
    EXPECT_EQ(cat->GetLength(), 4);
    EXPECT_EQ(cat->Get(0), 1);
    EXPECT_EQ(cat->Get(3), 4);
    delete cat;
}

// =============================================
// MutableArraySequence
// =============================================
TEST(MutableArraySequenceTest, GetFirstGetLast) {
    int items[] = {1, 2, 3};
    MutableArraySequence<int> seq(items, 3);
    EXPECT_EQ(seq.GetFirst(), 1);
    EXPECT_EQ(seq.GetLast(), 3);
}

TEST(MutableArraySequenceTest, GetFirstThrowsOnEmpty) {
    MutableArraySequence<int> seq;
    EXPECT_THROW(seq.GetFirst(), std::out_of_range);
}

TEST(MutableArraySequenceTest, Get) {
    int items[] = {10, 20, 30};
    MutableArraySequence<int> seq(items, 3);
    EXPECT_EQ(seq.Get(1), 20);
}

TEST(MutableArraySequenceTest, GetThrows) {
    int items[] = {1, 2};
    MutableArraySequence<int> seq(items, 2);
    EXPECT_THROW(seq.Get(-1), std::out_of_range);
    EXPECT_THROW(seq.Get(2), std::out_of_range);
}

TEST(MutableArraySequenceTest, GetSubsequence) {
    int items[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int> seq(items, 5);
    Sequence<int>* sub = seq.GetSubsequence(1, 3);
    EXPECT_EQ(sub->GetLength(), 3);
    EXPECT_EQ(sub->Get(0), 2);
    EXPECT_EQ(sub->Get(2), 4);
    delete sub;
}

TEST(MutableArraySequenceTest, AppendMutable) {
    MutableArraySequence<int> seq;
    seq.Append(10);
    EXPECT_EQ(seq.GetLength(), 1);
    EXPECT_EQ(seq.GetFirst(), 10);
    seq.Append(20);
    EXPECT_EQ(seq.GetLength(), 2);
    EXPECT_EQ(seq.GetLast(), 20);
}

TEST(MutableArraySequenceTest, Prepend) {
    int items[] = {2, 3};
    MutableArraySequence<int> seq(items, 2);
    seq.Prepend(1);
    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.GetFirst(), 1);
}

TEST(MutableArraySequenceTest, InsertAt) {
    int items[] = {1, 3};
    MutableArraySequence<int> seq(items, 2);
    seq.InsertAt(2, 1);
    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.Get(1), 2);
}

TEST(MutableArraySequenceTest, Concat) {
    int items1[] = {1, 2};
    int items2[] = {3, 4};
    MutableArraySequence<int> s1(items1, 2);
    MutableArraySequence<int> s2(items2, 2);
    s1.Concat(&s2);
    EXPECT_EQ(s1.GetLength(), 4);
    EXPECT_EQ(s1.Get(3), 4);
}

// =============================================
// ImmutableArraySequence
// =============================================
TEST(ImmutableArraySequenceTest, AppendDoesNotChangeOriginal) {
    int items[] = {1, 2, 3};
    ImmutableArraySequence<int> seq(items, 3);
    Sequence<int>* app = seq.Append(99);
    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(app->GetLength(), 4);
    EXPECT_EQ(app->GetLast(), 99);
    EXPECT_EQ(seq.GetLast(), 3);
    delete app;
}

TEST(ImmutableArraySequenceTest, PrependDoesNotChangeOriginal) {
    int items[] = {2, 3};
    ImmutableArraySequence<int> seq(items, 2);
    Sequence<int>* pre = seq.Prepend(1);
    EXPECT_EQ(seq.GetLength(), 2);
    EXPECT_EQ(pre->GetLength(), 3);
    EXPECT_EQ(pre->GetFirst(), 1);
    EXPECT_EQ(seq.GetFirst(), 2);
    delete pre;
}

TEST(ImmutableArraySequenceTest, InsertAtDoesNotChangeOriginal) {
    int items[] = {1, 3};
    ImmutableArraySequence<int> seq(items, 2);
    Sequence<int>* ins = seq.InsertAt(2, 1);
    EXPECT_EQ(seq.GetLength(), 2);
    EXPECT_EQ(ins->GetLength(), 3);
    EXPECT_EQ(ins->Get(1), 2);
    EXPECT_EQ(seq.Get(1), 3);
    delete ins;
}

TEST(ImmutableArraySequenceTest, ConcatDoesNotChangeOriginal) {
    int items1[] = {1, 2};
    int items2[] = {3, 4};
    ImmutableArraySequence<int> s1(items1, 2);
    ImmutableArraySequence<int> s2(items2, 2);
    Sequence<int>* cat = s1.Concat(&s2);
    EXPECT_EQ(s1.GetLength(), 2);
    EXPECT_EQ(cat->GetLength(), 4);
    delete cat;
}

// =============================================
// MutableListSequence
// =============================================
TEST(MutableListSequenceTest, BasicOperations) {
    int items[] = {1, 2, 3};
    MutableListSequence<int> seq(items, 3);
    EXPECT_EQ(seq.GetFirst(), 1);
    EXPECT_EQ(seq.GetLast(), 3);
    EXPECT_EQ(seq.GetLength(), 3);
}

TEST(MutableListSequenceTest, AppendPrependInsert) {
    MutableListSequence<int> seq;
    seq.Append(3);
    seq.Prepend(1);
    seq.InsertAt(2, 1);
    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 2);
    EXPECT_EQ(seq.Get(2), 3);
}

// =============================================
// ImmutableListSequence
// =============================================
TEST(ImmutableListSequenceTest, AppendDoesNotChangeOriginal) {
    int items[] = {1, 2};
    ImmutableListSequence<int> seq(items, 2);
    Sequence<int>* app = seq.Append(3);
    EXPECT_EQ(seq.GetLength(), 2);
    EXPECT_EQ(app->GetLength(), 3);
    delete app;
}

TEST(ImmutableListSequenceTest, PrependDoesNotChangeOriginal) {
    int items[] = {2, 3};
    ImmutableListSequence<int> seq(items, 2);
    Sequence<int>* pre = seq.Prepend(1);
    EXPECT_EQ(seq.GetLength(), 2);
    EXPECT_EQ(pre->GetFirst(), 1);
    delete pre;
}

TEST(ImmutableListSequenceTest, concatWithNullptr) {
    int items[] = {1, 2, 3};
    ImmutableListSequence<int> seq(items, 3);
    EXPECT_THROW(seq.Concat(nullptr), std::invalid_argument);
}