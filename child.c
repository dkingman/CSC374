// David Kingman
// CSC 374
// HW2

#include "stdio.h"
#include "signal.h"
#include "stdlib.h"

void print_usage();

void print_usage()
{ 
  fprintf(stderr,"Usage: child <numSeconds>\n");
}

int main(int argc, char* argv[])
{
  // Ignore Ctrl-C
  signal(SIGINT,SIG_IGN);
  
  if(argc < 2)
  {
    print_usage();
    return(EXIT_FAILURE);
  }

  // Validates that user input was a digit
  char seconds_char = argv[1][0];
  int is_a_digit  = isdigit(seconds_char);
  if(!is_a_digit)
  {
    print_usage();
    return(EXIT_FAILURE);
  }

  // Sleep for user specified number of seconds and print proc ID
  sleep(atoi(argv[1]));
  printf("Process %d says \"Hello\"!\n",getpid());

  return(EXIT_SUCCESS);
}
