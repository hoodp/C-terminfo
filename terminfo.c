#include <curses.h>
#include <term.h>
#include <stdio.h>

#define NUM_OPTIONS 4

int getOption();
int validOption(int option);
void setup();
int getSize();
void displaySize();
void clearScreen();

int nrows, ncolumns;

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
  nrows = tigetnum("lines");
  ncolumns = tigetnum("cols");
  printf("This screen has %d rows & %d columns.\n", nrows, ncolumns);
}

void clearScreen()
{

}
