#include "min_heap.hpp"

uint64_t MinHeap::Size () const { return data_.Size(); }

bool MinHeap::IsEmpty () const { return (data_.Size() == 0); }

uint64_t MinHeap::Top () const { return data_[0]; }

void MinHeap::Push (uint64_t key)
{
	data_.PushBack(key);
	uint64_t current_index {data_.Size() - 1};
	while (current_index)
	{
		uint64_t parent_index {(current_index - 1) / 2};
		if (data_[parent_index] > key) { data_[current_index] = data_[parent_index]; }
		else { break; }
		current_index = parent_index;
	}
	data_[current_index] = key;
	return;
}

void MinHeap::Pop ()
{
	uint64_t key {data_[data_.Size() - 1]};
	uint64_t current_index {};
	data_.PopBack();
	if (data_.Size())
	{
		while (true)
		{
			uint64_t left_child_index {current_index * 2 + 1};
			uint64_t right_child_index {current_index * 2 + 2};
			if (right_child_index < data_.Size()) // two children
			{
				uint64_t& left_child {data_[left_child_index]};
				uint64_t& right_child {data_[right_child_index]};
				if (left_child < key && left_child < right_child)
				{
					data_[current_index] = left_child;
					current_index = left_child_index;
				}
				else if (right_child < key && right_child < left_child)
				{
					data_[current_index] = right_child;
					current_index = right_child_index;
				}
				else { break; }
			}
			else if (left_child_index < data_.Size()) // only left child
			{
				uint64_t& left_child {data_[left_child_index]};
				if (left_child < key)
				{
					data_[current_index] = left_child;
					current_index = left_child_index;
				}
				else { break; }
			}
			else { break; } // no child (leaf)
		}
		data_[current_index] = key;
	}
	return;
}

std::ostream& operator<< (std::ostream& out, MinHeap heap)
{
	Vector<uint64_t> buffer;
	while (!heap.IsEmpty())
	{
		buffer.PushBack(heap.Top());
		heap.Pop();
	}
	out << buffer; // ascendingly sorted sequence
	return out;
}
