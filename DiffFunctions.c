//
//  DiffFunctions.c
//  DiffProject
//
//  Created by Andy Vera on 5/11/20.
//  Copyright © 2020 Andy Vera. All rights reserved.
//

#include "DiffFunctions.h"
#include "para.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXSTRINGS 1024
#define MAXPARAS 4096

void printOptions(){
    printf("\nUsage: ./diff option FILE1 FILE2\n");
    printf("Purpose: Compare TWO Files and prints out if they're the same or different and the differences\n");
    printf("\n\n            OPTIONS:                                DESCRIPTION:\n");
    printf("    -v :                         shows the version info of Diff Program\n\n");
    printf("    -q :                         reports only whether files are different under one column;\n");
    printf("                                 silent if they are the same\n\n");
    printf("    -s :                         reports if files are the same; if not prints out the differences\n");
    printf("                                 under one column\n\n");
    printf("    -s -q :                      reports identical if the files are identical and different if the file\n");
    printf("                                 are different; doesn't print differences\n\n");
    printf("    file1 file2 :                default behaivor; prints out differences under one column; silent if\n");
    printf("                                 they're the same\n\n");
    printf("    -y :                         prints out differences using < and > to show to which file it belongs to\n");
    printf("                                 and similarities side by side\n\n");
    printf("    -y --left-column :           shows the differences using < and > to show to which file it belongs to and (\n");
    printf("                                 if a line from the first file is found in the second file side by side\n\n");
    printf("    -y --suppress-common-lines : prints out the differences side by side using < and > to show to which file it\n");
    printf("                                 belongs to and doesn't show similarites\n\n");
}
void printVersion(){
    printf("\nDiff Version 1.0\n");
    printf("Copyright (C) 2020 CSUF\n");
    printf("Written by Andy Vera\n\n");
    exit(2);
}

void printErrorInput(){
    printf("\nMissing operant after diff\n");
    printf("To see all option try './diff --help' to list all options\n\n");
}

void printDifferent(const char* leftfile, const char* rightfile){
    char leftstring[BUFSIZ];
    char rightstring[BUFSIZ];
    memset(leftstring, 0, sizeof(leftstring));
    memset(rightstring, 0, sizeof(rightstring));
    
    FILE* left = fopen(leftfile, "r");
    FILE* right = fopen(rightfile, "r");
    
    if(left == NULL || right == NULL){
        fprintf(stderr, "Either file cannot be opened\n");
        exit(3);
    }
    
    while(fscanf(left, "%s", leftstring) != EOF && fscanf(right, "%s", rightstring) != EOF){
        if(strcmp(leftstring, rightstring) != 0){
            printf("\n%s and %s are not identical\n\n", leftfile, rightfile); exit(4);
        }
    }
}

void printSame(const char* leftfile, const char* rightfile){
    char leftstring[BUFSIZ];
    char rightstring[BUFSIZ];
    memset(leftstring, 0, sizeof(leftstring));
    memset(rightstring, 0, sizeof(rightstring));
    
    FILE* left = fopen(leftfile, "r");
    FILE* right = fopen(rightfile, "r");
    
    if(left == NULL || right == NULL){
         fprintf(stderr, "Either file cannot be opened\n");
         exit(3);
     }
    while(fscanf(left, "%s", leftstring) != EOF && fscanf(right, "%s", rightstring) != EOF){
        if(strcmp(leftstring, rightstring) != 0){
            fclose(left); fclose(right);
            printDifferences(leftfile, rightfile);
            exit(4);
        }
    }
    printf("\n%s and %s are identitical\n\n", leftfile, rightfile);
    exit(4);
    
}

char buf[BUFSIZ];
char *strings1[MAXSTRINGS], *strings2[MAXSTRINGS];
int count1 = 0, count2 = 0, different = 0;

void loadfiles(const char* filename1, const char* filename2) {
  memset(buf, 0, sizeof(buf));
  memset(strings1, 0, sizeof(strings1));
  memset(strings2, 0, sizeof(strings2));
  
  FILE *fin1 = fopen(filename1, "r");
  FILE *fin2 = fopen(filename2, "r");
  
  while (!feof(fin1) && fgets(buf, BUFSIZ, fin1) != NULL) { strings1[count1++] = strdup(buf); }  fclose(fin1);
  while (!feof(fin2) && fgets(buf, BUFSIZ, fin2) != NULL) { strings2[count2++] = strdup(buf); }  fclose(fin2);
  
  if (count1 != count2) { different = 1;  return; }
  for (int i = 0, j = 0; i < count1 && j < count2;  ++i, ++j) {
    if (strcmp(strings1[i], strings2[j]) != 0) { different = 1;  return; }
  }
}

void printDifferences(const char* leftfile, const char* rightfile){
    loadfiles(leftfile, rightfile);
    para* p = para_first(strings1, count1);
     para* q = para_first(strings2, count2);
     int foundmatch = 0;

     para* qlast = q;
     while (p != NULL) {
       qlast = q;
       foundmatch = 0;
       while (q != NULL && (foundmatch = para_equal(p, q)) == 0) {
         q = para_next(q);
       }
       q = qlast;

       if (foundmatch) {
         while ((foundmatch = para_equal(p, q)) == 0) {
           para_print(q, printrightcolumn);
           q = para_next(q);
           qlast = q;
             printf("\n");
         }
         //para_print(q, printboth);
         p = para_next(p);
         q = para_next(q);
       } else {
         para_print(p, printleftcolumn);
         p = para_next(p);
           printf("\n");
       }
     }
     while (q != NULL) {
       para_print(q, printrightcolumn);
       q = para_next(q);
     }
    }

void printSameOrDifferent(const char* leftfile, const char* rightfile){
    char leftstring[BUFSIZ];
    char rightstring[BUFSIZ];
    memset(leftstring, 0, sizeof(leftstring));
    memset(rightstring, 0, sizeof(rightstring));
    
    FILE* left = fopen(leftfile, "r");
    FILE* right = fopen(rightfile, "r");
    
    if(left == NULL || right == NULL){
        fprintf(stderr, "Either file cannot be opened\n");
        exit(3);
    }
    
    while(fscanf(left, "%s", leftstring) != EOF && fscanf(right, "%s", rightstring) != EOF){
        if(strcmp(leftstring, rightstring) != 0){
            printf("\n%s and %s are not identical\n\n", leftfile, rightfile); exit(4);
        }
    }
    printf("\n%s and %s are identical\n\n", leftfile, rightfile);
}

void printDefaultMode(const char* leftfile, const char* rightfile){
    printDifferences(leftfile, rightfile);
}

void printSidebySide(const char* leftfile, const char* rightfile){
    loadfiles(leftfile, rightfile);
    para* p = para_first(strings1, count1);
     para* q = para_first(strings2, count2);
     int foundmatch = 0;

     para* qlast = q;
     while (p != NULL) {
       qlast = q;
       foundmatch = 0;
       while (q != NULL && (foundmatch = para_equal(p, q)) == 0) {
         q = para_next(q);
       }
       q = qlast;

       if (foundmatch) {
         while ((foundmatch = para_equal(p, q)) == 0) {
           para_print(q, printright);
           q = para_next(q);
           qlast = q;
         }
         para_print(q, printboth);
         p = para_next(p);
         q = para_next(q);
       } else {
         para_print(p, printleft);
         p = para_next(p);
       }
     }
     while (q != NULL) {
       para_print(q, printright);
       q = para_next(q);
     }
}

void printLeftColumn(const char* leftfile, const char* rightfile){
    loadfiles(leftfile, rightfile);
    para* p = para_first(strings1, count1);
    para* q = para_first(strings2, count2);
    int foundmatch = 0;

    para* qlast = q;
        while (p != NULL) {
          qlast = q;
          foundmatch = 0;
          while (q != NULL && (foundmatch = para_equal(p, q)) == 0) {
            q = para_next(q);
          }
          q = qlast;

          if (foundmatch) {
            while ((foundmatch = para_equal(p, q)) == 0) {
              para_print(q, printright);
              q = para_next(q);
              qlast = q;
            }
            para_print(q, printbothleftonly);
            p = para_next(p);
            q = para_next(q);
          } else {
            para_print(p, printleft);
            p = para_next(p);
          }
        }
        while (q != NULL) {
          para_print(q, printright);
          q = para_next(q);
        }
}

void printNonSuppressedLines(const char* leftfile, const char* rightfile){
    loadfiles(leftfile, rightfile);
    para* p = para_first(strings1, count1);
    para* q = para_first(strings2, count2);
    int foundmatch = 0;

    para* qlast = q;
        while (p != NULL) {
          qlast = q;
          foundmatch = 0;
          while (q != NULL && (foundmatch = para_equal(p, q)) == 0) {
            q = para_next(q);
          }
          q = qlast;

          if (foundmatch) {
            while ((foundmatch = para_equal(p, q)) == 0) {
              para_print(q, printright);
              q = para_next(q);
              qlast = q;
            }
            //para_print(q, printbothleftonly);
            p = para_next(p);
            q = para_next(q);
          } else {
            para_print(p, printleft);
            p = para_next(p);
          }
        }
        while (q != NULL) {
          para_print(q, printright);
          q = para_next(q);
        }
}
