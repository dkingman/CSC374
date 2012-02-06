/* q1.c
 */
#include <stdlib.h>
#include <stdio.h>


#define	NUM_UNIQUE_VALUES	256
#define	NUM_SORT_OPTIONS	4
typedef	unsigned int		uint;



/*  PURPOSE:  To create from the heap and return an array of 'n' unsigned
 *	integers initialized to random values between 0 to
 *	'NUM_UNIQUE_VALUES-1'.
 */
uint*	initializeBigArray	(uint	n
				)
{
  uint	i;
  uint*	dataPtr	= (int*)calloc(n,sizeof(int));

  for  (i = 0;  i < n;  i++)
    dataPtr[i] = (rand() % NUM_UNIQUE_VALUES);

  return(dataPtr);
}



/*  PURPOSE:  To sort the 'arrayLen' elements in array 'array' by the O(N^2)
 *      expected running time 'bubble-sort' algorithm.  No return value.
 */
void	inefficientBubbleSort	(uint	arrayLen,
				 uint*	array
				)
{
  uint	i;
  uint	haveSwapped;

  do
  {
    haveSwapped	= 0;

    for  (i = 0;  i < arrayLen-1;  i++)
      if  (array[i] > array[i+1])
      {
        uint	temp	= array[i];

	array[i]	= array[i+1];
	array[i+1]	= temp;
	haveSwapped	= 1;
      }

  }
  while  (haveSwapped);

}



/*  PURPOSE:  To return the number of times that 'number' appears in array
 *	'array' of length 'arrayLen'.
 */
uint	countNum	(uint		arrayLen,
			 const uint*	array,
			 uint		number
			)
{
  uint	count	= 0;
  uint	i;

  for  (i = 0;  i < arrayLen;  i++)
    if  (array[i] == number)
      count++;

  return(count);
}


/*  PURPOSE: To compute and return some arbitrary function that came out of the
 *	mind of Joe Phillips based upon array of integers 'array' of length
 *	'arrayLen'.
 */
uint	uselessCount	(uint	arrayLen,
			 uint*	array
			)
{
  uint	i;
  uint	j;
  uint	sum = 0;

  for  (i = 0;  i < arrayLen/2;  i++)
    for  (j = 0;  j < arrayLen;  j++)
        if  (array[i*2] == array[j])
          sum += countNum(arrayLen,array,6);

  inefficientBubbleSort(arrayLen,array);

  for  (i = 0;  i < arrayLen/2;  i++)
    for  (j = 0;  j < arrayLen;  j++)
        if  (array[i*2] == array[j])
          sum -= countNum(arrayLen,array,7);
  
  return(sum);
}



/*  PURPOSE:  To compute and print the value of some arbitrary function
 *	thought of by Joe Phillips.  Ignores parameters.  Returns 'EXIT_SUCCESS'
 *	to OS.
 */
int	main	(int argc, const char*	argv[])
{
  uint	n	= 18000;
  uint*	intArray= initializeBigArray(n);

  printf("Useless value == %d\n",uselessCount(n,intArray));
  free(intArray);
  return(EXIT_SUCCESS);
}
