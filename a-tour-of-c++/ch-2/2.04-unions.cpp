#include<cstdio>
#include<iostream>
#include<string>

using std::string;

enum class Type { num, ptr };

struct Node {
    string data;

    // structs can have methods
    string toString()
    {
        return "this is Node toString() with data " + data;
    };
};

struct Entry {
    string name;
    Type t;
    Node* p; // Use p if t == ptr
    int i; // Use i if t === num
};

void print_entry(Entry* pe)
{
    if (pe->t == Type::num)
    {
        printf("Entry is a num type: %d\n", pe->i);
    } else if (pe->t == Type::ptr)
    {
        string s = pe->p->toString();
        // The experts recommend not doing this though
        printf("Entry is a ptr type: %s\n", pe->p->toString().c_str());
        // And doing this instead
        std::cout << "Entry is a ptr type: " << pe->p->toString() << "\n";
    }
}

int main()
{
    Entry e = Entry();
    e.t = Type::ptr;
    e.p = new Node();
    e.p->data = "local variable entry";

    Entry* f = new Entry();
    f->t = Type::ptr;
    f->p = new Node();
    f->p->data = "heap variable entry";

    Entry g = Entry();
    g.t = Type::num;

    print_entry(&e); // Entry is a ptr type: this is Node toString() with data local variable entry
    print_entry(f); // Entry is a ptr type: this is Node toString() with data heap variable entry
    print_entry(&g); // Entry is a num type: 0
}
