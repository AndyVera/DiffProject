//
//  para.h
//  DiffProject
//
//  Created by Andy Vera on 5/11/20.
//  Copyright © 2020 Andy Vera. All rights reserved.
//

#ifndef para_h
#define para_h

#include <stdio.h>
typedef struct para para;
struct para {
  char** base;
  int filesize;
  int start;
  int stop;
  char* firstline;   // DEBUG only
  char* secondline;
};

para* para_make(char* base[], int size, int start, int stop);
para* para_first(char* base[], int size);
para* para_next(para* p);
size_t para_filesize(para* p);
size_t para_size(para* p);
char** para_base(para* p);
char* para_info(para* p);
int   para_equal(para* p, para* q);
void para_print(para* p, void (*fp)(const char*));
void para_printfile(char* base[], int count, void (*fp)(const char*));
void printline(void);
#endif /* para_h */
