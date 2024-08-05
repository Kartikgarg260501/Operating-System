#include <stdio.h>  // Standard input-output library
#include <stdlib.h> // Standard library for memory allocation

// Function to search for a page in the memory array
int searchPage(int memory[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (memory[i] == page) { // If page is found in memory
            return i; // Return the index where the page is found
        }
    }
    return -1; // If page is not found, return -1
}

// Function to find the Least Recently Used (LRU) page
int findLRU(int time[], int n) {
    int min = time[0], pos = 0; // Initialize minimum time and position
    for (int i = 1; i < n; i++) {
        if (time[i] < min) { // If a smaller time is found
            min = time[i]; // Update minimum time
            pos = i; // Update position of least recently used page
        }
    }
    return pos; // Return the position of LRU page
}

// Function to implement LRU page replacement
void lruPageReplacement(int pages[], int n, int capacity) {
    int *memory = (int *)malloc(capacity * sizeof(int)); // Allocate memory for the pages in memory
    int *time = (int *)malloc(capacity * sizeof(int)); // Allocate memory for tracking the time of each page
    int count = 0, pageFaults = 0; // Initialize count of pages in memory and page faults
    
    // Initialize memory slots to -1 (indicating they are empty)
    for (int i = 0; i < capacity; i++) {
        memory[i] = -1;
    }
    
    // Loop through each page in the sequence
    for (int i = 0; i < n; i++) {
        int pos = searchPage(memory, capacity, pages[i]); // Search for the current page in memory
        
        if (pos == -1) { // If page is not found in memory (page fault)
            if (count < capacity) { // If there is still space in memory
                memory[count] = pages[i]; // Place the page in memory
                time[count] = i; // Record the time of insertion
                count++; // Increment count of pages in memory
            } else {
                int lru = findLRU(time, capacity); // Find the LRU page
                memory[lru] = pages[i]; // Replace LRU page with the current page
                time[lru] = i; // Update the time of the new page
            }
            pageFaults++; // Increment page fault count
        } else {
            time[pos] = i; // If page is found, update its last used time
        }
        
        // Print the current state of memory
        printf("Memory state after accessing page %d: ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (memory[j] != -1) { // Print page if it is in memory
                printf("%d ", memory[j]);
            } else {
                printf("- "); // Print - if the slot is empty
            }
        }
        printf("\n");
    }
    
    // Print the total number of page faults
    printf("Total page faults: %d\n", pageFaults);
    
    // Free the allocated memory
    free(memory);
    free(time);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2}; // Sequence of pages to be accessed
    int n = sizeof(pages) / sizeof(pages[0]); // Calculate the number of pages
    int capacity = 4; // Number of frames (slots) in memory
    
    // Call the LRU page replacement function
    lruPageReplacement(pages, n, capacity);
    
    return 0; // Indicate successful execution
}


