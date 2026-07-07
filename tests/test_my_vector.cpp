#include <gtest/gtest.h>

#include "my_vector.h"
#include "test_utils/tracker.h"

TEST(my_vector, DefaultConstructorCreatesEmptyVector)
{
	my_vector<int> v;

	EXPECT_TRUE(v.empty());
	EXPECT_EQ(v.size(), 0);
	EXPECT_GE(v.capacity(), 0);
}

TEST(my_vector, PushBackStoresElements)
{
	my_vector<int> v;

	v.push_back(10);
	v.push_back(20);
	v.push_back(30);

	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v[0], 10);
	EXPECT_EQ(v[1], 20);
	EXPECT_EQ(v[2], 30);
}

TEST(my_vector, CopyConstructorCreatesIndependentCopy)
{
	my_vector<int> original;

	original.push_back(10);

	my_vector<int> copy(original);

	EXPECT_EQ(copy.size(), original.size());
	EXPECT_EQ(copy[0], 10);

	original[0] = 100;

	EXPECT_EQ(original[0], 100);
	EXPECT_EQ(copy[0], 10);
}

TEST(my_vector, MoveConstructorTransfersOwnership)
{
	my_vector<int> original;

	original.push_back(10);

	my_vector<int> moved(std::move(original));

	EXPECT_EQ(moved.size(), 1);
	EXPECT_EQ(moved[0], 10);

	EXPECT_EQ(original.size(), 0);
}