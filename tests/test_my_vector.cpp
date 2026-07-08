#include <gtest/gtest.h>
#include <vector>

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

TEST(my_vector, SizeConstructorCreatesInitializedElements)
{
	my_vector<int> v(5);

	EXPECT_EQ(v.size(), 5);

	for (int value : v)
		EXPECT_EQ(value, 0);
}

TEST(my_vector, FillConstructorCreatesCopiesOfValue)
{
	my_vector<int> v(5, 42);

	EXPECT_EQ(v.size(), 5);

	for (int value : v)
		EXPECT_EQ(value, 42);
}

TEST(my_vector, MoveAssignmentTransfersOwnership)
{
	my_vector<int> original;

	original.push_back(10);
	original.push_back(20);

	my_vector<int> moved;

	moved = std::move(original);

	EXPECT_EQ(moved.size(), 2);
	EXPECT_EQ(moved[0], 10);
	EXPECT_EQ(moved[1], 20);

	EXPECT_EQ(original.size(), 0);
}

TEST(my_vector, PushBackTriggersReallocation)
{
	my_vector<int> v;

	for (int i = 0; i < 100; ++i)
		v.push_back(i);

	EXPECT_EQ(v.size(), 100);

	for (int i = 0; i < 100; ++i)
		EXPECT_EQ(v[i], i);
}

TEST(my_vector, ResizeIncreasesSize)
{
	my_vector<int> v;

	v.push_back(1);
	v.push_back(2);

	v.resize(5);

	EXPECT_EQ(v.size(), 5);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 2);

	EXPECT_EQ(v[2], 0);
	EXPECT_EQ(v[3], 0);
	EXPECT_EQ(v[4], 0);
}

TEST(my_vector, ResizeDecreasesSize)
{
	my_vector<int> v;

	for (int i = 0; i < 10; ++i)
		v.push_back(i);

	v.resize(3);

	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v[0], 0);
	EXPECT_EQ(v[1], 1);
	EXPECT_EQ(v[2], 2);
}

TEST(my_vector, ClearDestroysElementsAndKeepsCapacity)
{
	my_vector<int> v;

	for (int i = 0; i < 10; ++i)
		v.push_back(i);

	auto old_capacity = v.capacity();

	v.clear();

	EXPECT_TRUE(v.empty());
	EXPECT_EQ(v.capacity(), old_capacity);
}

TEST(my_vector, IteratorTraversesElements)
{
	my_vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	int sum = 0;

	for (auto it = v.begin(); it != v.end(); ++it)
		sum += *it;

	EXPECT_EQ(sum, 6);
}

TEST(my_vector, ReverseIteratorTraversesElementsBackwards)
{
	my_vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	std::vector<int> result;

	for (auto it = v.rbegin(); it != v.rend(); ++it)
		result.push_back(*it);

	EXPECT_EQ(result[0], 3);
	EXPECT_EQ(result[1], 2);
	EXPECT_EQ(result[2], 1);
}

TEST(my_vector, PopBackRemovesLastElement)
{
	my_vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	v.pop_back();

	EXPECT_EQ(v.size(), 2);
	EXPECT_EQ(v.back(), 2);
}