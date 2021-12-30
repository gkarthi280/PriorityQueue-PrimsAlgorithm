#ifndef __PROJ5_PRIORITY_QUEUE_HPP
#define __PROJ5_PRIORITY_QUEUE_HPP

#include "runtimeexcept.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

class PriorityQueueEmptyException : public RuntimeException 
{
public:
	PriorityQueueEmptyException(const std::string & err) : RuntimeException(err) {}
};




template<typename Object>
class MyPriorityQueue
{
private:
	// fill in private member data here
	std::vector<Object> minHeap;


public:

	// You also need a constructor and a destructor.
	MyPriorityQueue();
	~MyPriorityQueue(){};


	//returns vector form of the vdctor minHeap
	std::vector<Object> vectorHeap();

 	size_t size() const noexcept;
	bool isEmpty() const noexcept;

	void insert(const Object & elem);


	// Note:  no non-const version of this one.  This is on purpose because
	// the interior contents should not be able to be modified due to the
	// heap property.  This isn't true of all priority queues but 
	// for this project, we will do this.
	// min and extractMin should throw PriorityQueueEmptyException if the queue is empty.
	const Object & min() const; 

	void extractMin(); 

};

template<typename Object>
MyPriorityQueue<Object>::MyPriorityQueue()
	:minHeap{}
{
}


template<typename Object>
std::vector<Object> MyPriorityQueue<Object>::vectorHeap()
{
	return minHeap;
}


template<typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
	return minHeap.size();
}



template<typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
	return minHeap.empty();
}

template<typename Object>
void MyPriorityQueue<Object>::insert(const Object & elem) 
{
	minHeap.push_back(elem);
	int index = minHeap.size() - 1;
	int parent_index;
	while(index > 0)
	{
		parent_index = (index - 1) / 2;
		if(minHeap[index] < minHeap[parent_index])
		{
			std::swap(minHeap[index], minHeap[parent_index]);
			index = parent_index;
		}
		else
		{
			return;
		}
	}

}




template<typename Object>
const Object & MyPriorityQueue<Object>::min() const
{
	if(isEmpty())
	{
		throw PriorityQueueEmptyException{""};
	}
	return minHeap[0];
}



template<typename Object>
void MyPriorityQueue<Object>::extractMin() 
{
	if(isEmpty())
	{
		throw PriorityQueueEmptyException{""};
	}
	if(size() == 1)
	{
		minHeap.clear();
		return;
	}

	int index = minHeap.size() - 1;
	minHeap[0] = minHeap[index];
	minHeap.pop_back();
	index = 0;
	int leftChild_index;
	int rightChild_index;
	int end_index = minHeap.size() - 1;
	while(index < end_index)
	{
		leftChild_index = 2*index + 1;
		rightChild_index = 2*index + 2;
		if(leftChild_index > end_index) //if left and right child don't exist
		{
			index = leftChild_index;
		}
		else if(leftChild_index == end_index) //if right child does'nt exist
		{
			if(minHeap[leftChild_index] < minHeap[index])
			{
				std::swap(minHeap[index], minHeap[leftChild_index]);
				index = leftChild_index;

			}
			else
			{
				return;
			}
		}
		else //if both children are in bounds
		{
			Object minChild = std::min(minHeap[leftChild_index], minHeap[rightChild_index]);
			if(minChild < minHeap[index])
			{
				if(minChild == minHeap[leftChild_index]) //minimum is left child
				{
					std::swap(minHeap[index], minHeap[leftChild_index]);
					index = leftChild_index;
				}
				else //minimum is rightCHild
				{
					std::swap(minHeap[index], minHeap[rightChild_index]);
					index = rightChild_index;
				}
				
			}
			else
			{
				return;
			}
			
		}

	}
}


#endif 
