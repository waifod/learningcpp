#include <cassert>

template<int p, int q>
struct IsPrimeHelper {
  static constexpr bool value{p%q==0 ? false : IsPrimeHelper<p, q-1>::value};
};

template<int p>
struct IsPrimeHelper<p, 1> {
  static constexpr bool value{true};
};

template<int p>
struct IsPrime {
  static constexpr bool value{IsPrimeHelper<p, p/2>::value};
};

template<>
struct IsPrime<0> {
  static constexpr bool value{false};
};

template<>
struct IsPrime<1> {
  static constexpr bool value{false};
};

int main() {
  static_assert(IsPrime<0>::value == false);
  static_assert(IsPrime<1>::value == false);
  static_assert(IsPrime<2>::value == true);
  static_assert(IsPrime<3>::value == true);
  static_assert(IsPrime<4>::value == false);
  static_assert(IsPrime<5>::value == true);
  static_assert(IsPrime<6>::value == false);
  static_assert(IsPrime<7>::value == true);
  static_assert(IsPrime<8>::value == false);
  static_assert(IsPrime<99>::value == false);

  return EXIT_SUCCESS;
}
