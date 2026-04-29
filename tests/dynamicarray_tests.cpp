#include <gtest/gtest.h>
#include "dynamicarray.hpp"
#include <stdexcept>

namespace {
    void FillWithTestData(DynamicArray<int>& arr) {
        for (int i = 0; i < arr.get_size(); ++i) {
            arr.set(i, i * 10);
        }
    }
}


TEST(DynamicArrayTest, Lifecycle) {
    DynamicArray<int> sized(3);
    EXPECT_EQ(sized.get(0), 0);
    EXPECT_EQ(sized.get_size(), 3);

    int data[] = { 1, 2, 3 };
    DynamicArray<int> original(data, 3);
    DynamicArray<int> copy = original;

    copy.set(0, 99);
    EXPECT_EQ(original.get(0), 1);
    EXPECT_EQ(copy.get(0), 99);
}

TEST(DynamicArrayTest, MoveSemantics) {
    int data[] = { 10, 20, 30 };
    DynamicArray<int> source(data, 3);
    DynamicArray<int> moved(std::move(source));

    EXPECT_EQ(moved.get_size(), 3);
    EXPECT_EQ(moved.get(0), 10);
    EXPECT_EQ(source.get_size(), 0);
}

TEST(DynamicArrayTest, ExceptionHandling) {
    DynamicArray<int> arr(5);
    EXPECT_THROW(arr.get(-1), std::out_of_range);


    EXPECT_THROW(arr.get(5), std::out_of_range);
    EXPECT_THROW(arr.set(5, 10), std::out_of_range);

    EXPECT_THROW(DynamicArray<int> negativeSize(-10), std::invalid_argument);
    EXPECT_THROW(DynamicArray<int> nullPtr(nullptr, 1), std::invalid_argument);

    EXPECT_THROW(arr.resize(-1), std::invalid_argument);
    EXPECT_THROW(arr.remove_at(10), std::out_of_range);
}

TEST(DynamicArrayTest, StructuralChanges) {
    DynamicArray<int> arr(3);
    FillWithTestData(arr); // {0, 10, 20}

    arr.remove_at(0);
    EXPECT_EQ(arr.get_size(), 2);
    EXPECT_EQ(arr.get(0), 10);

    arr.resize(5);
    EXPECT_EQ(arr.get_size(), 5);
    EXPECT_EQ(arr.get(4), 0);

    arr.resize(0);
    EXPECT_EQ(arr.get_size(), 0);
}

TEST(DynamicArrayTest, Assignment) {
    DynamicArray<int> a(2);
    a.set(0, 1); a.set(1, 2);

    DynamicArray<int> b;
    b = a;

    EXPECT_EQ(b.get_size(), 2);
    EXPECT_EQ(b.get(0), 1);

    ASSERT_NO_THROW(a = a);
    EXPECT_EQ(a.get_size(), 2);
    EXPECT_EQ(a.get(0), 1);
}

TEST(DynamicArrayTest, NestedArrays) {
    DynamicArray<DynamicArray<int>> matrix(2);
    matrix.set(0, DynamicArray<int>(3));
    matrix.set(1, DynamicArray<int>(2));

    matrix.get(0).set(0, 10);
    matrix.get(0).set(1, 11);
    matrix.get(0).set(2, 12);

    matrix.get(1).set(0, 20);
    matrix.get(1).set(1, 21);

    EXPECT_EQ(matrix.get_size(), 2);
    EXPECT_EQ(matrix.get(0).get_size(), 3);
    EXPECT_EQ(matrix.get(1).get_size(), 2);

    EXPECT_EQ(matrix.get(0).get(1), 11);
    EXPECT_EQ(matrix.get(1).get(0), 20);

    DynamicArray<DynamicArray<int>> matrixCopy = matrix;

    matrixCopy.get(0).set(0, 999);

    EXPECT_EQ(matrixCopy.get(0).get(0), 999);
    EXPECT_EQ(matrix.get(0).get(0), 10);
}