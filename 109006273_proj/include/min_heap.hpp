#ifndef MINHEAP_HPP_
#define MINHEAP_HPP_

#include <fstream>

#include "vector.hpp"

class MinHeap
{
public:

  uint64_t Size () const;
  bool IsEmpty () const;
  uint64_t Top () const;
  void Push (uint64_t key);
  void Pop ();

  friend std::ostream& operator<< (std::ostream& out, MinHeap heap);

private:

  Vector<uint64_t> data_;

};

#endif
