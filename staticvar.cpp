#include <chrono>
#include <iostream>
#include <string>

constexpr int ITERATIONS{10000000};

// Static values are initialized thread-safely on the first call.
// This means that whenever you call them you first check whether
// they are already initialized performing a lock, and if they are
// not yet initialized you initialize them.
// This causes a performance overhead, which can be avoided as we
// do here by returning the member variable of the object instead.
class String {
  public:
    static const std::string& staticGetString() {
      static const std::string s{"sily pisi"};
      return s;
    }

    const std::string& getString() const {
      return s_;
    }

  private:
    const std::string& s_{staticGetString()};
};

int main() {
  auto start = std::chrono::steady_clock::now();
  for (size_t i{0}; i<ITERATIONS; ++i) {
    (void)String::staticGetString();
  }
  auto end = std::chrono::steady_clock::now();
  std::cout << "It took "
    << std::chrono::duration<double, std::milli>(end-start).count()
    << "ms to execute the static version.\n";
  
  auto obj = String();
  start = std::chrono::steady_clock::now();
  for (size_t i{0}; i<ITERATIONS; ++i) {
    (void)obj.getString();
  }
  end = std::chrono::steady_clock::now();
  std::cout << "It took "
    << std::chrono::duration<double, std::milli>(end-start).count()
    << "ms to execute the non-static version.\n";

  return EXIT_SUCCESS;
}
