#include <algorithm>

template<typename T>
class UniquePtr {
  private:
    T* ptr_;

  public:
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    explicit UniquePtr(T* ptr = nullptr) noexcept : ptr_{ptr} {}

    T* release() noexcept {
      auto oldPtr = ptr_;
      ptr_ = nullptr;
      return oldPtr;
    }

    void reset(T* ptr = nullptr) noexcept {
      if (ptr_ != nullptr) {
        delete ptr_;
      }
      ptr_ = ptr;
    }

    UniquePtr& operator=(T* ptr) noexcept {
      reset(ptr);
      return *this;
    }
    
    template<typename U>
    UniquePtr(UniquePtr<U>&& other) noexcept {
      reset(other.release());
    }
    
    template<typename U>
    UniquePtr& operator=(UniquePtr<U>&& other) noexcept {
      reset(other.release());
      return *this;
    }

    ~UniquePtr() noexcept {
      reset();
    }

    T* get() const noexcept {
      return ptr_;
    }

    T* operator->() const noexcept {
      return get();
    }
    
    T& operator*() const noexcept {
      return *get();
    }

    void swap(UniquePtr& other) noexcept {
      std::swap(this->ptr_, other.ptr_);
    }

    explicit operator bool() const noexcept {
      return ptr_ != nullptr;
    }
};
