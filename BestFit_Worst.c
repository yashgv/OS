//) Write a program to demonstrate the concept of dynamic partitioning placement 
//algorithms i.e. Best Fit, First Fit, Worst-Fit etc.
//-------------------------------------a) First-Fit
// C implementation of First - Fit algorithm 
#include<stdio.h> 
// Function to allocate memory to 
// blocks as per First fit algorithm 
void firstFit(int blockSize[], int m, int processSize[], int n) 
{ 
int i, j; 
// Stores block id of the 
// block allocated to a process 
int allocation[n]; 
// Initially no block is assigned to any process 
for(i = 0; i < n; i++) 
{ 
allocation[i] = -1; 
} 
// pick each process and find suitable blocks 
// according to its size ad assign to it 
for (i = 0; i < n; i++) //here, n -> number of processes 
{ 
for (j = 0; j < m; j++) //here, m -> number of blocks 
{ 
if (blockSize[j] >= processSize[i]) 
{ 
// allocating block j to the ith process 
allocation[i] = j; 
// Reduce available memory in this block. 
blockSize[j] -= processSize[i]; 
break; //go to the next process in the queue 
} 
} 
} 
printf("\nProcess No.\tProcess Size\tBlock no.\n"); 
for (int i = 0; i < n; i++) 
{ 
printf(" %i\t\t\t", i+1); 
printf("%i\t\t\t\t", processSize[i]); 
if (allocation[i] != -1) 
printf("%i", allocation[i] + 1); 
else
printf("Not Allocated"); 
printf("\n"); 
} 
} 
// Driver code 
int main() 
{ 
int m; //number of blocks in the memory 
int n; //number of processes in the input queue 
int blockSize[] = {100, 500, 200, 300, 600}; 
int processSize[] = {212, 417, 112, 426}; 
m = sizeof(blockSize) / sizeof(blockSize[0]); 
n = sizeof(processSize) / sizeof(processSize[0]); 
firstFit(blockSize, m, processSize, n); 
return 0 ; 
}
//--------------------------------------------------======b) Best Fit
#include <stdio.h>
// Method to allocate memory to blocks as per Best fit algorithm
void bestFit(int blockSize[], int m, int processSize[], int n)
{
 // Stores block id of the block allocated to a process
 int allocation[n];
 // Initially no block is assigned to any process
 for (int i = 0; i < n; i++)
 allocation[i] = -1;
 // Pick each process and find suitable blocks
 // according to its size and assign to it
 for (int i = 0; i < n; i++)
 {
 // Find the best fit block for the current process
 int bestIdx = -1;
 for (int j = 0; j < m; j++)
 {
 if (blockSize[j] >= processSize[i])
 {
 if (bestIdx == -1)
 bestIdx = j;
 else if (blockSize[bestIdx] > blockSize[j])
 bestIdx = j;
 }
 }
 // If we could find a block for the current process
 if (bestIdx != -1)
 {
 // Allocate block j to p[i] process
 allocation[i] = bestIdx;
 // Reduce available memory in this block
 blockSize[bestIdx] -= processSize[i];
 }
 }
 printf("\nProcess No.\tProcess Size\tBlock no.\n");
 for (int i = 0; i < n; i++)
 {
 printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
 if (allocation[i] != -1)
 printf("%d\n", allocation[i] + 1);
 else
 printf("Not Allocated\n");
 }
}
// Driver Method
int main()
{
 int blockSize[] = {100, 500, 200, 300, 600};
 int processSize[] = {212, 417, 112, 426};
 int m = sizeof(blockSize) / sizeof(blockSize[0]);
 int n = sizeof(processSize) / sizeof(processSize[0]);
 bestFit(blockSize, m, processSize, n);
 return 0;
}
//---------===========================c) Worst Fit
#include <stdio.h>
#include <string.h>
// Function to allocate memory to blocks as per worst fit algorithm
void worstFit(int blockSize[], int m, int processSize[], int n)
{
 // Stores block id of the block allocated to a process
 int allocation[n];
 // Initially no block is assigned to any process
 memset(allocation, -1, sizeof(allocation));
 // Pick each process and find suitable blocks
 // according to its size and assign to it
 for (int i = 0; i < n; i++)
 {
 // Find the worst fit block for current process
 int wstIdx = -1;
 for (int j = 0; j < m; j++)
 {
 if (blockSize[j] >= processSize[i])
 {
 if (wstIdx == -1)
 wstIdx = j;
 else if (blockSize[wstIdx] < blockSize[j])
 wstIdx = j;
 }
 }
 // If we could find a block for current process
 if (wstIdx != -1)
 {
 // Allocate block j to p[i] process
 allocation[i] = wstIdx;
 // Reduce available memory in this block
 blockSize[wstIdx] -= processSize[i];
 }
 }
 printf("\nProcess No.\tProcess Size\tBlock no.\n");
 for (int i = 0; i < n; i++)
 {
 printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
 if (allocation[i] != -1)
 printf("%d\n", allocation[i] + 1);
 else
 printf("Not Allocated\n");
 }
}
// Driver code
int main()
{
 int blockSize[] = {100, 500, 200, 300, 600};
 int processSize[] = {212, 417, 112, 426};
 int m = sizeof(blockSize) / sizeof(blockSize[0]);
 int n = sizeof(processSize) / sizeof(processSize[0]);
 worstFit(blockSize, m, processSize, n);
 return 0;
}
