#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Maximum number of pages the queue can hold

// Structure for the queue
typedef struct {
    int pages[MAX]; // Array to hold pages
    int front; // Index of the front of the queue
    int rear;  // Index of the rear of the queue
    int size;  // Size of the queue
} Queue;

// Function to initialize the queue
void initializeQueue(Queue *q, int size) {
    q->front = -1;  // Initially, the queue is empty, so front is -1
    q->rear = -1;   // Initially, the queue is empty, so rear is -1
    q->size = size; // Set the maximum size of the queue
}

// Function to check if the queue is full
int isFull(Queue *q) {
    // Queue is full if the next position of rear is front
    return (q->rear + 1) % q->size == q->front;
}

// Function to check if the queue is empty
int isEmpty(Queue *q) {
    // Queue is empty if front is -1
    return q->front == -1;
}

// Function to enqueue a page into the queue
void enqueue(Queue *q, int page) {
    // If the queue is full, we need to dequeue the front element
    if (isFull(q)) {
        // Move front to the next position
        q->front = (q->front + 1) % q->size;
    }
    // If the queue is empty, initialize front and rear to 0
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        // Move rear to the next position
        q->rear = (q->rear + 1) % q->size;
    }
    // Place the new page at the rear
    q->pages[q->rear] = page;
}

// Function to search for a page in the queue
int searchQueue(Queue *q, int page) {
    // If the queue is empty, return 0 (not found)
    if (isEmpty(q)) return 0;
    // Traverse the queue to search for the page
    for (int i = q->front; i != q->rear; i = (i + 1) % q->size) {
        if (q->pages[i] == page) return 1; // Page found
    }
    // Check the rear position separately
    if (q->pages[q->rear] == page) return 1; // Page found
    return 0; // Page not found
}

// Function to implement the FIFO page replacement algorithm
void fifoPageReplacement(int pages[], int n, int capacity) {
    Queue q; // Declare a queue
    initializeQueue(&q, capacity); // Initialize the queue with the given capacity
    int pageFaults = 0; // Initialize page fault count to 0

    // Loop through each page in the page reference string
    for (int i = 0; i < n; i++) {
        // If the page is not found in the queue, it's a page fault
        if (!searchQueue(&q, pages[i])) {
            enqueue(&q, pages[i]); // Enqueue the new page
            pageFaults++; // Increment the page fault count
        }

        // Print the current state of the queue
        printf("Memory state after accessing page %d: ", pages[i]);
        for (int j = q.front; j != q.rear; j = (j + 1) % q.size) {
            printf("%d ", q.pages[j]); // Print each page in the queue
        }
        printf("%d\n", q.pages[q.rear]); // Print the rear page separately
    }

    // Print the total number of page faults
    printf("Total page faults: %d\n", pageFaults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2}; // Array of pages to be accessed
    int n = sizeof(pages) / sizeof(pages[0]); // Calculate the number of pages
    int capacity = 4; // Number of frames in memory

    // Call the FIFO page replacement function
    fifoPageReplacement(pages, n, capacity);

    return 0; // Return 0 to indicate successful execution
}


