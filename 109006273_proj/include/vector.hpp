#ifndef VECTOR_HPP_
#define VECTOR_HPP_

template <typename T>
class Vector
{
public:

  // Vector () = default; // default constructor
  // Vector (Vector const&) = default; // copy constructor
  // Vector (Vector&&) = default; // move constructor
  // ~Vector () = default; // destructor
  // Vector& operator= (Vector const&); // copy assignment
  // Vector& operator= (Vector&&); // move assignment

  Vector (int size = 0);
  //Vector (Vector const&) = default; // copy constructor
  //Vector& operator= (Vector const&); // copy assignment
  ~Vector ();

  int Size () const;
  int Capacity () const;
  void PushBack (T);
  void PopBack ();
  T& operator[] (int);

private:

  int CalculateNextPowerOfTwo (int);
  void Swap (T**, T**);

  int capacity_;
  int size_;
  T* data_;

};

/* definitions of public member functions */

template <typename T>
Vector<T>::Vector (int size)
{
  capacity_ = CalculateNextPowerOfTwo((size < 4) ? 4 : size);
  size_ = size;
  data_ = new T [capacity_];
}

template <typename T>
Vector<T>::~Vector ()
{
  delete [] data_;
}

template <typename T>
int Vector<T>::Size () const { return size_; }

template <typename T>
int Vector<T>::Capacity () const { return capacity_; }

template <typename T>
void Vector<T>::PushBack (T value)
{
  data_[size_++] = value;
  if (size_ == capacity_)
  {
    capacity_ *= 2;
    T* temp = new T [capacity_];
    for (int i {}; i != size_; ++i)
    {
      temp[i] = data_[i];
    }
    Swap(&temp, &data_);
    delete [] temp;
  }
  return;
}

template <typename T>
void Vector<T>::PopBack ()
{
  if (size_ > 0)
  {
    if (--size_ == capacity_ / 4)
    {
      capacity_ /= 2;
      T* temp = new T [capacity_];
      for (int i {}; i != size_; ++i)
      {
        temp[i] = data_[i];
      }
      Swap(&temp, &data_);
      delete [] temp;
    }
  }
  return;
}

template <typename T>
T& Vector<T>::operator[] (int index)
{
  if (index < 0 || index >= size_) { std::cerr << "invalid index\n"; }
  return data_[index];
}

/* definitions of private member functions */

template <typename T>
int Vector<T>::CalculateNextPowerOfTwo (int value)
{
  int power_of_two {1};
  while (power_of_two <= value) { power_of_two <<= 1; }
  return power_of_two;
}

template <typename T>
void Vector<T>::Swap (T** lhs, T** rhs)
{
  T** temp = lhs; lhs = rhs; rhs = temp;
  return;
}

#endif
