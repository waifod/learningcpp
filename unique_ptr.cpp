#include <algorithm>

template<typename T>
class UniquePtr {
  private:
    T* ptr_;

  public:
    UniquePtr(const UniquePtr&) noexcept = delete;
    UniquePtr& operator=(const UniquePtr&) noexcept = delete;

    constexpr T* release() noexcept {
      auto tmp = ptr_;
      ptr_ = nullptr;
      return tmp;
    }

    constexpr void reset(T* ptr = nullptr) noexcept {
      delete ptr_;
      ptr_ = ptr;
    }

    [[nodiscard]] constexpr explicit UniquePtr(T* ptr = nullptr) noexcept : ptr_{ptr} {}

    // Move constructor
    [[nodiscard]] constexpr UniquePtr(UniquePtr&& other) noexcept 
    : ptr_{other.ptr_} {
      other.ptr_ = nullptr;
    }
    
    ~UniquePtr() noexcept {
      reset();
    }

    [[nodiscard]] constexpr UniquePtr& operator=(T* ptr) noexcept {
      reset(ptr);
      return *this;
    }
    
    // Move assignment
    [[nodiscard]] constexpr UniquePtr& operator=(UniquePtr&& other) noexcept {
      reset(other.ptr_);
      other.ptr_ = nullptr;
      return *this;
    }

    [[nodiscard]] T* get() const noexcept {
      return ptr_;
    }

    [[nodiscard]] T* operator->() const noexcept {
      return get();
    }
    
    [[nodiscard]] constexpr T& operator*() const noexcept {
      return *get();
    }

    template<typename U>
    void swap(UniquePtr<U>& other) noexcept {
      std::swap(ptr_, other.ptr_);
    }

    constexpr explicit operator bool() const noexcept {
      return static_cast<bool>(ptr_);
    }
};

template<typename T, typename ... Args>
UniquePtr& make_unique(Args&& ... args) {
  return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
