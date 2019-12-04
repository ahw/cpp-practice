#include <iostream>
#include <vector>
// Variables, Types, Arithmetic
// ============================

// Declarations
// ------------
double d1 = 1.1;
double d2 {2.2};
double d3 = {3.3};
std::vector<int> v1 {1, 2, 3, 6, 2, 8};
int a1[] = {1, 2, 3, 4};

// warning: ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings]
// char* s1 {"Hello this is a string"};

const char* s1 {"Hello this is a string"};

void print_all_memory() {
    const int i = 123;
    const int j = 123123;
    const int* ip = &i;

    while (ip) {
        printf("Value of *ip: %x\n", *ip);
        // It's OK to increment a const int* pointer.
        ++ip;
    }

    std::cout << "\n";

}

void print(double n) {
    printf("Printing double %f\n", n);
}

// When a string is passed to a function, only a pointer to the beginning of
// the string (char*) is actually passed.
void print(const char* p) {
    while (*p) {
        // Eventually *p will be the NULL character that terminates a string
        printf("%4d %c %p\n", *p, *p, p);
        ++p;
    }
    // This would print the final 0 NULL character
    printf("%d, %c %p\n", *p, *p, p);
}

void alter(double& d) {
    printf("Altering %f to %f %p\n", d, d + 1, d);
    d = d + 1;
}

void print(const int* v) {
    for (int i = 0; i < 14; ++i) {
        printf("%d %d\n", i, v[i]);
    }
}

int main() {
    print(s1);
    print(d1);
    alter(d1);
    print(d1);
    print(a1);
    print("Hello");
}
