#include <cassert>

template<int n>
struct IsPrime {
  private:
    template<int m, int k>
    struct IsPrimeHelper {
      static constexpr bool value{m % k == 0 ? false : IsPrimeHelper<m, k-1>::value};
    };

    template<int m>
    struct IsPrimeHelper<m, 1> {
      static constexpr bool value{true};
    };

  public:
    static constexpr bool value{IsPrimeHelper<n, n/2>::value};
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
  static_assert(IsPrime<9>::value == false);
  static_assert(IsPrime<99>::value == false);
  static_assert(IsPrime<999>::value == false);
  // We can't call IsPrime<9999>::value because there's
  // a maximum recursion depth for template instantiation.
  //static_assert(IsPrime<9999>::value == false);
}
