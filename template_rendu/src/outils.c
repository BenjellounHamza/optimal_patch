/**
 * @file
 * \author Benjelloun hamza, Ait lahmouch Nadir
 */

#include "outils.h"
extern void* ptr_begin_file;
/**
  *\fn size_t getFilesize(const char* filename)
  *\brief Retourne la taille du fichier qu'on passe en paramètre
  *\param filename Le nom du fichier dont on veut la taille
  *\return Retourne la taille d'un fichier (size_t)
  */
size_t getFilesize(const char* filename)
{
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

/**
  *\fn void* convert_file_to_table(const char* filename)
  *\brief Convertit un fichier en une table en utilisant mmap
  *\param filename Le nom du fichier qu'on convertir
  *\return Retounre void
  */
void* convert_file_to_table(const char* filename)
{
  /* open the file with the mode read & write and the flag 0 that mean append
     the function open return a file descriptor that is an int used by the kernel of the operating system
     to acess to the file
  */
  int fd = open(filename, O_RDWR, 0);
  size_t size_file = getFilesize(filename);
  /*
    PROT_WRITE|PROT_WRITE means that we can both read and write in the memory
  */
  void* ptr =  mmap(ptr_begin_file, size_file, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  ptr_begin_file += size_file;
  return ptr;
}

/*
  brief:
*/

/**
  *\fn int get_nbr_lines(char* ptr_file)
  *\brief Calcule et donne le nombre de ligne dans un fichier
  *\param ptr_file Pointeur sur le fichier 
  *\return Retourne un int qui indique le nombre de lignes de ce fichier
  */
int get_nbr_lines(char* ptr_file)
{
  char* ptr_line = ptr_file;
  char* ptr_charc = ptr_line;
  while(*ptr_line != '\0')
  {
    ptr_charc = ptr_line;
    while(*ptr_charc != '\n')
    {
      ptr_charc += 1;
    }
    ptr_line = ptr_charc + 1;
  }
  return (int)(ptr_line - ptr_file);
}

/**
  *\fn fichier lines(char* ptr_file)
  *\brief Remplit les champs de la struture fichier qu'on a implémenté (voir outils.h)
  *\param ptr_file Pointeur sur le fichier
  *\return Strcuture Fichier avec les champs remplis (nombre de lignes, tableau de lignes, pointeur, tableau avec les tailles de lignes)
  */
fichier lines(char* ptr_file)
{
  int nbr_ligne = get_nbr_lines(ptr_file);
  int* tab = malloc(nbr_ligne*sizeof(int));
  char** tab_ligne = malloc(nbr_ligne*sizeof(char*));
  tab_ligne[0] = ptr_file;
  char* ptr_line = ptr_file;
  char* ptr_charc = ptr_line;
  int compteur = 0;
  while(*ptr_line != '\0')
  {
    compteur += 1;
    ptr_charc = ptr_line;
    while(*ptr_charc != '\n')
    {
      ptr_charc += 1;
    }
    *tab = (int)(ptr_charc - ptr_line + 1);
    *(tab_ligne+compteur) = *(tab_ligne + compteur - 1) + *tab;
    tab += 1;
    ptr_line = ptr_charc + 1;
  }
  fichier f;
  f.tab_ligne = tab_ligne;
  f.nbr_lines = compteur;
  f.tab_size_line = tab-compteur;
  f.ptr = ptr_file;
  return f;
}

/**
  *\fn int min_2(int a, int b)
  *\brief Calcule le min de deux nombres
  *\param a un premier nombre
  *\param b un second nombre
  *\return Un int qui est le minimum des deux
  */
int min_2(int a, int b)
{
  return (a < b)? a : b;
}

/**
  *\fn int min_3(int a, int b, int c)
  *\brief Calcule le min de trois nombres
  *\param a un premier nombre
  *\param b un second nombre
  *\param c un troisème nombre
  *\return Un int qui est le minimum des trois
  */
int min_3(int a, int b, int c)
{
  return min_2(a, min_2(b, c));
}
/*
  brief: it takes a table of int8_t and a size as argument
  and calculate de sum of the first 'size' element of the table
*/

int sum(int* T, int size)
{
  int somme = 0;
  for(int j = 0; j < size; j++)
  {
    somme += T[j];
  }
  return somme;
}

/**
  *\fn int C(int n, int m, fichier f1, fichier f2)
  *\brief Cette fonction calcule le coût pour transformer une lign A_i en la ligne B_j
  *\param n indice de la ligne du fichier source qu'on veut transformer
  *\param m indice de la ligne du fichier target 
  *\param f1 Fichier Source
  *\param f2 Fichier Target
  *\return Un int qui est le coût pour transformer une lign A_i en la ligne B_j
  */
int C(int n, int m, fichier f1, fichier f2)
{
  if(strncmp(f1.tab_ligne[n],
             f2.tab_ligne[m],
             min_2(f1.tab_size_line[n], f2.tab_size_line[m])))
  {
    return 10 + f1.tab_size_line[n];
  }
  else
  {
    return 0;
  }
}
