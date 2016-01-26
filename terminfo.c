#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OPTIONS 4

int getOption();
int validOption(int option);
void setup();
int getSize();
void displaySize();
void clearScreen();
void printArbitrary();
int getRows();
int getColumns();

const char * options[NUM_OPTIONS] = {
  "Display # of rows & columns",
  "Clear the screen",
  "Print to an arbitrary location",
  "Enter data & print to an arbitrary location"
};

int main()
{

  // connect to lcurses library
  setup();
  
  // holds input value 
  int option = getOption();
  int valid = validOption(option);
  while(valid) {

    // handle the option request
    switch (option) {
    case 1:
      displaySize();
      break;
    case 2: 
      clearScreen();
      break;
    case 3:
      printArbitrary();
      break;
    default:
      printf("error\n");
    }
    option = getOption();
    valid = validOption(option);
  }
  return 0;
}

void setup()
{

  // connect to terminfo
  setupterm(NULL, fileno(stdout), (int *)0);

  // setup random number generator
  srand((unsigned int) time(NULL));
}

int getOption() 
{
  
  // print each option
  size_t i;
  for (i = 0; i < sizeof(options) / sizeof(options[0]); i++) {
    printf("(%lu): %s\n", i + 1, options[i]);
  }
  
  // get input from the user & return the value 
  int in;
  scanf("%d", &in);
  return in;
}

int validOption(int option)
{
  return option > 0 && option <= NUM_OPTIONS;
}

void displaySize()
{
  int nrows, ncolumns;
  nrows = getRows();
  ncolumns = getColumns();
  printf("This screen has %d rows & %d columns.\n", nrows, ncolumns);
}

void clearScreen()
{
  char * clear = tigetstr("clear");
  printf("%s", clear);
}

void printArbitrary()
{
  char *flash = tigetstr("vb");
  printf("%s", flash);
}

void printArbitrary2() 
{

  // clear the screen so the text is visible
  //  clearScreen();
  tigetstr("cvvis");

  // setup left & right cursors
  char * cursorRight = tigetstr("cuf1");
  char * cursorDown = tigetstr("cud1");
  
  // generate a random number of spaces to move right
  int nRight = rand() % getColumns();

  // random number of rows to move down
  int nDown = rand() % getRows();

  int i;

  // move to cursor right nRight times
  for (i = 0; i < nRight; i++) {
    printf("%s", cursorRight);
  }

  // move the cursor up nDown times
  for (i = 0; i < nDown; i++) {
    printf("%s", cursorDown);
  }
  printf("%d times right cursor - %d times down cursor\n", nRight, nDown);
}

int getRows()
{
  return tigetnum("lines");
}

int getColumns()
{
  return tigetnum("cols");
}
