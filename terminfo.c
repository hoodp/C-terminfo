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
}

void setup()
{
  setupterm(NULL, fileno(stdout), (int *)0);
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
  //  char * cursor = tigetstr("cuf1");
  srand(time(NULL));
  int nrows = getRows();
  int random = rand();
  int result = random % nrows;
  printf("%d %d %d\n", nrows, random, random % nrows);
}

int getRows()
{
  return tigetnum("lines");
}

int getColumns()
{
  return tigetnum("cols");
}
