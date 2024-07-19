#include <iostream>

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

template<typename T>
void printSize(std::string structName) {
  std::cout << "sizeof(" << structName << ") = " << sizeof(T) << "\n";
}

int main() {
  printSize<char>("char");
  printSize<char*>("char*");
  printSize<short>("short");
  printSize<int>("int");
  printSize<long>("long");
  printSize<float>("float");
  printSize<double>("double");
  printSize<foo1>("struct foo1");
  printSize<foo2>("struct foo2");
  printSize<foo3>("struct foo3");
  printSize<foo4>("struct foo4");
  printSize<foo5>("struct foo5");
  printSize<foo6>("struct foo6");
  printSize<foo7>("struct foo7");
  printSize<foo8>("struct foo8");
  printSize<foo9>("struct foo9");
  printSize<foo10>("struct foo10");
  printSize<foo11>("struct foo11");
  printSize<foo12>("struct foo12");

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
