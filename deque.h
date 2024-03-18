#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>

//deque data structure
typedef struct {
    struct object *first;
    struct object *last;
} deque;

typedef enum {
    DEQUE_SUCCESS = 0,              // No error
    DEQUE_ERROR_NULL_POINTER = -1,  // Null pointer error
    DEQUE_ERROR_MALLOC_FAILURE = -2,// Memory allocation failure
    DEQUE_ERROR_FULL = -3,          // Deque is full
    DEQUE_ERROR_EMPTY = -4,         // Deque is empty
} deque_error_code;

//function allocates dynamic memory and checks whether it was successful
//takes the size of the element and serves as a pointer to allocated memory
void *MallocAndCheck(size_t size);

// Function to create an empty deque
deque_error_code CreateDeque(deque *d);

// Function to delete deque by freeing the memory
void DeleteDeque(deque *d);

// Function to add an object to the end of deque
deque_error_code AddToBack(deque *d, void *data, size_t dataSize);

// Function to add an object to the front of deque
deque_error_code AddToFront(deque *d, void *data, size_t dataSize);

// Function to count and print out the number of objects in deque
int NumberOfObjects(deque *d);

// Function to delete the last object of deque
deque_error_code DeleteFromBack(deque *d);

// Function to delete the first object of deque
deque_error_code DeleteFromFront(deque *d);

// Function to check whether the deque is empty or not
bool IsEmpty(deque *d);

// Function to check whether the deque is full
bool isFull(deque *d);

// Function to get the element at the front of the deque without deleting it
void *GetFront(deque *d);

// Function to get the element at the back of the deque without deleting it
void *GetBack(deque *d);


#endif /* DEQUE.H */
