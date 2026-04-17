#include <gtest/gtest.h>
#include "linkedlist.hpp"
#include <stdexcept>

TEST(LinkedListTest, Lifecycle) {
    LinkedList<int> empty;
    EXPECT_EQ(empty.get_size(), 0);
    EXPECT_THROW(empty.get_first(), std::out_of_range);

    int items[] = { 10, 20, 30 };
    LinkedList<int> sized(items, 3);
    EXPECT_EQ(sized.get_size(), 3);
    EXPECT_EQ(sized.get_first(), 10);
    EXPECT_EQ(sized.get_last(), 30);
}

TEST(LinkedListTest, Insertion) {
    LinkedList<int> list;
    list.append(20);
    list.prepend(10);
    list.append(30);

    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list.get_first(), 10);
    EXPECT_EQ(list.get_last(), 30);
}

TEST(LinkedListTest, Deletion) {
    int items[] = { 1, 2, 3 };
    LinkedList<int> list(items, 3);

    list.remove_at(1);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list.get_first(), 1);
    EXPECT_EQ(list.get_last(), 3);

    list.remove_at(0);
    EXPECT_EQ(list.get_first(), 3);
}

TEST(LinkedListTest, SublistVerification) {
    int items[] = { 10, 20, 30, 40 };
    LinkedList<int> list(items, 4);

    LinkedList<int>* sub = list.get_sublist(1, 3);
    EXPECT_EQ(sub->get_size(), 2);
    EXPECT_EQ(sub->get_first(), 20);
    EXPECT_EQ(sub->get_last(), 30);
    delete sub;
}

TEST(LinkedListTest, CopyAndAssignment) {
    int items[] = { 100, 200 };
    LinkedList<int> original(items, 2);

    LinkedList<int> copy(original);
    EXPECT_EQ(copy.get_size(), 2);
    EXPECT_EQ(copy.get_first(), 100);

    LinkedList<int> assigned;
    assigned = original;
    EXPECT_EQ(assigned.get_last(), 200);
}

TEST(LinkedListTest, ExceptionHandling) {
    LinkedList<int> list;
    EXPECT_THROW(list.remove_at(0), std::out_of_range);
    EXPECT_THROW(list.get_sublist(1, 0), std::out_of_range);

    int* null_ptr = nullptr;
    EXPECT_THROW(LinkedList<int> invalid(null_ptr, 5), std::invalid_argument);
}