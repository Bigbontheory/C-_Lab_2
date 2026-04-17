#include <gtest/gtest.h>
#include "mutable_list_sequence.hpp"

TEST(SequenceBuilderTest, BuildMutableListSequence) {
    
    MutableListSequence<int> proto;
    ISequenceBuilder<int>* builder = proto.create_builder();


    builder->append(10);
    builder->append(20);
    builder->append(30);

    Sequence<int>* result = builder->build();

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->get_size(), 3);
    EXPECT_EQ(result->get(0), 10);
    EXPECT_EQ(result->get(1), 20);
    EXPECT_EQ(result->get(2), 30);

    
    delete builder; 
    delete result;
}