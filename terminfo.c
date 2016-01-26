#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_OPTIONS 5
#define MAX_OUTPUT_SIZE 32

int getOption();
int validOption(int option);
int getRows();
int getColumns();
void displayScreenSize();
void clearScreen();
void flashScreen();
void printArbitrary(int getData);

const char *options[NUM_OPTIONS] = {
  "Display the # of rows & columns",
  "Clear the screen",
  "Flash the screen",
  "Print to arbitrary location",
  "Enter data & print to arbitrary location"
};

int main()
{

  // setup the terminfo
  setupterm(NULL, fileno(stdout), (int *) 0);

  // initialize random integer generator
  srand((unsigned int) time(NULL));

  // get input option from user
  int option = getOption();

  // loop until the option is not valid
  while (validOption(option)) {

    // handle the option request
    switch (option) {
    case 0:
      displayScreenSize();
      break;
    case 1:
      clearScreen();
      break;
    case 2:
      flashScreen();
      break;
    case 3:
      printArbitrary(0);
      break;
    case 4:
      printArbitrary(1);
      break;
    default:
      printf("Not a valid entry.\n");
      exit(1);
    }
    
    // update the option index
    option = getOption();
  }

  // delete the current terminfo
  del_curterm(cur_term);
  return 0;
}

void printArbitrary(int getData)
{

  // generate a random row & column index with the current window 
  int row = rand() % getRows();
  int column = rand() % getColumns();

  // save the original cursor address
  tigetstr("sc");

  // generate new cursor address with random values as parameters
  char *mvCursor = tparm(tigetstr("cup"), row, column);

  // stores the output string
  char *output = malloc(MAX_OUTPUT_SIZE);

  // check if user input is needed
  if (getData) {

    // ask the user for input & assign to output
    printf("Enter data: ");
    scanf("%s", output);
  } else {

    // set output to the # of rows & columns the cursor was moved
    sprintf(output, "Cursor moved %d rows & %d columns", row, column);
  }

  // move the cursor
  putp(mvCursor);

  // print the output
  printf("%s\n", output);
  free(output);

  // move the cursor back to its original location 
  putp(tigetstr("rc"));
  
}

void flashScreen()
{
  putp(tigetstr("flash"));
}

void clearScreen()
{
  putp(tigetstr("clear"));
}

int getRows() 
{
  return tigetnum("lines");
}

int getColumns() 
{
  return tigetnum("cols");
}

void displayScreenSize() 
{
  printf("This screen has %d rows & %d columns.\n", getRows(), getColumns());
}

int validOption(int option)
{
  return option >= 0 && option < NUM_OPTIONS;
}

int getOption()
{
  
  // print each option
  size_t i;
  for (i = 0; i < NUM_OPTIONS; i++) {
    printf("(%lu): %s\n", i + 1, options[i]);
  }

  // get the input from the user & return the value 
  int in;
  scanf("%d", &in);

  // substract one from the input or return -1  
  return in == 0 ? -1 : in - 1;
}
