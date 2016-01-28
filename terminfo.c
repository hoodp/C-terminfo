/*****************************************************************************
* The following program provides control of some terminal features by using the
* terminfo API. 
*
* @author Paul Hood
* @version January 28, 2016
*****************************************************************************/
#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define NUM_OPTIONS 6
#define MAX_OUTPUT_SIZE 32

int getOption();
int validOption(int option);
int getRows();
int getColumns();
void displayScreenSize();
void clearScreen();
void flashScreen();
void printArbitrary(int getData);
void printOptions();

/** Array of strings that represent possible options a user can choose from */
const char *options[NUM_OPTIONS] = {
	"Display the # of rows & columns",
	"Clear the screen",
	"Flash the screen",
	"Print to arbitrary location",
	"Enter data & print to arbitrary location",
	"Show all options"
};

/******************************************************************************
* Controls the flow of the program. It retrieves input from the user until an
* invalid option is entered.
* @return The exit status of the program. 
******************************************************************************/
int main()
{

	// setup the terminfo
	setupterm(NULL, fileno(stdout), (int *) 0);

	// initialize random integer generator
	srand((unsigned int) time(NULL));

	// get input option from user
	int option = getOption(1);

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
			case 5:
				option = getOption(1);
				continue;
			default:
				printf("Not a valid entry.\n");
				exit(1);
		}

		// update the option index
		option = getOption(0);
	}

	// delete the current terminfo
	del_curterm(cur_term);
	return 0;
}

/******************************************************************************
* Prints to an arbitary location on the screen. 
* @param getData Boolean value to print the cursor location or to get data 
* from the user.	 
******************************************************************************/
void printArbitrary(int getData)
{

	// generate a random row & column index with the current window 
	int row = rand() % getRows();
	int column = rand() % getColumns();

	// stores the output string
	char *output = malloc(MAX_OUTPUT_SIZE);

	// check if user input is needed
	if (getData) {

		// ask the user for input & assign to output
		printf("Enter data: ");
		scanf("%s", output);
	} else {

		// set output to the # of rows & columns the cursor was moved
		sprintf(output, "Cursor at row %d rows & column %d", row, column);
	}

	// substract the size of the output from the column width
	column -= strlen(output);

	// save the current cursor position
	putp(tigetstr("sc"));

	// generate new cursor address with random values as parameters
	char *mvCursor = tparm(tigetstr("cup"), row, column);

	// move the cursor
	putp(mvCursor);

	// print the output
	printf("%s\n", output);
	free(output);

	putp(tigetstr("rc"));
}

/******************************************************************************
* Flashes the screen. 
******************************************************************************/
void flashScreen()
{
	putp(tigetstr("flash"));
}

/******************************************************************************
* Clears the screen.
******************************************************************************/
void clearScreen()
{
	putp(tigetstr("clear"));
}

/******************************************************************************
* Retrieves the number of rows in the terminal.
* @return Integer value of the number of rows.
******************************************************************************/
int getRows() 
{
	return tigetnum("lines");
}

/******************************************************************************
* Retrieves the number of columns in the terminal.
* @return Integer value of the number of columns.
******************************************************************************/
int getColumns() 
{
	return tigetnum("cols");
}

/******************************************************************************
* Prints the screen size by calling the getRows() and getColumns() functions. 
******************************************************************************/
void displayScreenSize() 
{
	printf("This screen has %d rows & %d columns.\n", getRows(), getColumns());
}

/******************************************************************************
* Determines if an option is within an accepted range.
* @param option Index from the user.
* @return True if the index is within the range of options. 
******************************************************************************/
int validOption(int option)
{
	return option >= 0 && option < NUM_OPTIONS;
}

/******************************************************************************
* Prints all of the available options that the user can choose from.
* @param showAll Passed to printOptions method to output the list of options. 
******************************************************************************/
int getOption(int showAll)
{

	// show the list of options
	printOptions(showAll);

	// get the input from the user & return the value 
	int in;
	scanf("%d", &in);

	// substract one from the input or return -1  
	return in == 0 ? -1 : in - 1;
}

/******************************************************************************
* Prints all of the available options that the user can choose from.
* @param showAll Show list of options or just the range.
******************************************************************************/
void printOptions(int showAll)
{
  
	// check of all options should be shown
	if (showAll) {

		// print each option value
		size_t i;
		for (i = 0; i < NUM_OPTIONS; i++) {
			printf("(%lu): %s\n", i + 1, options[i]);
		}
	} 

	// show range of options
	printf("[1-6]: ");
}