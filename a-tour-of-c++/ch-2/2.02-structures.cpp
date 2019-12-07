#include<iostream>

struct Vector {
    int sz; // number of elements
    double* elem; // pointer to elements
};

void init_vector(Vector& v, int s) {
    v.elem = new double[s];
    v.sz = s;
}

void print_vector(Vector& v) {
    printf("[print_vector] v: %p\n", &v);
    for (int i = 0; i < v.sz; i++)
    {
        printf("Vector element %2d: %f\n", i, v.elem[i]);
    }
}

void print_vector_copy(Vector v)
{
    printf("[print_vector_copy] v: %p\n", &v);
    print_vector(v);
}

void mutate_vector(Vector& v)
{
    printf("[mutate_vector_copy] mutating a Vector reference\n");
    v.elem[0] = 42.19;
}

void mutate_vector_copy(Vector v)
{
    // Original v
    // sz: int
    // elem: *------> array
    //                  ^
    // Copy of v        |
    // sz: int          |
    // elem: *----------+
    printf("[mutate_vector_copy] mutating a Vector copy\n");
    printf("[mutate_vector_copy] Even though the vector is passed by value, the pointer to the elements array doesn't change\n");
    v.elem[0] = 100.123;
    print_vector(v);
}

int main() {
    Vector v1;
    printf("v1: %p\n", &v1);
    init_vector(v1, 3);
    v1.elem[2] = 2.123;
    print_vector(v1);
    print_vector_copy(v1);

    mutate_vector(v1);
    print_vector(v1);

    mutate_vector_copy(v1);
    print_vector(v1);
}
