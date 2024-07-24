#include <cstdlib>

template <int m, int n>
struct GCD {
  static constexpr int value{GCD<n, m % n>::value};
};

template <int m>
struct GCD<m, 0> {
  static constexpr int value{m};
};

int main() {
  static_assert(GCD<2, 4>::value == 2);
  static_assert(GCD<1, 4>::value == 1);
  static_assert(GCD<0, 4>::value == 4);
  static_assert(GCD<3, 0>::value == 3);
  static_assert(GCD<6, 4>::value == 2);
}
