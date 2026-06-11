#include <gtest/gtest.h>
#include "Stack.h"
#include "Queue.h"
#include "Deque.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "LinkedList.h"
#include "Boolean.h"

// =============================================
// Stack
// =============================================
TEST(StackTest, PushPopPeek) {
    Stack<int> stack(new MutableArraySequence<int>());
    EXPECT_TRUE(stack.IsEmpty());
    EXPECT_EQ(stack.GetLength(), 0);

    stack.Push(10);
    EXPECT_FALSE(stack.IsEmpty());
    EXPECT_EQ(stack.GetLength(), 1);
    EXPECT_EQ(stack.Peek(), 10);

    stack.Push(20);
    EXPECT_EQ(stack.GetLength(), 2);
    EXPECT_EQ(stack.Peek(), 20);

    EXPECT_EQ(stack.Pop(), 20);
    EXPECT_EQ(stack.GetLength(), 1);
    EXPECT_EQ(stack.Peek(), 10);

    EXPECT_EQ(stack.Pop(), 10);
    EXPECT_TRUE(stack.IsEmpty());
}

TEST(StackTest, PopOnEmptyThrows) {
    Stack<int> stack(new MutableArraySequence<int>());
    EXPECT_THROW(stack.Pop(), std::out_of_range);
}

TEST(StackTest, PeekOnEmptyThrows) {
    Stack<int> stack(new MutableArraySequence<int>());
    EXPECT_THROW(stack.Peek(), std::out_of_range);
}

TEST(StackTest, MultiplePushPop) {
    Stack<int> stack(new MutableArraySequence<int>());
    for (int i = 0; i < 100; ++i)
        stack.Push(i);
    EXPECT_EQ(stack.GetLength(), 100);
    EXPECT_EQ(stack.Peek(), 99);

    for (int i = 99; i >= 0; --i)
        EXPECT_EQ(stack.Pop(), i);
    EXPECT_TRUE(stack.IsEmpty());
}

TEST(StackTest, Map) {
    Stack<int> stack(new MutableArraySequence<int>());
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    Stack<int>* result = stack.Map([](const int& x) { return x * x; });
    EXPECT_EQ(result->GetLength(), 3);
    EXPECT_EQ(result->Pop(), 9);
    EXPECT_EQ(result->Pop(), 4);
    EXPECT_EQ(result->Pop(), 1);
    delete result;

    EXPECT_EQ(stack.GetLength(), 3);
    EXPECT_EQ(stack.Peek(), 3);
}

TEST(StackTest, Where) {
    Stack<int> stack(new MutableArraySequence<int>());
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    stack.Push(4);

    Stack<int>* result = stack.Where([](const int& x) { return x % 2 == 0; });
    EXPECT_EQ(result->GetLength(), 2);
    EXPECT_EQ(result->Pop(), 4);
    EXPECT_EQ(result->Pop(), 2);
    delete result;

    EXPECT_EQ(stack.GetLength(), 4);
}

TEST(StackTest, WhereNoMatch) {
    Stack<int> stack(new MutableArraySequence<int>());
    stack.Push(1);
    stack.Push(3);
    stack.Push(5);

    Stack<int>* result = stack.Where([](const int& x) { return x % 2 == 0; });
    EXPECT_EQ(result->GetLength(), 0);
    EXPECT_TRUE(result->IsEmpty());
    delete result;
}

TEST(StackTest, Reduce) {
    Stack<int> stack(new MutableArraySequence<int>());
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    int result = stack.Reduce([](const int& x, const int& acc) { return acc + x; }, 0);
    EXPECT_EQ(result, 6);
}

TEST(StackTest, ReduceProduct) {
    Stack<int> stack(new MutableArraySequence<int>());
    stack.Push(2);
    stack.Push(3);
    stack.Push(4);

    int result = stack.Reduce([](const int& x, const int& acc) { return acc * x; }, 1);
    EXPECT_EQ(result, 24);
}

TEST(StackTest, ReduceEmpty) {
    Stack<int> stack(new MutableArraySequence<int>());
    int result = stack.Reduce([](const int& x, const int& acc) { return acc + x; }, 100);
    EXPECT_EQ(result, 100);
}

TEST(StackTest, Concat) {
    Stack<int> s1(new MutableArraySequence<int>());
    s1.Push(1);
    s1.Push(2);

    Stack<int> s2(new MutableArraySequence<int>());
    s2.Push(3);
    s2.Push(4);

    Stack<int>* result = s1.Concat(&s2);
    EXPECT_EQ(result->GetLength(), 4);
    EXPECT_EQ(result->Pop(), 4);
    EXPECT_EQ(result->Pop(), 3);
    EXPECT_EQ(result->Pop(), 2);
    EXPECT_EQ(result->Pop(), 1);
    delete result;

    EXPECT_EQ(s1.GetLength(), 2);
    EXPECT_EQ(s2.GetLength(), 2);
}

TEST(StackTest, GetSubsequence) {
    Stack<int> stack(new MutableArraySequence<int>());
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    stack.Push(40);

    Stack<int>* sub = stack.GetSubsequence(1, 2);
    EXPECT_EQ(sub->GetLength(), 2);
    EXPECT_EQ(sub->Pop(), 30);
    EXPECT_EQ(sub->Pop(), 20);
    delete sub;

    EXPECT_EQ(stack.GetLength(), 4);
}

TEST(StackTest, ContainsSubsequence) {
    Stack<int> stack(new MutableArraySequence<int>());
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    stack.Push(4);

    int items[] = {2, 3};
    MutableArraySequence<int> sub(items, 2);
    EXPECT_TRUE(stack.ContainsSubsequence(&sub));

    int items2[] = {1, 3};
    MutableArraySequence<int> sub2(items2, 2);
    EXPECT_FALSE(stack.ContainsSubsequence(&sub2));
}

TEST(StackTest, ContainsSubsequenceTooLong) {
    Stack<int> stack(new MutableArraySequence<int>());
    stack.Push(1);

    int items[] = {1, 2, 3};
    MutableArraySequence<int> sub(items, 3);
    EXPECT_FALSE(stack.ContainsSubsequence(&sub));
}

TEST(StackTest, ContainsSubsequenceEmpty) {
    Stack<int> stack(new MutableArraySequence<int>());
    stack.Push(1);

    int items[] = {1};
    MutableArraySequence<int> sub(items, 1);
    EXPECT_TRUE(stack.ContainsSubsequence(&sub));
}

TEST(StackTest, ImmutableSequence) {
    int items[] = {1, 2, 3};
    Stack<int> stack(new ImmutableArraySequence<int>(items, 3));

    EXPECT_EQ(stack.GetLength(), 3);
    EXPECT_EQ(stack.Peek(), 3);

    stack.Push(4);
    EXPECT_EQ(stack.GetLength(), 4);
    EXPECT_EQ(stack.Peek(), 4);
}

TEST(StackTest, ListSequence) {
    int items[] = {10, 20};
    Stack<int> stack(new MutableListSequence<int>(items, 2));

    EXPECT_EQ(stack.GetLength(), 2);
    EXPECT_EQ(stack.Peek(), 20);

    stack.Push(30);
    EXPECT_EQ(stack.GetLength(), 3);
    EXPECT_EQ(stack.Peek(), 30);
    EXPECT_EQ(stack.Pop(), 30);
    EXPECT_EQ(stack.Pop(), 20);
    EXPECT_EQ(stack.Pop(), 10);
}

// =============================================
// Boolean
// =============================================
TEST(BooleanTest, Basic) {
    int items[] = {1, 2, 3};
    MutableArraySequence<int> seq(items, 3);

    Sequence<Sequence<int>*>* result = BuildBoolean(&seq);
    EXPECT_EQ(result->GetLength(), 8);

    bool foundEmpty = false;
    for (int i = 0; i < result->GetLength(); ++i) {
        Sequence<int>* sub = result->Get(i);
        if (sub->GetLength() == 0) foundEmpty = true;
    }
    EXPECT_TRUE(foundEmpty);

    for (int i = 0; i < result->GetLength(); ++i)
        delete result->Get(i);
    delete result;
}

// =============================================
// Queue
// =============================================
TEST(QueueTest, EnqueueDequeue) {
    Queue<int> q(new MutableListSequence<int>());
    EXPECT_TRUE(q.IsEmpty());
    EXPECT_EQ(q.GetLength(), 0);

    q.Enqueue(10);
    EXPECT_FALSE(q.IsEmpty());
    EXPECT_EQ(q.GetLength(), 1);
    EXPECT_EQ(q.Peek(), 10);

    q.Enqueue(20);
    EXPECT_EQ(q.GetLength(), 2);
    EXPECT_EQ(q.Peek(), 10);

    EXPECT_EQ(q.Dequeue(), 10);
    EXPECT_EQ(q.GetLength(), 1);
    EXPECT_EQ(q.Peek(), 20);

    EXPECT_EQ(q.Dequeue(), 20);
    EXPECT_TRUE(q.IsEmpty());
}

TEST(QueueTest, DequeueOnEmptyThrows) {
    Queue<int> q(new MutableListSequence<int>());
    EXPECT_THROW(q.Dequeue(), std::out_of_range);
}

TEST(QueueTest, PeekOnEmptyThrows) {
    Queue<int> q(new MutableListSequence<int>());
    EXPECT_THROW(q.Peek(), std::out_of_range);
}

TEST(QueueTest, FIFOOrder) {
    Queue<int> q(new MutableListSequence<int>());
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    EXPECT_EQ(q.Dequeue(), 1);
    EXPECT_EQ(q.Dequeue(), 2);
    EXPECT_EQ(q.Dequeue(), 3);
}

TEST(QueueTest, Map) {
    Queue<int> q(new MutableListSequence<int>());
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);

    Queue<int>* result = q.Map([](const int& x) { return x * x; });
    EXPECT_EQ(result->GetLength(), 3);
    EXPECT_EQ(result->Dequeue(), 1);
    EXPECT_EQ(result->Dequeue(), 4);
    EXPECT_EQ(result->Dequeue(), 9);
    delete result;
    EXPECT_EQ(q.GetLength(), 3);
}

TEST(QueueTest, Where) {
    Queue<int> q(new MutableListSequence<int>());
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    q.Enqueue(4);

    Queue<int>* result = q.Where([](const int& x) { return x % 2 == 0; });
    EXPECT_EQ(result->GetLength(), 2);
    EXPECT_EQ(result->Dequeue(), 2);
    EXPECT_EQ(result->Dequeue(), 4);
    delete result;
}

TEST(QueueTest, Reduce) {
    Queue<int> q(new MutableListSequence<int>());
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    EXPECT_EQ(q.Reduce([](const int& x, const int& acc) { return acc + x; }, 0), 6);
}

TEST(QueueTest, Concat) {
    Queue<int> q1(new MutableListSequence<int>());
    q1.Enqueue(1);
    q1.Enqueue(2);

    Queue<int> q2(new MutableListSequence<int>());
    q2.Enqueue(3);
    q2.Enqueue(4);

    Queue<int>* result = q1.Concat(&q2);
    EXPECT_EQ(result->GetLength(), 4);
    EXPECT_EQ(result->Dequeue(), 1);
    EXPECT_EQ(result->Dequeue(), 2);
    EXPECT_EQ(result->Dequeue(), 3);
    EXPECT_EQ(result->Dequeue(), 4);
    delete result;
}

TEST(QueueTest, GetSubsequence) {
    Queue<int> q(new MutableListSequence<int>());
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);

    Queue<int>* sub = q.GetSubsequence(0, 1);
    EXPECT_EQ(sub->GetLength(), 2);
    EXPECT_EQ(sub->Dequeue(), 10);
    EXPECT_EQ(sub->Dequeue(), 20);
    delete sub;
}

TEST(QueueTest, ContainsSubsequence) {
    Queue<int> q(new MutableListSequence<int>());
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);

    MutableListSequence<int> sub1(new int[2]{1, 2}, 2);
    EXPECT_TRUE(q.ContainsSubsequence(&sub1));

    MutableListSequence<int> sub2(new int[2]{1, 3}, 2);
    EXPECT_FALSE(q.ContainsSubsequence(&sub2));
}

// =============================================
// Deque
// =============================================
TEST(DequeTest, PushPopFront) {
    Deque<int> d(new MutableListSequence<int>());
    d.PushFront(10);
    d.PushFront(20);
    EXPECT_EQ(d.GetLength(), 2);
    EXPECT_EQ(d.PopFront(), 20);
    EXPECT_EQ(d.PopFront(), 10);
    EXPECT_TRUE(d.IsEmpty());
}

TEST(DequeTest, PushPopBack) {
    Deque<int> d(new MutableListSequence<int>());
    d.PushBack(10);
    d.PushBack(20);
    EXPECT_EQ(d.GetLength(), 2);
    EXPECT_EQ(d.PopBack(), 20);
    EXPECT_EQ(d.PopBack(), 10);
    EXPECT_TRUE(d.IsEmpty());
}

TEST(DequeTest, MixedPushPop) {
    Deque<int> d(new MutableListSequence<int>());
    d.PushFront(1);
    d.PushBack(2);
    d.PushFront(0);
    EXPECT_EQ(d.PeekFront(), 0);
    EXPECT_EQ(d.PeekBack(), 2);
    EXPECT_EQ(d.PopFront(), 0);
    EXPECT_EQ(d.PopBack(), 2);
    EXPECT_EQ(d.PopFront(), 1);
}

TEST(DequeTest, PopFrontOnEmptyThrows) {
    Deque<int> d(new MutableListSequence<int>());
    EXPECT_THROW(d.PopFront(), std::out_of_range);
}

TEST(DequeTest, PopBackOnEmptyThrows) {
    Deque<int> d(new MutableListSequence<int>());
    EXPECT_THROW(d.PopBack(), std::out_of_range);
}

TEST(DequeTest, Map) {
    Deque<int> d(new MutableListSequence<int>());
    d.PushBack(1);
    d.PushBack(2);
    d.PushBack(3);

    Deque<int>* result = d.Map([](const int& x) { return x * 2; });
    EXPECT_EQ(result->GetLength(), 3);
    EXPECT_EQ(result->PopFront(), 2);
    EXPECT_EQ(result->PopFront(), 4);
    EXPECT_EQ(result->PopFront(), 6);
    delete result;
}

TEST(DequeTest, Where) {
    Deque<int> d(new MutableListSequence<int>());
    d.PushBack(1);
    d.PushBack(2);
    d.PushBack(3);
    d.PushBack(4);

    Deque<int>* result = d.Where([](const int& x) { return x > 2; });
    EXPECT_EQ(result->GetLength(), 2);
    EXPECT_EQ(result->PopFront(), 3);
    EXPECT_EQ(result->PopFront(), 4);
    delete result;
}

TEST(DequeTest, Reduce) {
    Deque<int> d(new MutableListSequence<int>());
    d.PushBack(5);
    d.PushBack(10);
    d.PushBack(15);
    EXPECT_EQ(d.Reduce([](const int& x, const int& acc) { return acc + x; }, 0), 30);
}

TEST(DequeTest, Concat) {
    Deque<int> d1(new MutableListSequence<int>());
    d1.PushBack(1);
    d1.PushBack(2);

    Deque<int> d2(new MutableListSequence<int>());
    d2.PushBack(3);
    d2.PushBack(4);

    Deque<int>* result = d1.Concat(&d2);
    EXPECT_EQ(result->GetLength(), 4);
    EXPECT_EQ(result->PopFront(), 1);
    EXPECT_EQ(result->PopFront(), 2);
    EXPECT_EQ(result->PopFront(), 3);
    EXPECT_EQ(result->PopFront(), 4);
    delete result;
}

TEST(DequeTest, GetSubsequence) {
    Deque<int> d(new MutableListSequence<int>());
    d.PushBack(10);
    d.PushBack(20);
    d.PushBack(30);

    Deque<int>* sub = d.GetSubsequence(1, 2);
    EXPECT_EQ(sub->GetLength(), 2);
    EXPECT_EQ(sub->PopFront(), 20);
    EXPECT_EQ(sub->PopFront(), 30);
    delete sub;
}