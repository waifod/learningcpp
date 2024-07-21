#include <algorithm>

template<typename T>
class UniquePtr {
  public:
    constexpr UniquePtr(const UniquePtr&) noexcept = delete;
    constexpr UniquePtr& operator=(const UniquePtr&) noexcept = delete;

    [[nodiscard]] constexpr explicit UniquePtr(T* ptr = nullptr) noexcept 
    : ptr_{ptr} {}

    [[nodiscard]] constexpr UniquePtr(UniquePtr&& other) noexcept 
    : ptr_{other.ptr_} {
      other.ptr_ = nullptr;
    }
    
    ~UniquePtr() noexcept { delete ptr_; }

    [[nodiscard]] constexpr UniquePtr& operator=(T* ptr) noexcept {
      reset(ptr);
      return *this;
    }
    
    [[nodiscard]] constexpr UniquePtr& operator=(UniquePtr&& other) noexcept {
      reset(other.ptr_);
      other.ptr_ = nullptr;
      return *this;
    }

    [[nodiscard]] T* get() const noexcept { return ptr_; }
    [[nodiscard]] T* operator->() const noexcept { return get(); }
    [[nodiscard]] constexpr T& operator*() const noexcept { return *get(); }

    void swap(UniquePtr& other) noexcept { std::swap(ptr_, other.ptr_); }

    constexpr explicit operator bool() const noexcept { return static_cast<bool>(ptr_); }

    constexpr T* release() noexcept {
      auto tmp = ptr_;
      ptr_ = nullptr;
      return tmp;
    }

    constexpr void reset(T* ptr = nullptr) noexcept {
      delete ptr_;
      ptr_ = ptr;
    }

  private:
    T* ptr_{nullptr};
};

template<typename T, typename ... Args>
UniquePtr<T> make_unique(Args&& ... args) {
  return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
