// https://www.sandordargo.com/blog/2024/08/21/std-ref

#include <functional>
#include <iostream>
 
void f(int& p1, int& p2, const int& p3) {
    std::cout << "In function: " << p1 << ' ' << p2 << ' ' << p3 << '\n';
    ++p1; // increments the copy of n1 stored in the function object
    ++p2; // increments the main()'s n2
    // ++p3; // compile error
}
 
int main() {
    int n1 = 1, n2 = 2, n3 = 3;
    std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));
    n1 = 10;
    n2 = 11;
    n3 = 12;
    std::cout << "Before calling f() directly: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    f(n1, n2, n3);
    std::cout << "After calling f() directly: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    std::cout << "==================\n";
    std::cout << "Before calling bound_f(): " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    bound_f();
    bound_f();
    std::cout << "After calling bound_f(): " << n1 << ' ' << n2 << ' ' << n3 << '\n';
}
