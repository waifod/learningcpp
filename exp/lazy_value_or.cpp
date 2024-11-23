#include <functional>
#include <iostream>
#include <optional>

template <typename F>
struct Lazy {
  F f;

  operator decltype(f())() const {
    std::cout << "Lazily evaluating function... ";
    return f();
  }
};

template <typename T>
struct AlsoLazy {
  std::function<T()> f;

  operator T() const {
    std::cout << "Lazily evaluating function... ";
    return f();
  }
};

int main() {
  auto lambda = [] { return 42; };
  auto lazyInt = Lazy{lambda};
  auto alsoLazyInt = AlsoLazy<int32_t>{lambda};

  std::optional<int32_t> optInt;
  std::cout << "Calling value_or on empty optional... "
            << optInt.value_or(lazyInt) << '\n';
  std::cout << "Again calling value_or on empty optional... "
            << optInt.value_or(alsoLazyInt) << "\n\n";

  optInt = 7;
  std::cout << "Calling value_or on non-empty optional... "
            << optInt.value_or(lazyInt) << '\n';
  std::cout << "Again calling value_or on non-empty optional... "
            << optInt.value_or(alsoLazyInt) << '\n';
}
