#include <iostream>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
std::string to_string_impl(const T& t) {
  std::stringstream ss;
  ss << t;
  return ss.str();
}

std::vector<std::string> recursive_to_string_vec() {
  return {};
}

template <typename T, typename ... Ts>
std::vector<std::string> recursive_to_string_vec(const T& t1, const Ts& ... ts) {
  std::vector<std::string> strings {to_string_impl(t1)};
  for (const auto& s : recursive_to_string_vec(ts...)) {
    strings.emplace_back(s);
  } 
  return strings;
}

template <typename ... Ts>
std::vector<std::string> initlist_to_string_vec(const Ts& ... ts) {
  return {to_string_impl(ts)...};
}

template <typename ... Ts>
std::vector<std::string> lambda_to_string_vec(const Ts& ... ts) {
  const auto to_string = [](const auto& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
  };

  return {to_string(ts)...};
}

int main() {
  std::cout << "Calling the recursive version.\n";
  auto vec {recursive_to_string_vec("hello", 1, 2.0, 4.3f, "bob")};
  for (const auto& s : vec) {
    std::cout << s << '\n';
  }
  
  std::cout << "\nCalling the initializer_list version.\n";
  vec = initlist_to_string_vec("hello", 1, 2.0, 4.3f, "bob");
  for (const auto& s : vec) {
    std::cout << s << '\n';
  }

  std::cout << "\nCalling the lambda version.\n";
  vec = lambda_to_string_vec("hello", 1, 2.0, 4.3f, "bob");
  for (const auto& s : vec) {
    std::cout << s << '\n';
  }
}
