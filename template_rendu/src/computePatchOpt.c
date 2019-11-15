/**
 * @file
 * \author Dorothée
 */

#include "algo_1.h"
#include <stdlib.h>
#include <assert.h>
#include <time.h>

/**
  *\fn void main(int argc, char* argv[])
  *\brief
  *\param argc Le fichier source
  *\param argc Le fichier Destination
  */
void* ptr_begin_file = 0;
int main(int argc, char* argv[])
{
  clock_t start, end;
  float ecoule;
  start = clock();
  //algo_iter("source", "target", "patch");
  algo_iter(argv[1], argv[2], argv[3]);
  end = clock();
  ecoule = ((float)end - start) / CLOCKS_PER_SEC;
  printf("%f secondes entre start et end.\n", ecoule);
}
