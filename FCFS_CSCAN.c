// 1) Write a program in C to do disk scheduling - FCFS, SCAN, C-SCAN
//--------------------------------- a) FCFS
// C++ program to demonstrate
// FCFS Disk Scheduling algorithm
#include <stdio.h>
#include <math.h>
int size = 8;
void FCFS(int arr[],int head)
{
int seek_count = 0;
int cur_track, distance;
for(int i=0;i<size;i++)
{
cur_track = arr[i];
// calculate absolute distance
distance = fabs(head - cur_track);
// increase the total count
seek_count += distance;
// accessed track is now new head
head = cur_track;
}
printf("Total number of seek operations: %d\n",seek_count);
// Seek sequence would be the same
// as request array sequence
printf("Seek Sequence is\n");
for (int i = 0; i < size; i++) {
printf("%d\n",arr[i]);
}
}
//Driver code
int main()
{
// request array
int arr[8] = { 176, 79, 34, 60, 92, 11, 41, 114 };
int head = 50;
FCFS(arr,head);
return 0;
}
// -----------------------b) SCAN
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define SIZE 8
#define DISK_SIZE 200
// Comparison function for qsort
int compare(const void *a, const void *b) {
 return (*(int*)a - *(int*)b);
}
void SCAN(int arr[], int head, char* direction)
{
 int seek_count = 0;
 int distance, cur_track;
 int* left = (int*)malloc(SIZE * sizeof(int));
 int* right = (int*)malloc(SIZE * sizeof(int));
 int left_size = 0, right_size = 0;
 int* seek_sequence = (int*)malloc(SIZE * sizeof(int));
 int seek_sequence_size = 0;
 // appending end values
 // which has to be visited
 // before reversing the direction
 if (strcmp(direction, "left") == 0)
 left[left_size++] = 0;
 else if (strcmp(direction, "right") == 0)
 right[right_size++] = DISK_SIZE - 1;
 for (int i = 0; i < SIZE; i++) {
 if (arr[i] < head)
 left[left_size++] = arr[i];
 if (arr[i] > head)
 right[right_size++] = arr[i];
 }
 // sorting combined left and right arrays
 qsort(left, left_size, sizeof(int), compare);
 qsort(right, right_size, sizeof(int), compare);
 // run the while loop two times.
 // one by one scanning right
 // and left of the head
 int run = 2;
 while (run--) {
 if (strcmp(direction, "left") == 0) {
 for (int i = left_size - 1; i >= 0; i--) {
 cur_track = left[i];
 // appending current track to seek sequence
 seek_sequence[seek_sequence_size++] = cur_track;
 // calculate absolute distance
 distance = abs(cur_track - head);
 // increase the total count
 seek_count += distance;
 // accessed track is now the new head
 head = cur_track;
 }
 strcpy(direction, "right");
 }
 else if (strcmp(direction, "right") == 0) {
 for (int i = 0; i < right_size; i++) {
 cur_track = right[i];
 // appending current track to seek sequence
 seek_sequence[seek_sequence_size++] = cur_track;
 // calculate absolute distance
 distance = abs(cur_track - head);
 // increase the total count
 seek_count += distance;
 // accessed track is now new head
 head = cur_track;
 }
 strcpy(direction, "left");
 }
 }
 printf("Total number of seek operations = %d\n", seek_count);
 printf("Seek Sequence is\n");
 for (int i = 0; i < seek_sequence_size; i++) {
 printf("%d\n", seek_sequence[i]);
 }
 free(left);
 free(right);
 free(seek_sequence);
}
int main()
{
 // request array
 int arr[SIZE] = { 176, 79, 34, 60, 92, 11, 41, 114 };
 int head = 50;
 char direction[] = "left";
 SCAN(arr, head, direction);
 return 0;
}
//---------------------------------c) C-SCAN
#include <stdio.h>
#include <stdlib.h>
int size = 8;
int disk_size = 200;
void CSCAN(int arr[], int head)
{
 int seek_count = 0;
 int distance, cur_track;
 int left[size], right[size];
 int left_size = 0, right_size = 0;
 int seek_sequence[size];
 int seek_sequence_size = 0;
 // Appending end values
 // which have to be visited
 // before reversing the direction
 left[left_size++] = 0;
 right[right_size++] = disk_size - 1;
 // Tracks on the left of the
 // head will be serviced once
 // the head comes back
 // to the beginning (left end).
 for (int i = 0; i < size; i++)
 {
 if (arr[i] < head)
 left[left_size++] = arr[i];
 if (arr[i] > head)
 right[right_size++] = arr[i];
 }
 // Sorting left and right arrays
 for (int i = 0; i < left_size - 1; i++)
 {
 for (int j = 0; j < left_size - i - 1; j++)
 {
 if (left[j] > left[j + 1])
 {
 int temp = left[j];
 left[j] = left[j + 1];
 left[j + 1] = temp;
 }
 }
 }
 for (int i = 0; i < right_size - 1; i++)
 {
 for (int j = 0; j < right_size - i - 1; j++)
 {
 if (right[j] > right[j + 1])
 {
 int temp = right[j];
 right[j] = right[j + 1];
 right[j + 1] = temp;
 }
 }
 }
 // First, service the requests
 // on the right side of the
 // head.
 for (int i = 0; i < right_size; i++)
 {
 cur_track = right[i];
 // Appending current track to seek sequence
 seek_sequence[seek_sequence_size++] = cur_track;
 // Calculate absolute distance
 distance = abs(cur_track - head);
 // Increase the total count
 seek_count += distance;
 // Accessed track is now new head
 head = cur_track;
 }
 // Once reached the right end
 // jump to the beginning.
 head = 0;
 // Adding seek count for head returning from 199 to 0
 seek_count += (disk_size - 1);
 // Now service the requests again
 // which are left.
 for (int i = 0; i < left_size; i++)
 {
 cur_track = left[i];
 // Appending current track to seek sequence
 seek_sequence[seek_sequence_size++] = cur_track;
 // Calculate absolute distance
 distance = abs(cur_track - head);
 // Increase the total count
 seek_count += distance;
 // Accessed track is now the new head
 head = cur_track;
 }
 printf("Total number of seek operations = %d\n", seek_count);
 printf("Seek Sequence is\n");
 for (int i = 0; i < seek_sequence_size; i++)
 {
 printf("%d\n", seek_sequence[i]);
 }
}
// Driver code
int main()
{
 // Request array
 int arr[] = {176, 79, 34, 60, 92, 11, 41, 114};
 int head = 50;
 printf("Initial position of head: %d\n", head);
 CSCAN(arr, head);
 return 0;
}
