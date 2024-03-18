#include <stdio.h>
#include "deque.h"

int main() {
    // Declare deque instances
    deque d1, d2;

    // Create deque instances
    if (CreateDeque(&d1) != DEQUE_SUCCESS) {
        printf("Error creating deque d1\n");
        return 1;
    }

    if (CreateDeque(&d2) != DEQUE_SUCCESS) {
        printf("Error creating deque d2\n");
        DeleteDeque(&d1); // Clean up deque d1
        return 1;
    }

    // Add elements to deque d1
    int data1 = 10;
    if (AddToBack(&d1, &data1, sizeof(data1)) != DEQUE_SUCCESS) {
        printf("Error adding element to deque d1\n");
        DeleteDeque(&d1); // Clean up deque d1
        DeleteDeque(&d2); // Clean up deque d2
        return 1;
    }

    // Add elements to deque d2
    int data2 = 20;
    if (AddToFront(&d2, &data2, sizeof(data2)) != DEQUE_SUCCESS) {
        printf("Error adding element to deque d2\n");
        DeleteDeque(&d1); // Clean up deque d1
        DeleteDeque(&d2); // Clean up deque d2
        return 1;
    }

    // Test IsEmpty for d1 (should be false)
    printf("Is deque d1 empty? %s\n", IsEmpty(&d1) ? "Yes" : "No");

    // Test IsEmpty for d2 (should be false)
    printf("Is deque d2 empty? %s\n", IsEmpty(&d2) ? "Yes" : "No");

    // Test GetFront for d1
    int *front_d1 = GetFront(&d1);
    if (front_d1 != NULL) printf("Front element of deque d1: %d\n", *front_d1);

    // Test GetBack for d2
    int *back_d2 = GetBack(&d2);
    if (back_d2 != NULL) printf("Back element of deque d2: %d\n", *back_d2);

    // Test CountObjects for d1 and d2
    printf("Number of objects in deque d1: %d\n", NumberOfObjects(&d1));
    printf("Number of objects in deque d2: %d\n", NumberOfObjects(&d2));

    // Delete elements from d1 and d2
    if (DeleteFromBack(&d1) != DEQUE_SUCCESS) {
        printf("Error deleting element from back of deque d1\n");
        DeleteDeque(&d1); // Clean up deque d1
        DeleteDeque(&d2); // Clean up deque d2
        return 1;
    }

    if (DeleteFromFront(&d2) != DEQUE_SUCCESS) {
        printf("Error deleting element from front of deque d2\n");
        DeleteDeque(&d1); // Clean up deque d1
        DeleteDeque(&d2); // Clean up deque d2
        return 1;
    }

    // Test IsEmpty for d1 (should be true)
    printf("Is deque d1 empty? %s\n", IsEmpty(&d1) ? "Yes" : "No");

    // Test IsEmpty for d2 (should be true)
    printf("Is deque d2 empty? %s\n", IsEmpty(&d2) ? "Yes" : "No");

    // Delete deque instances
    DeleteDeque(&d1);
    DeleteDeque(&d2);

    return 0;
}
