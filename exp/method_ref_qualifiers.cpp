#include <iostream>

class Object {
 private:
  std::string val_;

 public:
  explicit Object(std::string s) : val_{s} {};

  static const Object getConstInstance(std::string s) { return Object{s}; }

  void foo() { std::cout << "Calling foo() for " << val_ << " Object\n"; }

  void foo() const {
    std::cout << "Calling foo() const for " << val_ << " Object\n";
  }

  // foo() & conflicts with foo() and foo() const
  // foo() const& conflicts with foo() const
  // foo() && conflicts with foo() and foo() const
  // foo() const&& conflicts with foo() const

  void bar() & { std::cout << "Calling bar() & for " << val_ << " Object\n"; }

  void bar() const& {
    std::cout << "Calling bar() const& for " << val_ << " Object\n";
  }

  void bar() && { std::cout << "Calling bar() && for " << val_ << " Object\n"; }

  void bar() const&& {
    std::cout << "Calling bar() const&& for " << val_ << " Object\n";
  }

  void baz() const {
    std::cout << "Calling baz() const for " << val_ << " Object\n";
  }

  void qux() const& {
    std::cout << "Calling qux() const& for " << val_ << " Object\n";
  }

  void qux() const&& {
    std::cout << "Calling qux() const&& for " << val_ << " Object\n";
  }

  void quux() & { std::cout << "Calling quux() & for " << val_ << " Object\n"; }

  void quux() && {
    std::cout << "Calling quux() && for " << val_ << " Object\n";
  }

  void quuz() const& {
    std::cout << "Calling quuz() const& for " << val_ << " Object\n";
  }
};

int main() {
  Object obj{"l-value"};
  obj.foo();
  obj.bar();
  obj.baz();
  obj.qux();
  obj.quux();
  obj.quuz();

  std::cout << '\n';
  const Object constObj{"const l-value"};
  constObj.foo();
  constObj.bar();
  constObj.baz();
  constObj.qux();
  std::cout << "Unable to call quux() & or quux() && on const l-value Object\n";
  constObj.quuz();

  std::cout << '\n';
  std::string rValStr{"r-value"};
  Object{rValStr}.foo();
  Object{rValStr}.bar();
  Object{rValStr}.baz();
  Object{rValStr}.qux();
  Object{rValStr}.quux();
  Object{rValStr}.quuz();

  std::cout << '\n';
  std::string constRValStr{"const r-value"};
  Object::getConstInstance(constRValStr).foo();
  Object::getConstInstance(constRValStr).bar();
  Object::getConstInstance(constRValStr).baz();
  Object::getConstInstance(constRValStr).qux();
  std::cout << "Unable to call quux() & or quux() && on const r-value Object\n";
  Object::getConstInstance(constRValStr).quuz();
}
