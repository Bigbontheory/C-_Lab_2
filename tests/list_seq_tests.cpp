#include <gtest/gtest.h>
#include "mutable_list_sequence.hpp"


class MutableListSequenceTest : public ::testing::Test {
protected:
    void AssertSequencesEqual(Sequence<int>* seq, const int* expected, int count) {
        ASSERT_EQ(seq->get_size(), count);
        for (int i = 0; i < count; ++i) {
            EXPECT_EQ(seq->get(i), expected[i]);
        }
    }
};

TEST_F(MutableListSequenceTest, CreationFromBuffer) {
    int data[] = { 1, 2, 3, 4, 5 };
    MutableListSequence<int> seq(data, 5);
    int expected[] = { 1, 2, 3, 4, 5 };
    AssertSequencesEqual(&seq, expected, 5);
}

TEST_F(MutableListSequenceTest, AppendPrepend) {
    MutableListSequence<int> seq;
    seq.append(10);
    seq.prepend(20);
    seq.append(30);

    EXPECT_EQ(seq.get(0), 20);
    EXPECT_EQ(seq.get(1), 10);
    EXPECT_EQ(seq.get(2), 30);
    EXPECT_EQ(seq.get_size(), 3);
}

TEST_F(MutableListSequenceTest, InsertAt) {
    int data[] = { 1, 2, 4 };
    MutableListSequence<int> seq(data, 3);
    seq.insert_at(3, 2);

    int expected[] = { 1, 2, 3, 4 };
    AssertSequencesEqual(&seq, expected, 4);
}

TEST_F(MutableListSequenceTest, RemoveAt) {
    int data[] = { 10, 20, 30 };
    MutableListSequence<int> seq(data, 3);
    seq.remove_at(1);

    EXPECT_EQ(seq.get_size(), 2);
    EXPECT_EQ(seq.get(0), 10);
    EXPECT_EQ(seq.get(1), 30);
}

TEST_F(MutableListSequenceTest, GetFirstLast) {
    int data[] = { 5, 10, 15 };
    MutableListSequence<int> seq(data, 3);

    EXPECT_EQ(seq.get_first(), 5);
    EXPECT_EQ(seq.get_last(), 15);
}

TEST_F(MutableListSequenceTest, MapLogic) {
    int data[] = { 1, 2, 3 };
    MutableListSequence<int> seq(data, 3);
    auto* mapped = seq.map([](const int& x) { return x * 10; });

    int expected[] = { 10, 20, 30 };
    AssertSequencesEqual(mapped, expected, 3);
    delete mapped;
}

TEST_F(MutableListSequenceTest, WhereLogic) {
    int data[] = { 1, 2, 3, 4, 5, 6 };
    MutableListSequence<int> seq(data, 6);
    auto* filtered = seq.where([](const int& x) { return x % 2 != 0; });

    int expected[] = { 1, 3, 5 };
    AssertSequencesEqual(filtered, expected, 3);
    delete filtered;
}

TEST_F(MutableListSequenceTest, ReduceLogic) {
    int data[] = { 1, 2, 3, 4 };
    MutableListSequence<int> seq(data, 4);
    int sum = seq.reduce([](const int& a, const int& b) { return a + b; }, 0);

    EXPECT_EQ(sum, 10);
}

TEST_F(MutableListSequenceTest, CloneTest) {
    int data[] = { 7, 8, 9 };
    MutableListSequence<int> seq(data, 3);
    auto* cloned = seq.clone();

    int expected[] = { 7, 8, 9 };
    AssertSequencesEqual(cloned, expected, 3);

    cloned->append(10);
    EXPECT_EQ(seq.get_size(), 3);
    EXPECT_EQ(cloned->get_size(), 4);

    delete cloned;
}

TEST_F(MutableListSequenceTest, IteratorManual) {
    int data[] = { 100, 200 };
    MutableListSequence<int> seq(data, 2);
    auto* it = seq.get_enumerator();

    ASSERT_TRUE(it->move_next());
    EXPECT_EQ(it->get_current(), 100);
    ASSERT_TRUE(it->move_next());
    EXPECT_EQ(it->get_current(), 200);
    ASSERT_FALSE(it->move_next());

    delete it;
}
