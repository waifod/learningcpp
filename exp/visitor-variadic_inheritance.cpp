#include <cstdint>
#include <iostream>
#include <string>
#include <variant>

// Multiple inheritance from C++98
// Operator overloading from C++98
// Variadic templates from C++11
// Variadic using from C++17
// No need for an explicit deduction guide for the constructor as of C++20

template <typename... Callable>
struct Visitor : Callable... {
  using Callable::operator()...;
};

int main() {
  constexpr Visitor visitor{
      [](std::int32_t n) { std::cout << "Received int " << n << ".\n"; },
      [](float f) { std::cout << "Received float " << f << ".\n"; },
      [](auto) { std::cout << "Received something.\n"; }};

  std::variant<std::monostate, int, float, std::string> variant;
  std::visit(visitor, variant);

  variant = 3;
  std::visit(visitor, variant);

  variant = 4.5f;
  std::visit(visitor, variant);

  variant = "sily_pisi";
  std::visit(visitor, variant);
}
