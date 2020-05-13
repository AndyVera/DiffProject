//
//  utils.c
//  DiffProject
//
//  Created by Andy Vera on 5/12/20.
//  Copyright © 2020 Andy Vera. All rights reserved.
//

#include "utils.h"
#include <string.h>
#include <stdlib.h>

void printleftcolumn(const char* left) {
  char buf[BUFSIZ];
  
  strcpy(buf, left);
  int j = 0, len = (int)strlen(buf) - 1;
  for (j = 0; j <= 48 - len ; ++j) { buf[len + j] = ' '; }
  //buf[len + j++] = '<';
  buf[len + j++] = '\0';
  printf("< ");
  printf("%s\n", buf);
}

void printrightcolumn(const char* right) {
  if (right == NULL) { return; }
  printf("> ");
  printf("%s",right);
}

void printboth(const char* left_right) {
  char buf[BUFSIZ];
  size_t len = strlen(left_right);
  if (len > 0) { strncpy(buf, left_right, len); }
  buf[len - 1] = '\0';
  printf("%-50s %s", buf, left_right);
}

void printleft(const char* left) {
char buf[BUFSIZ];
  
  strcpy(buf, left);
  int j = 0, len = (int)strlen(buf) - 1;
  for (j = 0; j <= 48 - len ; ++j) { buf[len + j] = ' '; }
  buf[len + j++] = '<';
  buf[len + j++] = '\0';
  printf("%s\n", buf);
}

void printright(const char* right) {
  if (right == NULL) { return; }
  printf("%50s %s", ">", right);
}

void printbothleftonly(const char* left_right) {
  char buf[BUFSIZ];
  size_t len = strlen(left_right);
  if (len > 0) { strncpy(buf, left_right, len); }
  buf[len - 1] = '\0';
  printf("%-48s %s", buf, "(\n");
}
