#include "deque.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//structure for each object of deque
struct object {
    void *data;
    struct object *next; //pointer to the next object
    struct object *prev; //pointer to the previous object
};

//first and last objects are initialized
struct object *first = NULL;
struct object *last = NULL;


//////////////////////////////////////////////////////////////////////////////////////

//function allocates dynamic memory and checks whether it was successful
//takes the size of the element and serves as a pointer to allocated memory
void *MallocAndCheck(size_t size, deque_error_code *err) 
{
    void *ptr = malloc(size);
    if (ptr == NULL) {
        *err = DEQUE_ERROR_MALLOC_FAILURE; // Set error code for malloc failure
    }
    else {
        *err = DEQUE_SUCCESS; // Set success if allocation is successful
    }
    return ptr;
}

// Function to create an empty deque
deque_error_code CreateDeque(deque *d) 
{
    if (d == NULL) return DEQUE_ERROR_NULL_POINTER;

    d->first = NULL;
    d->last = NULL;

    return DEQUE_SUCCESS;
}

// Function to delete deque by freeing the memory
void DeleteDeque(deque *d)
{
    struct object *current = d->first;
    struct object *nextObject;

    while (current != NULL)
    {
        nextObject = current->next;
        free(current->data);
        free(current);
        current = nextObject;
    }

    d->first = NULL;
    d->last = NULL;
}

// Function to add an object to the back of the deque
deque_error_code AddToBack(deque *d, void *data, size_t dataSize) {
    if (d == NULL) return DEQUE_ERROR_NULL_POINTER;

    struct object *newObject = (struct object *)malloc(sizeof(struct object));
    if (newObject == NULL) return DEQUE_ERROR_MALLOC_FAILURE;

    newObject->data = malloc(dataSize);
    if (newObject->data == NULL) {
        free(newObject);
        return DEQUE_ERROR_MALLOC_FAILURE;
    }
    memcpy(newObject->data, data, dataSize);

    newObject->next = NULL;

    if (d->last == NULL) {
        newObject->prev = NULL;
        d->first = newObject;
        d->last = newObject;
    }
    else {
        newObject->prev = d->last;
        d->last->next = newObject;
        d->last = newObject;
    }

    return DEQUE_SUCCESS;
}

// Function to add an object to the front of the deque
deque_error_code AddToFront(deque *d, void *data, size_t dataSize) {
    if (d == NULL) return DEQUE_ERROR_NULL_POINTER;

    struct object *newObject = (struct object *)malloc(sizeof(struct object));
    if (newObject == NULL) return DEQUE_ERROR_MALLOC_FAILURE;

    newObject->data = malloc(dataSize);
    if (newObject->data == NULL) {
        free(newObject);
        return DEQUE_ERROR_MALLOC_FAILURE;
    }
    memcpy(newObject->data, data, dataSize);

    newObject->prev = NULL;
    newObject->next = d->first;
    if (d->first != NULL)
        d->first->prev = newObject;
    d->first = newObject;
    if (d->last == NULL)
        d->last = newObject;

    return DEQUE_SUCCESS;
}

// Function to count and print out the number of objects in deque
int NumberOfObjects(deque *d)
{
    int count = 0;
    struct object *current = d->first;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

// Function to delete the last object from the deque
deque_error_code DeleteFromBack(deque *d) {
    if (d == NULL) return DEQUE_ERROR_NULL_POINTER;
    if (d->last == NULL) return DEQUE_ERROR_EMPTY; // Check if deque is empty

    struct object *current = d->last;

    if (d->last->prev != NULL) // Check if there are more elements before the last one
        d->last->prev->next = NULL;
    else
        d->first = NULL; // If there's only one element, update 'first' as well

    d->last = d->last->prev; // Move 'last' pointer to the previous element

    free(current->data);
    free(current);

    return DEQUE_SUCCESS;
}

// Function to delete the first object from the deque
deque_error_code DeleteFromFront(deque *d) {
    if (d == NULL) return DEQUE_ERROR_NULL_POINTER;
    if (d->first == NULL) return DEQUE_ERROR_EMPTY; // Check if deque is empty

    struct object *current = d->first;

    if (d->first->next != NULL) // Check if there are more elements after the first one
        d->first->next->prev = NULL;
    else
        d->last = NULL; // If there's only one element, update 'last' as well

    d->first = d->first->next; // Move 'first' pointer to the next element

    free(current->data);
    free(current);

    return DEQUE_SUCCESS;
}

// Function to check whether the deque is empty or not
bool IsEmpty(deque *d)
{
    return (d->first == NULL && d->last == NULL);
}

// Function to check whether the deque is full
bool isFull(deque *d) {
    // Allocate memory for a new object
    struct object *newObject = malloc(sizeof(struct object));
    if (newObject == NULL)
        return true;
    else
    {
        free(newObject);
        return false;
    }
}

// Function to get the element at the front of the deque without deleting it
void *GetFront(const deque *d) 
{
    if (d == NULL || d->first == NULL) return NULL;
    return d->first->data;
}

// Function to get the element at the front of the deque without deleting it
void *GetBack(const deque *d) 
{
    if (d == NULL || d->last == NULL) return NULL;
    return d->last->data;
}