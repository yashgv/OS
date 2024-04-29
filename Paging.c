// Write a program in C demonstrate the concept of page replacement policies for 
handling page faults eg: FIFO, LRU etc.
//-----------------------------a) FIFO
#include <stdio.h>
#include <stdlib.h>
// Define a structure for queue
struct Queue
{
 int front, rear, size;
 unsigned capacity;
 int *array;
};
// Function to create a queue of given capacity
struct Queue *createQueue(unsigned capacity)
{
 struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
 queue->capacity = capacity;
 queue->front = queue->size = 0;
 queue->rear = capacity - 1; // Important for the circular queue
 queue->array = (int *)malloc(queue->capacity * sizeof(int));
 return queue;
}
// Queue is full when size becomes equal to the capacity
int isFull(struct Queue *queue)
{
 return (queue->size == queue->capacity);
}
// Queue is empty when size is 0
int isEmpty(struct Queue *queue)
{
 return (queue->size == 0);
}
// Function to add an item to the queue
void enqueue(struct Queue *queue, int item)
{
 if (isFull(queue))
 return;
 queue->rear = (queue->rear + 1) % queue->capacity;
 queue->array[queue->rear] = item;
 queue->size = queue->size + 1;
}
// Function to remove an item from queue
int dequeue(struct Queue *queue)
{
 if (isEmpty(queue))
 return -1;
 int item = queue->array[queue->front];
 queue->front = (queue->front + 1) % queue->capacity;
 queue->size = queue->size - 1;
 return item;
}
// Function to check if an item is present in the queue
int isPresent(struct Queue *queue, int item)
{
 for (int i = 0; i < queue->size; i++)
 {
 if (queue->array[i] == item)
 return 1;
 }
 return 0;
}
// Function to find page faults using FIFO
int pageFaults(int pages[], int n, int capacity)
{
 struct Queue *queue = createQueue(capacity);
 int page_faults = 0;
 for (int i = 0; i < n; i++)
 {
 // Check if the set can hold more pages
 if (!isFull(queue))
 {
 // Insert it into queue if not present already which represents page fault
 if (!isPresent(queue, pages[i]))
 {
 // Insert the current page into the queue
 enqueue(queue, pages[i]);
 // Increment page fault
 page_faults++;
 }
 }
 // If the queue is full then need to perform FIFO
 else
 {
 // Check if current page is not already present in the queue
 if (!isPresent(queue, pages[i]))
 {
 // Remove the first page from the queue
 dequeue(queue);
 // Insert the current page into the queue
 enqueue(queue, pages[i]);
 // Increment page faults
 page_faults++;
 }
 }
 }
 free(queue->array);
 free(queue);
 return page_faults;
}
// Driver code
int main()
{
 int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
 int n = sizeof(pages) / sizeof(pages[0]);
 int capacity = 4;
 printf("%d\n", pageFaults(pages, n, capacity));
 return 0;
}
//-------------------------------b) LRU
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
// Function to find page faults using indexes
int pageFaults(int pages[], int n, int capacity)
{
 // To represent set of current pages.
 int *s = (int *)malloc(capacity * sizeof(int));
 int *indexes = (int *)malloc(n * sizeof(int));
 int page_faults = 0;
 // Initialize set and indexes array
 for (int i = 0; i < capacity; i++)
 s[i] = -1; // Initialize set with -1 (indicating empty)
 for (int i = 0; i < n; i++)
 indexes[i] = -1; // Initialize indexes with -1
 // Start from initial page
 for (int i = 0; i < n; i++)
 {
 // Check if the set can hold more pages
 if (s[pages[i]] == -1)
 {
 // Insert it into set if not present
 // already which represents page fault
 s[pages[i]] = i;
 // Increment page fault
 page_faults++;
 }
 // If the set is full then need to perform LRU
 else
 {
 // Find the least recently used page
 int lru = INT_MAX, val;
 for (int j = 0; j < capacity; j++)
 {
 if (s[j] < lru)
 {
 lru = s[j];
 val = j;
 }
 }
 // Remove the LRU page from the set
 s[val] = -1;
 // Insert the current page
 s[pages[i]] = i;
 // Increment page faults
 page_faults++;
 }
 }
 free(s);
 free(indexes);
 return page_faults;
}
// Driver code
int main()
{
 int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
 int n = sizeof(pages) / sizeof(pages[0]);
 int capacity = 4;
 printf("%d\n", pageFaults(pages, n, capacity));
 return 0;
}
//--------------------------------c) Optimal
#include <stdio.h>
#include <stdbool.h>
// Function to check whether a page exists
// in a frame or not
bool search(int key, int fr[], int fr_size)
{
 for (int i = 0; i < fr_size; i++)
 {
 if (fr[i] == key)
 return true;
 }
 return false;
}
// Function to find the frame that will not be used
// recently in future after given index in pg[0..pn-1]
int predict(int pg[], int pn, int fr[], int fr_size, int index)
{
 // Store the index of pages which are going
 // to be used recently in future
 int res = -1, farthest = index;
 for (int i = 0; i < fr_size; i++)
 {
 int j;
 for (j = index; j < pn; j++)
 {
 if (fr[i] == pg[j])
 {
 if (j > farthest)
 {
 farthest = j;
 res = i;
 }
 break;
 }
 }
 // If a page is never referenced in future,
 // return it.
 if (j == pn)
 return i;
 }
 // If all of the frames were not in future,
 // return any of them, we return 0. Otherwise
 // we return res.
 return (res == -1) ? 0 : res;
}
void optimalPage(int pg[], int pn, int fn)
{
 // Create an array for given number of
 // frames and initialize it as empty.
 int fr[fn];
 int fr_size = 0;
 // Traverse through page reference array
 // and check for miss and hit.
 int hit = 0;
 for (int i = 0; i < pn; i++)
 {
 // Page found in a frame : HIT
 if (search(pg[i], fr, fr_size))
 {
 hit++;
 continue;
 }
 // Page not found in a frame : MISS
 // If there is space available in frames.
 if (fr_size < fn)
 {
 fr[fr_size] = pg[i];
 fr_size++;
 }
 // Find the page to be replaced.
 else
 {
 int j = predict(pg, pn, fr, fr_size, i + 1);
 fr[j] = pg[i];
 }
 }
 printf("No. of hits = %d\n", hit);
 printf("No. of misses = %d\n", pn - hit);
}
// Driver Function
int main()
{
 int pg[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
 int pn = sizeof(pg) / sizeof(pg[0]);
 int fn = 4;
 optimalPage(pg, pn, fn);
 return 0;
}
