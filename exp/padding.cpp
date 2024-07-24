#include <cxxabi.h>

#include <iostream>
#include <stdexcept>
#include <typeinfo>

/* The expected sizes in these comments assume a 64-bit machine */

struct foo1 {
  char *p;
  char c;
  long x;
};

struct foo2 {
  char c;      /* 1 byte */
  char pad[7]; /* 7 bytes */
  char *p;     /* 8 bytes */
  long x;      /* 8 bytes */
};

struct foo3 {
  char *p; /* 8 bytes */
  char c;  /* 1 byte */
};

struct foo4 {
  short s; /* 2 bytes */
  char c;  /* 1 byte */
};

struct foo5 {
  char c;
  struct foo5_inner {
    char *p;
    short x;
  } inner;
};

struct foo6 {
  short s;
  char c;
  int flip : 1;
  int nybble : 4;
  int septet : 7;
};

struct foo7 {
  int bigfield : 31;
  int littlefield : 1;
};

struct foo8 {
  int bigfield1 : 31;
  int littlefield1 : 1;
  int bigfield2 : 31;
  int littlefield2 : 1;
};

struct foo9 {
  int bigfield1 : 31;
  int bigfield2 : 31;
  int littlefield1 : 1;
  int littlefield2 : 1;
};

struct foo10 {
  char c;
  struct foo10 *p;
  short x;
};

struct foo11 {
  struct foo11 *p;
  short x;
  char c;
};

struct foo12 {
  struct foo12_inner {
    char *p;
    short x;
  } inner;
  char c;
};

std::string demangle(const char *mangled_name) {
  int status;
  char *demangled_name{abi::__cxa_demangle(mangled_name, nullptr, 0, &status)};
  if (status == 0) {
    std::string retval{demangled_name};
    free(demangled_name);
    return retval;
  } else {
    throw std::runtime_error("Error demangling");
  }
}

template <typename T>
void print_size() {
  std::cout << "sizeof(" << demangle(typeid(T).name()) << ") = " << sizeof(T)
            << "\n";
}

int main() {
  print_size<char>();
  print_size<char[3]>();
  print_size<char *>();
  print_size<short>();
  print_size<int>();
  print_size<long>();
  print_size<float>();
  print_size<double>();
  print_size<foo1>();
  print_size<foo2>();
  print_size<foo3>();
  print_size<foo4>();
  print_size<foo5>();
  print_size<foo6>();
  print_size<foo7>();
  print_size<foo8>();
  print_size<foo9>();
  print_size<foo10>();
  print_size<foo11>();
  print_size<foo12>();

  if (sizeof(struct foo3) == 16) {
    std::cout << "This looks like a 64-bit machine.\n";
  } else if (sizeof(struct foo3) == 6) {
    std::cout << "This looks like a 32-bit machine.\n";
  } else {
    std::cout << "Huh? The word size of this machine is not obvious.\n";
  }

  if ((offsetof(struct foo1, x) % sizeof(long)) == 0) {
    std::cout << "Self-alignment seems to be required.";
  } else {
    std::cout << "Self-alignment test of type long failed.";
  }
  std::cout << std::endl;
}
