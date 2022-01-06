#include <iostream>
#include <vector>
#include <climits>
#include "minheap.hpp"

// Constructor: Builds a heap from a given array a[] of given size
MinHeap::MinHeap ()
{
	heap_size_ = 0;
}

int MinHeap::Size ()
{
  return data_.size();
}
// Inserts a new key 'k'
void MinHeap::Insert (int key)
{
	// if (heap_size == data_.capacity())
	// {
  //   data_.push_back(key);
  //   heap_size++;
	// 	cout << "\nOverflow: Could not insertKey\n";
	// 	return;
	// } // vector automatically increase

	// First insert the new key at the end
	heap_size_++;
	int i = heap_size_ - 1;
	data_.push_back(key);

	// Fix the min heap property if it is violated
	while (i != 0 && data_[Parent(i)] > data_[i])
	{
  	Swap(&data_[i], &data_[Parent(i)]);
  	i = Parent(i);
	}
}

// Method to remove minimum element (or root) from min heap
int MinHeap::ExtractMin ()
{
	if (heap_size_ <= 0) { return INT_MAX; }
	if (heap_size_ == 1)
	{
		heap_size_--;
    data_.pop_back();
		return data_[0];
	}

	// Store the minimum value, and remove it from heap
	int root = data_[0];
	data_[0] = data_[heap_size_-1];
	heap_size_--;
  data_.pop_back();
	MinHeapify(0);

	return root;
}

// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
// void MinHeap::deleteKey(int index)
// {
// 	decreaseKey(index, INT_MIN);
// 	extractMin();
// }

/* private members */

int MinHeap::Parent (int index) { return (index - 1)/2; }

int MinHeap::Left (int index) { return (2*index + 1); }

int MinHeap::Right (int index) { return (2*index + 2); }

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify (int index)
{
	int left_node = Left(index);
	int right_node = Right(index);
	int smallest = index;
	if (left_node < heap_size_ && data_[left_node] < data_[index]) { smallest = left_node; }
	if (right_node < heap_size_ && data_[right_node] < data_[smallest]) { smallest = right_node; }
	if (smallest != index)
	{
		Swap(&data_[index], &data_[smallest]);
		MinHeapify(smallest);
	}
}



// Decreases value of key at index 'i' to new_val. It is assumed that
// new_val is smaller than harr[i].
// void MinHeap::decreaseKey(int index, int new_val)
// {
// 	data_[index] = new_val;
// 	while (index != 0 && data_[parent(index)] > data_[index])
// 	{
//   	swap(&data_[index], &data_[parent(index)]);
//   	index = parent(index);
// 	}
// }

// A utility function to swap two elements
void MinHeap::Swap (int *x, int *y) { int temp = *x; *x = *y; *y = temp; }
