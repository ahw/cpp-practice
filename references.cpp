#include<iostream>
#include<stdio.h>

using namespace std;

class Foo {
    public:
        int i;
};

std::ostream& operator<<(std::ostream &strm, const Foo &a) {
  return strm << "F(" << a.i << ")";
}

int main() {
    Foo a, b;
    Foo* p1 = new Foo;
    Foo* p2 = p1;

    std::cout << "*p1 \"toString\": " << *p1 << "\n"; // F(0)
    std::cout << "*p1 \"toString\": " << *p2 << "\n"; // F(0)
    std::cout << "a \"toString\": " << a << "\n"; // F(460795941)
    std::cout << "b \"toString\": " << b << "\n"; // F(-508596144)
    printf("Pointer address of  p1 %p\n", p1); // 0x7f8291401a10
    printf("Pointer address of  p2 %p\n", p2); // 0x7f8291401a10
    printf("Pointer address of &p1 %p\n", &p1); // 0x7ffee1af7028
    printf("Pointer address of &p2 %p\n", &p2); // 0x7ffee1af7020
    printf("Pointer address of  &a %p\n", &a); // 0x7ffee1af7038
    printf("Pointer address of  &b %p\n", &b); // 0x7ffee1af7030
}
