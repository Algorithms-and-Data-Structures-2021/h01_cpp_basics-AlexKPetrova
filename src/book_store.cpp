#include "book_store.hpp"

#include <algorithm>  // copy
#include <stdexcept>  // invalid_argument

// 1. реализуйте функцию ...
ResizeStorageStatus resize_storage(Book *&storage, int size, int new_capacity) {
    if(size<0) return ResizeStorageStatus::NEGATIVE_SIZE;
    if(new_capacity<= size) return ResizeStorageStatus::INSUFFICIENT_CAPACITY;
    if(storage == nullptr) return ResizeStorageStatus::NULL_STORAGE;
    auto new_arr = new Book[new_capacity];
    std::copy(storage,storage+size,new_arr);
    delete[] storage;
    storage=new_arr;
    return ResizeStorageStatus::SUCCESS;
}

// 2. реализуйте конструктор ...
BookStore::BookStore(const std::string &name) : name_{name} {
        if (name.empty()) {
            throw std::invalid_argument("BookStore::name must not be empty");
        }
        name_ = name;
        storage_capacity_= kInitStorageCapacity;
        storage_ = new Book[storage_capacity_];
}

// 3. реализуйте деструктор ...
BookStore::~BookStore() {
        delete[] storage_;
        storage_ = nullptr;
        storage_size_ = 0;
        storage_capacity_ = 0;
}

// 4. реализуйте метод ...
void BookStore::AddBook(const Book &book) {
    if (storage_size_ == storage_capacity_) {
        ResizeStorageStatus status = resize_storage_internal(storage_capacity_+ kCapacityCoefficient);
        if(status != ResizeStorageStatus::SUCCESS){
            return;
        }
    }
    storage_[storage_size_]= book;
    storage_size_++;
}

// РЕАЛИЗОВАНО

const std::string &BookStore::GetName() const {
  return name_;
}

int BookStore::GetSize() const {
  return storage_size_;
}

int BookStore::GetCapacity() const {
  return storage_capacity_;
}

const Book *BookStore::GetBooks() const {
  return storage_;
}

ResizeStorageStatus BookStore::resize_storage_internal(int new_capacity) {
  // изменяем размеры хранилища с копированием старых данных в хранилище нового объема
  const ResizeStorageStatus status = resize_storage(storage_, storage_size_, new_capacity);

  // если все прошло ОК, то сохраняем новый объем хранилища в объекте
  if (status == ResizeStorageStatus::SUCCESS) {
    storage_capacity_ = new_capacity;
  }

  return status;
}