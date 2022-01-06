#ifndef MINHEAP_HPP_
#define MINHEAP_HPP_

class MinHeap
{
public:
  MinHeap ();
  int Size ();
	//int getMinimum () { return harr[0]; } // Returns the minimum key (key at root) from min heap
  int ExtractMin (); // pop_back and return root
	//void deleteKey(int); // Deletes a key stored at index i
	void Insert (int); // Inserts a new key 'k'

private:

  int Parent (int);
  int Left (int); // to get index of left child of node at index i
  int Right (int); // to get index of right child of node at index i

  void MinHeapify(int); // to heapify a subtree with the root at given index
  //int ExtractMin(); // to extract the root which is the minimum element
  //void DecreaseKey(int i, int new_val); // Decreases key value of key at index i to new_val

  void Swap(int*, int*); // utility function to swap

  int heap_size_; // Current number of elements in min heap
  std::vector<int> data_;

};

#endif
