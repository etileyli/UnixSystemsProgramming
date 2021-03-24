#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_DELIMITERS "\n"
#define WORD_DELIMITERS " "

static int wordcount(char *s) {
  int count = 1;
  char *lasts;

  if (strtok_s(s, WORD_DELIMITERS, &lasts) == NULL)
    return 0;

  while (strtok_s(NULL, WORD_DELIMITERS, &lasts) != NULL)
    count++;

  return count;
}

double wordaverage(char *s) { /* return average size of words in s */

  char *lasts;
  int linecount = 1;
  char *nextline;
  int words;

  nextline = strtok_s(s, LINE_DELIMITERS, &lasts);
  if (nextline == NULL)
    return 0.0;

  words = wordcount(nextline);
  while ((nextline = strtok_s(NULL, LINE_DELIMITERS, &lasts)) != NULL) {
    words += wordcount(nextline);
    linecount++;
    }

  return (double)words/linecount;
}

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
