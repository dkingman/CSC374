#include "stdlib.h"
#include "stdio.h"


extern int* intArray;
extern count(int* array);
extern int n;

int createAndCount()
{
  intArray = (int*) calloc(n,sizeof(int));
  int i;
  for(i = 0; i < n; i++)
  {
    intArray[i] = rand() % 256;
  }

  int sum = count(intArray);
  free(intArray);

  return sum;
}
