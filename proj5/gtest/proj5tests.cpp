#include <vector>
#include <gtest/gtest.h>
#include "proj5.hpp"
#include "MyPriorityQueue.hpp"
#include "../include/ver.hpp"
#include <iostream>

namespace{

// As always, this is a STARTING POINT of test cases
	// and is not an exhaustive set of test cases.
	// You should be sure to test EVERY function of 
	// your priority queue as well as the creation of MSTs.l


TEST(SampleTests, SimplePQ)
{
	MyPriorityQueue<int> mpq;
	mpq.insert(3);
	EXPECT_TRUE(mpq.min() == 3);
}

TEST(SampleTests, SimplePQ1)
{
	MyPriorityQueue<int> mpq;
	mpq.insert(1);
	mpq.insert(2);
	mpq.insert(3);
	EXPECT_EQ(mpq.size(),3);
	ASSERT_FALSE(mpq.isEmpty());
	EXPECT_EQ(mpq.min(),1);
}

TEST(SampleTests, SimplePQ2)
{
	MyPriorityQueue<int> mpq;
	ASSERT_TRUE(mpq.isEmpty());
	mpq.insert(5);
	mpq.insert(4);
	EXPECT_EQ(mpq.size(),2);
	ASSERT_FALSE(mpq.isEmpty());
	EXPECT_EQ(mpq.min(),4);
	auto vec = mpq.vectorHeap();
	std::vector<int> expected{4,5};
	ASSERT_EQ(vec, expected);
	// mpq.printPQ();
}

TEST(SampleTests, SimplePQ3Const)
{
	const MyPriorityQueue<int> mpq;
	ASSERT_THROW(mpq.min(), PriorityQueueEmptyException);
}

TEST(SampleTests, SimplePQ3)
{
	MyPriorityQueue<int> mpq;
	ASSERT_TRUE(mpq.isEmpty());
	mpq.insert(1);
	mpq.insert(3);
	mpq.insert(6);
	mpq.insert(5);
	mpq.insert(9);
	mpq.insert(8);
	mpq.insert(-2);
	EXPECT_EQ(mpq.size(),7);
	ASSERT_FALSE(mpq.isEmpty());
	EXPECT_EQ(mpq.min(),-2);
	auto vec = mpq.vectorHeap();
	std::vector<int> expected{-2,3,1,5,9,8,6};
	ASSERT_EQ(vec, expected);
	// mpq.printPQ();
}

TEST(SampleTests, ExtractMin1)
{
	MyPriorityQueue<int> mpq;
	ASSERT_TRUE(mpq.isEmpty());
	mpq.insert(0);
	mpq.insert(1);
	mpq.insert(2);
	mpq.insert(3);
	mpq.insert(4);
	mpq.insert(5);
	mpq.insert(6);
	EXPECT_EQ(mpq.size(),7);
	ASSERT_FALSE(mpq.isEmpty());
	EXPECT_EQ(mpq.min(),0);
	auto vec = mpq.vectorHeap();
	std::vector<int> expected{0,1,2,3,4,5,6};
	ASSERT_EQ(vec, expected);
	mpq.extractMin();
	EXPECT_EQ(mpq.size(),6);
	EXPECT_EQ(mpq.min(),1);
	vec = mpq.vectorHeap();
	expected = {1,3,2,6,4,5};
	ASSERT_EQ(vec, expected);
}

TEST(SampleTests, ExtractMin2)
{
	MyPriorityQueue<int> mpq;
	mpq.insert(0);
	ASSERT_EQ(mpq.min(), 0);
	mpq.extractMin();
	ASSERT_TRUE(mpq.isEmpty());
	ASSERT_EQ(mpq.size(), 0);
	ASSERT_THROW(mpq.extractMin(), PriorityQueueEmptyException);
}

TEST(SampleTests, ExtractMin3)
{
	MyPriorityQueue<int> mpq;
	ASSERT_TRUE(mpq.isEmpty());
	mpq.insert(3);
	mpq.insert(4);
	mpq.insert(5);
	mpq.insert(7);
	mpq.insert(9);
	mpq.insert(8);
	mpq.insert(6);
	ASSERT_EQ(mpq.min(), 3);
	mpq.extractMin();
	ASSERT_EQ(mpq.min(), 4);

}

TEST(SampleTests, ExtractMinComplex)
{
	MyPriorityQueue<int> mpq;
	for(int i = 0; i < 10; i ++)
	{
		mpq.insert(i);
		ASSERT_EQ(mpq.size(), i+1);
		ASSERT_EQ(mpq.min(), 0);
	}
	int j = 10;
	for(int i = 0; i < 9; i ++)
	{
		mpq.extractMin();
		j--;
		ASSERT_EQ(mpq.min(), i+1);
		ASSERT_EQ(mpq.size(), j);
	}
	ASSERT_EQ(mpq.size(),1);
	ASSERT_EQ(mpq.min(), 9);
}


TEST(SampleTests, ExtractMinThrow)
{
	MyPriorityQueue<int> mpq;
	ASSERT_THROW(mpq.extractMin(), PriorityQueueEmptyException);
}

TEST(SampleTests, MinThrow)
{
	MyPriorityQueue<int> mpq;
	ASSERT_THROW(mpq.min(), PriorityQueueEmptyException);
}





TEST(SampleTests, MSTn10)
{
	std::vector< std::vector< unsigned>  > gr = { 
		{ 0, 12, 12, 13, 17, 9, 7, 14, 3, 17},
		{ 12, 0, 8, 8, 8, 18, 19, 5, 15, 8},
		{ 12, 8, 0, 12, 15, 19, 17, 12, 9, 8},
		{ 13, 8, 12, 0, 6, 15, 14, 3, 10, 4},
		{ 17, 8, 15, 6, 0, 21, 19, 3, 14, 10},
		{ 9, 18, 19, 15, 21, 0, 11, 18, 10, 11},
		{ 7, 19, 17, 14, 19, 11, 0, 17, 10, 18},
		{ 14, 5, 12, 3, 3, 18, 17, 0, 11, 7},
		{ 3, 15, 9, 10, 14, 10, 10, 11, 0, 14},
		{ 17, 8, 8, 4, 10, 11, 18, 7, 14, 0}
	};

	std::vector<Edge> mst = compute_mst(gr);
	EXPECT_TRUE( verifyMST(mst, gr) );
}
TEST(SampleTests, MSTn20)
{
	std::vector< std::vector< unsigned>  > gr = { 
		{ 0, 8, 14, 10, 9, 8, 7, 6, 3, 12, 6, 10, 11, 9, 13, 5, 8, 8, 9, 13},
		{ 8, 0, 12, 11, 6, 6, 8, 9, 6, 11, 3, 10, 4, 12, 11, 3, 11, 7, 7, 12},
		{ 14, 12, 0, 10, 11, 16, 12, 13, 11, 9, 14, 16, 8, 12, 9, 15, 15, 11, 10, 5},
		{ 10, 11, 10, 0, 6, 14, 3, 13, 11, 10, 9, 9, 13, 16, 11, 11, 6, 10, 10, 10},
		{ 9, 6, 11, 6, 0, 11, 9, 7, 6, 12, 3, 12, 10, 10, 8, 9, 11, 8, 4, 12},
		{ 8, 6, 16, 14, 11, 0, 11, 11, 11, 13, 8, 8, 8, 14, 9, 3, 15, 11, 8, 11},
		{ 7, 8, 12, 3, 9, 11, 0, 13, 10, 11, 11, 6, 10, 14, 8, 8, 9, 7, 11, 7},
		{ 6, 9, 13, 13, 7, 11, 13, 0, 3, 11, 6, 15, 10, 3, 7, 11, 8, 7, 3, 10},
		{ 3, 6, 11, 11, 6, 11, 10, 3, 0, 14, 3, 12, 10, 6, 10, 8, 5, 10, 6, 10},
		{ 12, 11, 9, 10, 12, 13, 11, 11, 14, 0, 12, 10, 7, 14, 12, 14, 14, 4, 8, 7},
		{ 6, 3, 14, 9, 3, 8, 11, 6, 3, 12, 0, 12, 7, 9, 8, 6, 8, 8, 4, 9},
		{ 10, 10, 16, 9, 12, 8, 6, 15, 12, 10, 12, 0, 14, 18, 12, 11, 15, 13, 16, 13},
		{ 11, 4, 8, 13, 10, 8, 10, 10, 10, 7, 7, 14, 0, 13, 11, 7, 7, 3, 7, 13},
		{ 9, 12, 12, 16, 10, 14, 14, 3, 6, 14, 9, 18, 13, 0, 10, 14, 11, 10, 6, 7},
		{ 13, 11, 9, 11, 8, 9, 8, 7, 10, 12, 8, 12, 11, 10, 0, 12, 7, 8, 4, 14},
		{ 5, 3, 15, 11, 9, 3, 8, 11, 8, 14, 6, 11, 7, 14, 12, 0, 13, 10, 10, 14},
		{ 8, 11, 15, 6, 11, 15, 9, 8, 5, 14, 8, 15, 7, 11, 7, 13, 0, 10, 11, 15},
		{ 8, 7, 11, 10, 8, 11, 7, 7, 10, 4, 8, 13, 3, 10, 8, 10, 10, 0, 4, 11},
		{ 9, 7, 10, 10, 4, 8, 11, 3, 6, 8, 4, 16, 7, 6, 4, 10, 11, 4, 0, 13},
		{ 13, 12, 5, 10, 12, 11, 7, 10, 10, 7, 9, 13, 13, 7, 14, 14, 15, 11, 13, 0}
	};

	std::vector<Edge> mst = compute_mst(gr);
	EXPECT_TRUE( verifyMST(mst, gr) );
}


}