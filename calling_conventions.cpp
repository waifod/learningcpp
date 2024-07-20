#include <iostream>

struct Wrapper {
  public:
    explicit Wrapper(int val) : val_{val} {
      std::cout << "Wrapper " << val_ << " constructed from int.\n";
    }
    
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

void foo(Wrapper w) {
  std::cout << "foo called for wrapper " << w.getVal() << ".\n\n";
}

void bar(const Wrapper& w) {
  std::cout << "bar called by const& for wrapper " << w.getVal() << ".\n\n";
}

void bar(Wrapper&& w) {
  std::cout << "bar called by && for wrapper " << w.getVal() << ".\n\n";
}

void baz(const Wrapper& w) {
    std::cout << "baz called for wrapper " << w.getVal() << ".\n\n";
}

int main() {
  std::cout << "w0: passed as-is.\n"
            << "w1: passed via std::move.\n"
            << "w2: constructed in the function call.\n";

  std::cout << "\n========================================"
            << "\nTesting constructors.\n\n";
  Wrapper w0 {0};
  Wrapper w1 {1};
  [[maybe_unused]] auto w3 {w0};
  [[maybe_unused]] auto w4 {std::move(w1)};
  [[maybe_unused]] auto w5 {Wrapper{2}};

  std::cout << "\n========================================"
            << "\nTesting assignments.\n\n";
  w0 = w0;
  w0 = std::move(w1);
  w0 = Wrapper{2};

  std::cout << "\n========================================"
            << "\nTesting calling conventions for foo."
            << "\nfoo has signature void(Wrapper).\n\n";
  foo(w0);
  foo(std::move(w1));
  foo(Wrapper{2});

  std::cout << "========================================"
            << "\nTesting calling conventions for bar."
            << "\nbar has signatures void(const Wrapper&) and void(Wrapper&&).\n\n";
  bar(w0);
  bar(std::move(w1));
  bar(Wrapper{2});

  std::cout << "========================================"
            << "\nTesting calling conventions for baz."
            << "\nbaz has signature void(const Wrapper&).\n\n";
  baz(w0);
  baz(std::move(w1));
  baz(Wrapper{2});
}
