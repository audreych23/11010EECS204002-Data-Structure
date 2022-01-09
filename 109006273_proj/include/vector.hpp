#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <iostream>

template <typename ElementType>
class Vector
{
public:

  // Vector () = default; // default constructor
  // Vector (Vector const&) = default; // copy constructor
  // Vector (Vector&&) = default; // move constructor
  // ~Vector () = default; // destructor
  // Vector& operator= (Vector const&); // copy assignment
  // Vector& operator= (Vector&&); // move assignment

  Vector (uint64_t size = 0);
  Vector (Vector const&); // copy constructor
  Vector& operator= (Vector const&); // copy assignment
  ~Vector ();

  uint64_t Size () const;
  uint64_t Capacity () const;
  bool IsEmpty () const;
  void PushBack (ElementType element);
  void PopBack ();
  ElementType& operator[] (uint64_t index);
  ElementType const& operator[] (uint64_t index) const;

  /* https://youtu.be/POa_V15je8Y?t=2053 */
  friend std::ostream& operator<< (std::ostream& out, Vector const& vector)
  {
    if (!vector.IsEmpty())
    {
      out << vector[0];
      for (uint64_t i {1}; i != vector.Size(); ++i) { out << " " << vector[i]; }
    }
    out << "\n";
    return out;
  }

private:

  uint64_t CalculateNextPowerOfTwo (uint64_t value);

  uint64_t capacity_;
  uint64_t size_;
  ElementType* data_;

};

/* definition of public member functions */

template <typename ElementType>
Vector<ElementType>::Vector (uint64_t size)
{
  capacity_ = CalculateNextPowerOfTwo((size < 4) ? 4 : size);
  size_ = size;
  data_ = new ElementType [capacity_];
}

template <typename ElementType>
Vector<ElementType>::Vector (Vector const& vector) // copy constructor
{
  if (this != &vector)
  {
    capacity_ = vector.capacity_;
    size_ = vector.size_;
    data_ = new ElementType [capacity_];
    for (uint64_t i {}; i != size_; ++i) { data_[i] = vector.data_[i]; }
  }
}

template <typename ElementType>
Vector<ElementType>& Vector<ElementType>::operator= (Vector const& vector) // copy assignment
{
  if (this != &vector)
  {
    capacity_ = vector.capacity_;
    size_ = vector.size_;
    data_ = new ElementType [capacity_];
    for (uint64_t i {}; i != size_; ++i) { data_[i] = vector.data_[i]; }
  }
  return *this;
}

template <typename ElementType>
Vector<ElementType>::~Vector ()
{
  delete [] data_;
}

template <typename ElementType>
uint64_t Vector<ElementType>::Size () const { return size_; }

template <typename ElementType>
uint64_t Vector<ElementType>::Capacity () const { return capacity_; }

template <typename ElementType>
bool Vector<ElementType>::IsEmpty () const { return (size_ == 0); }

template <typename ElementType>
void Vector<ElementType>::PushBack (ElementType value)
{
  data_[size_++] = value;
  if (size_ == capacity_)
  {
    capacity_ *= 2;
    ElementType* temp = new ElementType [capacity_];
    for (uint64_t i {}; i != size_; ++i)
    {
      temp[i] = data_[i];
    }
    delete [] data_;
    data_ = temp;
  }
  return;
}

template <typename ElementType>
void Vector<ElementType>::PopBack ()
{
  if (size_)
  {
    if (capacity_ >= 8)
    {
      if (--size_ == capacity_ / 4)
      {
        capacity_ /= 2;
        ElementType* temp = new ElementType [capacity_];
        for (uint64_t i {}; i != size_; ++i)
        {
          temp[i] = data_[i];
        }
        delete [] data_;
        data_ = temp;
      }
    }
    else { --size_; }
  }
  return;
}

template <typename ElementType>
ElementType& Vector<ElementType>::operator[] (uint64_t index) { return data_[index]; }

template <typename ElementType>
ElementType const& Vector<ElementType>::operator[] (uint64_t index) const { return data_[index]; }

/* definition of private member functions */

template <typename ElementType>
uint64_t Vector<ElementType>::CalculateNextPowerOfTwo (uint64_t value)
{
  uint64_t power_of_two {1};
  while (power_of_two <= value) { power_of_two <<= 1; }
  return power_of_two;
}

#endif
