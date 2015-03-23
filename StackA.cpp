#include <cassert>
#include <iostream>

using namespace std;

template<typename Object>
class Stack {
private:
    Object *data;       // Data array
    int theSize;        // Size of the stack
    int theCapacity;    // Capacity of the stack

    // Initialize the stack
    void init() {
        theSize = 0;                    // initialize size
        theCapacity = 1;                // initialize capacity
        data = new Object[theCapacity]; // initialize data
    }

    // Delete the entire stack
    void emptyStack() { delete[] data; }

public:
    // Constructor
    Stack() { init(); }

    // Destructor
    ~Stack() { emptyStack(); }

    // Copy constructor
    Stack( const Stack& rhs ) {
        init();         // initialize the stack
        *this = rhs;    // leveraging the operator= method
    }

    // Assignment operator
    const Stack& operator=(const Stack& rhs) {
        if(this == &rhs) return *this;     // check for self-assignment
        emptyStack();                       // delete the entire stack
        init();                             // initialize the stack
        theSize = rhs.theSize;              // copy size
        theCapacity = rhs.theCapacity;      // copy capacity
        data = new Object[rhs.size()];      // create the data array
        for(int i = 0; i < rhs.size(); i++) // loop through all data
            data[i] = rhs.data[i];          // copy data
        return *this;
    }

    // Return the current size
    int size() const { return theSize; }

    // Return true if empty
    bool empty() const { return theSize == 0; }

    // Return the data at the top of the stack
    Object top() const {
        assert(!empty());
        return data[theSize - 1];
    }

    // Return data at the i-th position in the stack
    Object peek(int i) const {
        assert(i > 0 && i <= theSize);
        return data[theSize - i];
    }

    // Add to the top of the stack
    void push(const Object& x) {
        data[theSize++] = x;                        // copy x into next element
        if(theSize == theCapacity) {                // reached capacity
            theCapacity = theCapacity * 2;          // doubling the capacity
            Object *tmp = new Object[theCapacity];  // allocated new data array
            for(int i = 0; i < theSize; i++)        // loop through all data
                tmp[i] = data[i];                   // copy data over
            delete[] data;                          // delete old array
            data = tmp;                             // assign data to new array
        }
    }

    // Delete the top of the stack
    void pop() {
        if(empty()) return; // nothing to pop
        theSize--;          // decrease size counter
    }

    // Print the data of the entire stack
    void print() {
        for(int i = theSize - 1; i >= 0; i--)
            cout << data[i] << " "; // output data
        cout << endl;
    }

    // Print the data and the address of the entire stack
    void print_all() {
        for(int i = theSize - 1; i >= 0; i--){
            cout << data[i] << " ";             // output data
            cout << " (" << &data[i] << ") ";   // output address of node
        }
        cout << endl;
    }
};
