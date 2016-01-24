#include <curses.h>
#include <term.h>
#include <stdio.h>

/*int setupterm(char *term, int fildes, int *errret);
int del_curterm(TERMINAL *oterm);
int restartterm(char *term, int fildes, int *errret);
char *tparm(char *str, ...);
int tputs(const char *str, int affcnt, int (*putc)(int));
int putp(const char *str);
int vidputs(chtype attrs, int (*putc)(int));
int vidattr(chtype attrs);
int vid_puts(attr_t attrs, short pair, void *opts, int (*putc)(char));
int vid_attr(attr_t attrs, short pair, void *opts);
int mvcur(int oldrow, int oldcol, int newrow, int newcol);
int tigetflag(char *capname);
int tigetnum(char *capname);
char *tigetstr(char *capname);*/

int main()
{
  int nrows, ncolumns;
  setupterm(NULL, fileno(stdout), (int *)0);
  nrows = tigetnum("lines");
  ncolumns = tigetnum("cols");
  printf("This terminal has %d columns and %d rows.\n", ncolumns, nrows);
  return 0;
}
