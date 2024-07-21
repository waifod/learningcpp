#include <algorithm>
#include <atomic>

template<typename T>
class SharedPtr {
  public:
    explicit SharedPtr() noexcept = default;

    explicit SharedPtr(T* ptr) noexcept
    : ptr_{ptr}
    , counter_{new std::atomic<int>(1)} {}

    SharedPtr(const SharedPtr& other) noexcept
    : ptr_{other.ptr_}
    , counter_{other.counter_} {
      increment();
    }

    SharedPtr(SharedPtr&& other) noexcept
    : ptr_{other.ptr_}
    , counter_{other.counter_} {
      other.ptr_ = nullptr;
      other.counter_ = nullptr;
    }
    
    ~SharedPtr() noexcept { decrement(); }

    SharedPtr& operator=(const SharedPtr& other) {
      if (this != &other) [[likely]] {
        decrement();
        ptr_ = other.ptr_;
        counter_ = other.counter_;
        increment();
      }
      return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) {
      if (this != &other) [[likely]] {
        decrement();
        ptr_ = other.ptr_;
        counter_ = other.counter_;
        other.ptr_ = nullptr;
        other.counter_ = nullptr;
      }
      return *this;
    }

    T* get() const noexcept { return ptr_; }
    T* operator->() const noexcept { return get(); }
    T& operator*() const noexcept { return *get(); }

    int use_count() const noexcept { return counter_ ? counter_->load() : 0; }

    void swap(SharedPtr& other) noexcept {
      std::swap(ptr_, other.ptr_);
      std::swap(counter_, other.counter_);
    }

    explicit operator bool() const noexcept { return static_cast<bool>(ptr_); }
    
  private:
    T* ptr_{nullptr};
    std::atomic<int>* counter_{nullptr};

    void increment() {
      if (counter_) [[likely]] {
        ++(*counter_);
      }
    }

    void decrement() {
      if (counter_ && --(*counter_) == 0) {
        delete ptr_;
        delete counter_;
      }
    }
};

template<typename T, typename ... Args>
SharedPtr<T> make_shared(Args&& ... args) {
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}
