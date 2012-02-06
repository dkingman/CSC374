// David Kingman
// CSC374
// HW 2

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


const int	TEXT_LEN		= 20;

const int	MIN_NUM_CHILDREN	= 1;

const int	MAX_NUM_CHILDREN	= 8;

const int	MIN_DELAY_SECS		= 4;

const int	MAX_DELAY_SECS		= 60;

#define		CHILD_PROGRAM_NAME	"./child"

int		currentNumChildren;

void interrupt_handler(int);

void child_handler(int);

// Disables Ctrl-C and displays message instead
void interrupt_handler(int signum)
{
  printf("Be a good mother and wait for ALL you children, please!\n");
}

// Handles children finished signal and displays success or failure
void child_handler(int signum)
{
  int status;
  pid_t child_pid = wait(&status);
  if(WIFEXITED(status))
    printf("Child process %d ended normally and returned %d.\n",
    child_pid, status);
  else
    printf("Child process %d met an untimely demise.\n",child_pid);

  currentNumChildren--;
}

int main()
{
  int i;
  pid_t pid[MAX_NUM_CHILDREN];
  int delay;

  // Signal handlers for Ctrl-C and child finishing
  signal(SIGINT,interrupt_handler);
  signal(SIGCHLD,child_handler);

  // Get number of children to fork from stdin
  do
  {
  puts("How many children processes do you want (1-8)? ");
  scanf("%d",&currentNumChildren);
  }
  while(currentNumChildren < MIN_NUM_CHILDREN ||
        currentNumChildren > MAX_NUM_CHILDREN);

  // Fork children and get seconds to delay from stdin
  for(i = 0; i < currentNumChildren; i++)
  {
    do
    {
    printf("How many second shall child %d delay? (%d-%d)"
    ,i+1,MIN_DELAY_SECS,MAX_DELAY_SECS);
    scanf("%d",&delay);
    }
    while(delay < MIN_DELAY_SECS || delay > MAX_DELAY_SECS);
  
    // Fork child and run child specific code
    pid[i] = fork();
    if(pid[i] == -1)
    {
      puts("Forked bad. Exiting");
      return(EXIT_FAILURE);
    }
    else if(pid[i] == 0)
    {
      char text[TEXT_LEN];

      snprintf(text,TEXT_LEN,"%d",delay);
      execl(CHILD_PROGRAM_NAME,CHILD_PROGRAM_NAME,text,NULL);
      fprintf(stderr,"Child %d couldn't find program %s!\n",
      	      getpid(),CHILD_PROGRAM_NAME
	     );
      exit(EXIT_FAILURE);
    }
  }

  // Wait until all children have finished
  while(currentNumChildren > 0)
  {
    printf("Mama \"Waiting for my BABY.\"\n");
    sleep(2);
  }

}
