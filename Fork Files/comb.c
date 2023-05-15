#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#define ARR_SIZE 100000

int arr[ARR_SIZE];

void ParseParameters(int tempArr[]) {
  for (int i = 0, j = 1; j < ARR_SIZE + 1; i++, j++)
  arr[i] = tempArr[i];
    // sscanf(argv[j], "%d", &arr[i]);
}

int getNextGap(int gap) {
  // Shrink gap by Shrink factor
  gap = (gap * 10) / 13;
  if (gap < 1)
    return 1;
  return gap;
}

void CombSort() {
  int n = ARR_SIZE;
  int gap = n;
  int i, temp;
  int swapped = 1;

  while (gap != 1 || swapped == 1) {
    gap = getNextGap(gap);
    swapped = 0;
    for (i = 0; i < n - gap; i++) {
      if (arr[i] > arr[i + gap]) {

        temp = arr[i];
        arr[i] = arr[i + gap];
        arr[i + gap] = temp;

        swapped = 1;
      }
    }
  }
}

int main() {
  FILE *fp;
  fp = fopen("CombFork.csv", "a");
  if(fp == NULL)
    printf("ERROR!\n");

  // fprintf(fp,"time,trial\n");
  int k;
  int tempArr[ARR_SIZE];
  int id = getpid();
  double times[15];
  double timetaken1;

  srand(time(0));
  int i;
	for (i = 0; i < ARR_SIZE; i++)
	{
		tempArr[i] = rand() % 100000;
	}

  clock_t start1 = clock();

  fork();
  fork();
  fork();
  if (getpid() == id)
  {
    clock_t end1 = clock();
    timetaken1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
  }

  for (k = 0; k < 15; k++)
  {
    clock_t start = clock();
    ParseParameters(tempArr);
    CombSort();
    clock_t end = clock();

    double timetaken = ((double)(end - start) / CLOCKS_PER_SEC) + timetaken1;
    if (getpid() == id)
    {
      if(k==14)
        fprintf(fp,"%f,15\n", timetaken);
      else
        fprintf(fp, "%f,%d\n", (timetaken),(k+1));
      
      printf("Time taken by 8 \x1b[1mPROCESSES\x1b[0m:\x1b[92m %f "
            "seconds\x1b[0m\n\n", timetaken);
    }
  }
  fclose(fp);
}
