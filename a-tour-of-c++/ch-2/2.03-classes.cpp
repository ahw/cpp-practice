#include<cstdio>
#include<exception>


class Vector {
    public:
        // Constructor
        Vector(int s):
            elem(new double[s]),
            sz{s}
        {
            // printf("Initializing a Vector\n");
        }

        ~Vector()
        {
            // printf("Vector destroyed\n");
            delete elem;
        }

        // Override the [] operator
        double& operator[](int i)
        {
            return elem[i];
        }

        // The size method
        int size()
        {
            return sz;
        }
    private:
        double* elem;
        int sz;
};

void create_vector_on_heap_without_deleting(int elementCount)
{
    Vector* u = new Vector(elementCount);
}

void create_vector_on_heap_with_deletion(int elementCount)
{
    Vector* u = new Vector(elementCount);
    delete u;
}

void memory_leak()
{
    for (int i = 0; i < 1000000; i++)
    {
        try
        {
            create_vector_on_heap_without_deleting(1000000000);
            // create_vector_on_heap_with_deletion(1000000000);
        }
        catch(std::bad_alloc& err) {
            printf("Caught bad_alloc error %s\n", err.what());
            // Either need to manually terminate() or throw the exception
            // and let the OS (?) handle by killing the process. If the
            // exception is merely caught and logged it'll do so for all
            // 1000000 iterations of this loop.
            std::terminate();
        }
    }
}

int main()
{
    // Local variable on the stack
    Vector v = Vector(2);

    // Local pointer to something on the heap
    Vector* u = new Vector(2);

    memory_leak();
}
