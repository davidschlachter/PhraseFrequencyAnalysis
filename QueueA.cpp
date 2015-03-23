#include <cassert>
#include <iostream>

using namespace std;

template<typename Object>
class Queue {
private:
    Object *data;       // Data array
    int theSize;        // Size of the queue
    int first;          // Index of the front
    int last;           // Index of the rear
    int theCapacity;    // Capacity of the queue

    // Initialize the queue
    void init() {
        theSize = 0;                    // Initialize the size
        first = 0;                      // index of the front
        last = -1;                      // Index of the rear
        theCapacity = 1;                // initialize capacity
        data = new Object[theCapacity]; // initialize data
    }

    // Delete the entire queue
    void emptyQueue() { delete[] data; }

    // Circularly determine the next index
    int next_index(int i) const { return (i+1) % theCapacity; }

public:
    // Constructor
    Queue() { init(); }

    // Destructor
    ~Queue() { emptyQueue(); }

    // Copy Constructor
    Queue( const Queue& rhs ) {
        init();         // initialize the queue
        *this = rhs;    // leveraging the operator= method
    }

    // Assignment operator
    const Queue& operator=( const Queue& rhs ) {
        if( this == &rhs )  return *this;       // check for self-assignment
        emptyQueue();                           // delete the entire queue
        init();                                 // initialize the queue
        theSize = rhs.theSize;                  // copy size
        first = rhs.first;                      // copy front index
        last = rhs.last;                        // copy rear index
        theCapacity = rhs.theCapacity;          // copy capacity
        data = new Object[rhs.theCapacity];     // create the data array
        // loop through all data
        for( int i = first, j = 0; j < rhs.size(); j++, i = next_index(i) ) //note the commas to perform multiple tasks
            data[i] = rhs.data[i];              // copy data
        return *this;
    }

    // Return the current size
    int size() const {  return theSize; }

    // Return true if empty
    bool empty() const {    return theSize == 0;   }

    // Return the data at the front of the queue
    Object front() const {
        assert(!empty());
        return data[first];
    }

    // Return the data at the i-th position in the queue
    Object peek(int i) const {
        assert(i > 0 && i <= theSize);
        int pi = first;
        for( int j = 1; j <1; j++) pi = next_index(pi);
        return data[pi];
    }

    // Add to the rear of the queue
    void push( const Object& x ) {
        if(theSize == theCapacity) {                // reached capacity
            int newCapacity = theCapacity * 2;      // doubling the capacity
            Object *tmp = new Object[newCapacity];  // allocated new data array
            // loop through all data
            for( int i = first, j = 0; j< theSize; j++, i = next_index(i) )
                tmp[j] = data[i];                   // copy data over
            delete[] data;                          // delete old data
            data = tmp;                             // assign data to new array
            first = 0;                              // reset first index
            last = theSize - 1;                     // reset last index
            theCapacity = newCapacity;              // set capacity
        }
        last = next_index(last);                    // get the next index
        data[last] = x;                             // copy x into next element
        theSize++;                                  // increase the size
    }

    // Delete the front of the queue
    void pop() {
        if(empty()) return;         // nothing to pop
        first = next_index(first);  // get the next index
        theSize--;                  // decrease size counter
    }

    // Print the data of the entire queue
    void print() {
        // loop through all data
        for( int i = first, j = 0; j < size(); j++, i = next_index(i) )
            cout << data[i] << " "; // output data
        cout << endl;
    }

    // Print the data and address of the entire queue
    void print_all() {
        // loop through all data
        for( int i = first, j = 0; j < size(); j++, i = next_index(i) ) {
            cout << data[i] << " ";             // output data
            cout << " (" << &data[i] << ") ";   // output address of node
        }
        cout << endl;
    }
};
