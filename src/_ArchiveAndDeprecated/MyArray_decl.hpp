#pragma once
#include "GlobalCore.hpp"

#include <string>
#include <vector>

namespace MyUtils::MyArray {

template<typename T>
class Array {
  using size_t = std::size_t;
  
 private:
  size_t size_ = 0;
  T* data_ = nullptr;

 public:
  Array() = default;

  explicit Array(size_t n)
    : size_(n), data_(n ? new T[n] : nullptr) {}

  Array(size_t n, const T& value)
    : Array(n) {
    for (size_t i = 0; i < size_; ++i) data_[i] = value;
  }

  Array(const std::vector<T>& v)
    : Array(v.size()) {
    for (size_t i = 0; i < size_; ++i) data_[i] = v[i];
  }

  ~Array() { delete[] data_; }

  Array(const Array& other)
    : Array(other.size_) {
    for (size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
  }

  Array(Array&& other) noexcept
    : size_(other.size_), data_(other.data_) {
    other.size_ = 0;
    other.data_ = nullptr;
  }

  Array& operator=(const Array& other) {
    if (this != &other) {
      Array tmp(other);          // copy-construct
      swap(tmp);                 // commit (strong-ish safety)
    }
    return *this;
  }

  Array& operator=(Array&& other) noexcept {
    if (this != &other) {
      delete[] data_;
      data_ = other.data_;
      size_ = other.size_;
      other.data_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  void swap(Array& o) noexcept {
    std::swap(size_, o.size_);
    std::swap(data_, o.data_);
  }

  T& operator[](size_t i) { return data_[i]; }
  const T& operator[](size_t i) const { return data_[i]; }

  T* raw() noexcept { return data_; }
  const T* raw() const noexcept { return data_; }

  size_t size() const noexcept { return size_; }
  
  void resize(size_t newSize) {
    T* newData = (T*)malloc(newSize*sizeof(T));
    free(data_);
    data_ = newData;
    size_ = newSize;
    data_.resize(newSize);
  }
  
  void push_back(T ele) {
    ++size_;
    data_.push_back(ele);
  };
  
  // Find ele with the value and return the positions of all occurances; if not found, return empty arr
  Array<int> find(T val) const {
    Array<int> arr = Array<int>();
    for(int i=0; i<size_; ++i) {
      if((*this)(i) == val)
        arr.push_back(i);
    }
    return arr;
  }
  
  void deleteIndices(const Array<size_t>& indicesToDelete) {
    Array<size_t> keepIndices;
    for (size_t i = 0; i < size_; ++i) {
      if(indicesToDelete.find((size_t)i).size()==0)
        keepIndices.push_back(i);
    }

    std::vector<T> newData(keepIndices.size());
    for (size_t iNew = 0; iNew < keepIndices.size(); ++iNew) {
      size_t iOld = keepIndices(iNew);
      newData[iNew] = (*this)(iOld);
    }

    size_ = keepIndices.size();
    data_ = std::move(newData);
  }
  void deleteIndices(const Array<int>& indicesToDelete) { // TODO: think about which we want. size_t or int or both possibly but also maybe not very good to have both
    Array<size_t> keepIndices;
    for (size_t i = 0; i < size_; ++i) {
      if(indicesToDelete.find((size_t)i).size()==0)
        keepIndices.push_back(i);
    }

    std::vector<T> newData(keepIndices.size());
    for (size_t iNew = 0; iNew < keepIndices.size(); ++iNew) {
      size_t iOld = keepIndices(iNew);
      newData[iNew] = (*this)(iOld);
    }

    size_ = keepIndices.size();
    data_ = std::move(newData);
  }
  
  // extends if newRowCount > size_; else return and throw no errors
  void extend(size_t newRowCount) {
    if (newRowCount <= size_)
      return;

    // inefficient
    for(int i=size_; i< newRowCount; ++i)
      (*this).push_back(T{});
    size_ = newRowCount;
  }
  
  void print(int eleStrLen = 5) const;
  std::string toString(int eleStrLen = 5) const;
};

} // namespace MyFem
