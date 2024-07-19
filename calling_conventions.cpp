#include <iostream>

struct Wrapper {
  public:
    explicit Wrapper(int val) : val_{val} {}
    
    Wrapper(const Wrapper& other) : val_{other.val_} {
      std::cout << "Wrapper constructed from " << val_ << " with copy constructor.\n";
    }

    Wrapper(Wrapper&& other) : val_{other.val_} {
      std::cout << "Wrapper constructed from " << val_ << " with move constructor.\n";
    }
    
    Wrapper& operator=(Wrapper&& other) {
      std::cout << "Wrapper " << val_ << " assigned from " << other.val_ << " with move assignment.\n";
      return *this;
    }
    
    Wrapper& operator=(const Wrapper& other) {
      std::cout << "Wrapper " << val_ << " assigned from " << other.val_ << " with copy assignment.\n";
      return *this;
    }
    
    int getVal() const { return val_; }
    
  private:
    int val_;
};

void fooVal(Wrapper w) {
  std::cout << "foo called by value for wrapper " << w.getVal() << ".\n";
}

void foo(const Wrapper& w) {
  std::cout << "foo called by const& for wrapper " << w.getVal() << ".\n";
}

void foo(Wrapper&& w) {
  std::cout << "foo called by && for wrapper " << w.getVal() << ".\n";
}

void goo(const Wrapper& w) {
    std::cout << "goo called by const& for wrapper " << w.getVal() << ".\n";
}

int main() {
  std::cout << "w0 is always passed as-is, w1 is always passed via std::move, w2 is always constructed in the function call.\n";
  Wrapper w0 {0};
  Wrapper w1 {1};
  
  std::cout << "\nTesting constructors.\n";
  auto w3 {w0};
  auto w4 {std::move(w1)};
  auto w5 {Wrapper(2)};  // Why is this not outputting anything?
  std::cout << "Nothing is being outputted for 2 and I don't know why. Is this some sort of elision?\n";

  std::cout << "\nTesting assignments.\n";
  w1 = w0;
  w1 = std::move(w1);
  w1 = Wrapper(2);

  std::cout << "\nfooVal has signature void(Wrapper)."
            << "\nTesting calling conventions for fooVal.\n";
  fooVal(w0);
  fooVal(w0);
  fooVal(std::move(w1));
  fooVal(Wrapper(2));

  std::cout << "\nfoo has signatures void(const Wrapper&) and void(Wrapper&&)."
            << "\nTesting calling conventions for foo.\n";
  foo(w0);
  foo(std::move(w1));
  foo(Wrapper(2));

  std::cout << "\ngoo has signature void(const Wrapper&)."
            << "\nTesting calling conventions for goo.\n";
  goo(w0);
  goo(std::move(w1));
  goo(Wrapper(2));

  std::cout << std::endl;
}
