#include <gtest/gtest.h>
#include "mutable_array_sequence.hpp"


class MutableArraySequenceTest : public ::testing::Test {
protected:
    void AssertSequencesEqual(Sequence<int>* seq, const int* expected, int count) {
        ASSERT_EQ(seq->get_size(), count);
        for (int i = 0; i < count; ++i) {
            EXPECT_EQ(seq->get(i), expected[i]);
        }
    }
};

TEST_F(MutableArraySequenceTest, BasicCreation) {
    int data[] = { 1, 2, 3 };
    MutableArraySequence<int> seq(data, 3);
    int expected[] = { 1, 2, 3 };
    AssertSequencesEqual(&seq, expected, 3);
}

TEST_F(MutableArraySequenceTest, Modifications) {
    MutableArraySequence<int> seq;
    seq.append(10);
    seq.prepend(20);
    seq.insert_at(30, 1);

    EXPECT_EQ(seq.get(0), 20);
    EXPECT_EQ(seq.get(1), 30);
    EXPECT_EQ(seq.get(2), 10);
}

TEST_F(MutableArraySequenceTest, Removal) {
    int data[] = { 1, 2, 3, 4 };
    MutableArraySequence<int> seq(data, 4);
    seq.remove_at(1);
    int expected[] = { 1, 3, 4 };
    AssertSequencesEqual(&seq, expected, 3);
}

TEST_F(MutableArraySequenceTest, MapTest) {
    int data[] = { 1, 2, 3 };
    MutableArraySequence<int> seq(data, 3);
    auto* mapped = seq.map([](const int& x) { return x * x; });
    int expected[] = { 1, 4, 9 };
    AssertSequencesEqual(mapped, expected, 3);
    delete mapped;
}

TEST_F(MutableArraySequenceTest, WhereTest) {
    int data[] = { 1, 2, 3, 4, 5, 6 };
    MutableArraySequence<int> seq(data, 6);
    auto* filtered = seq.where([](const int& x) { return x % 2 == 0; });
    int expected[] = { 2, 4, 6 };
    AssertSequencesEqual(filtered, expected, 3);
    delete filtered;
}

TEST_F(MutableArraySequenceTest, ReduceTest) {
    int data[] = { 1, 2, 3, 4 };
    MutableArraySequence<int> seq(data, 4);
    int sum = seq.reduce([](const int& a, const int& b) { return a + b; }, 0);
    EXPECT_EQ(sum, 10);
}

TEST_F(MutableArraySequenceTest, ConcatAndSub) {
    int d1[] = { 1, 2 };
    int d2[] = { 3, 4 };
    MutableArraySequence<int> s1(d1, 2);
    MutableArraySequence<int> s2(d2, 2);

    auto* concatenated = s1.concat(&s2);
    int expected_concat[] = { 1, 2, 3, 4 };
    AssertSequencesEqual(concatenated, expected_concat, 4);

    auto* sub = concatenated->get_subsequence(1, 2);
    int expected_sub[] = { 2, 3 };
    AssertSequencesEqual(sub, expected_sub, 2);

    delete concatenated;
    delete sub;
}

TEST_F(MutableArraySequenceTest, ManualIterator) {
    int data[] = { 10, 20, 30 };
    MutableArraySequence<int> seq(data, 3);
    auto* it = seq.get_enumerator();
    int i = 0;
    while (it->move_next()) {
        EXPECT_EQ(it->get_current(), data[i]);
        i++;
    }
    EXPECT_EQ(i, 3);
    delete it;
}

TEST_F(MutableArraySequenceTest, OptionSafety) {
    MutableArraySequence<int> empty;
    auto opt_empty = empty.try_get_first();
    EXPECT_FALSE(opt_empty.has_value());
    empty.append(100);
    auto opt_full = empty.try_get_first();
    EXPECT_TRUE(opt_full.has_value());
    int val = opt_full.get_value();
    EXPECT_EQ(val, 100);
}