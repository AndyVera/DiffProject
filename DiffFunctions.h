
#ifndef DiffFunctions_h
#define DiffFunctions_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printOptions(void);
void printVersion(void);
void printErrorInput(void);
void printDifferent(const char* leftfile, const char* rightfile);
void printSame(const char* leftfile, const char* rightfile);
void printDifferences(const char* leftfile, const char* rightfile);
void printSameOrDifferent(const char* leftfile, const char* rightfile);
void printDefaultMode(const char* leftfile, const char* rightfile);
void printSidebySide(const char* leftfile, const char* rightfile);
void printLeftColumn(const char* leftfile, const char* rightfile);
void printNonSuppressedLines(const char* leftfile, const char* rightfile);

#endif /* DiffFunctions_h */
