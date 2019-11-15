#include<stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
typedef struct fichier fichier;
struct fichier
{
  char* ptr;
  int nbr_lines;
  int* tab_size_line;
  char** tab_ligne;
};

size_t getFilesize(const char* filename);

void* convert_file_to_table(const char* filename);

int get_nbr_lines(char* ptr_file);

fichier lines(char* ptr_file);

int min_2(int a, int b);

int min_3(int a, int b, int c);

int sum(int* T, int size);

int C(int n, int m, fichier f1, fichier f2);
