/**
 * @file
 * \author Benjelloun hamza, Ait lahmouch Nadir
 */
#include "algo_1.h"
#include <time.h>
extern void* ptr_begin_file;

/**
  *\fn void write_patch_recur(int** mat, int i, int j, FILE* patch, fichier src, fichier dst)
  *\brief
  *\param mat La matrice qui mémorise les valeurs de tous les noeuds de notre graphe d'appel.
  *\param i indexe qui renvoie aux lignes du fichier source
  *\param j indexe qui renvoie aux lignes du fichier target
  *\param patch Notre fichier patch qu'on remplit
  *\param src Le fichier source
  *\param dst Le fichier Destination
  *\return Ne retourne rien, mais écrit dans le patch écrit en paramètre
  */
void write_patch_recur(int** mat, int i, int j, FILE* patch, fichier src, fichier dst)
{
  if(i == 0 && j == 0)
  {
    return;
  }
  else if(i == 0)
  {
    while (j!=0){
    char* ligne = malloc(src.tab_size_line[j-1] * sizeof(char*));
    strncpy(ligne, src.tab_ligne[j-1], src.tab_size_line[j-1]);
    *(ligne + src.tab_size_line[j-1]) = '\0';
    fprintf(patch,"- %i\n%s", j, ligne); // “- k\nL_new\n”
    j--;
  }
    return;
  }
  else if(j == 0)
  {
    while(i!=0){
    write_patch_recur(mat, i - 1, j, patch, src, dst);
    char* ligne = malloc(dst.tab_size_line[i-1] * sizeof(char*));
    strncpy(ligne, dst.tab_ligne[i-1], dst.tab_size_line[i-1]);
    *(ligne + dst.tab_size_line[i-1]) = '\0';
    fprintf(patch,"+ %i\n%s", j, ligne); // “+ k\nL_new\n”
    i--;
  }
  return;
  }
  else
  {
  int a_11 = mat[i-1][j] + 10 + dst.tab_size_line[i - 1];
  int a_12 = mat[i-1][j - 1] + C(i - 1, j - 1, dst, src);
  int a_13 = mat[i][j-1] + 10;
  int a_ij = mat[i][j];
  if(a_ij == a_12)
    {
      char* ligne1 = malloc(src.tab_size_line[j-1] * sizeof(char*));
      char* ligne2 = malloc(dst.tab_size_line[i-1] * sizeof(char*));
      strncpy(ligne1, src.tab_ligne[j-1], src.tab_size_line[j-1]);
      strncpy(ligne2, dst.tab_ligne[i-1], dst.tab_size_line[i-1]);
      *(ligne1 +src.tab_size_line[j-1]) = '\0';
      *(ligne2 +dst.tab_size_line[i-1]) = '\0';
      if(!strcmp(ligne1, ligne2))
      {
        int i_cur = i;
        int j_cur = j;
        while(!strcmp(ligne1, ligne2) && i_cur > 0 && j_cur > 0)
        {
          i_cur -= 1;
          j_cur -= 1;
          ligne1 = malloc(src.tab_size_line[i_cur-1] * sizeof(char*));
          ligne2 = malloc(dst.tab_size_line[i_cur-1] * sizeof(char*));
          strncpy(ligne1, src.tab_ligne[j_cur - 1], src.tab_size_line[j_cur-1]);
          strncpy(ligne2, dst.tab_ligne[i_cur - 1], dst.tab_size_line[i_cur-1]);
          *(ligne1 +src.tab_size_line[j_cur-1]) = '\0';
          *(ligne2 +dst.tab_size_line[i_cur-1]) = '\0';
        }
        write_patch_recur(mat, i_cur, j_cur, patch, src, dst);
      }
      else
      {
        write_patch_recur(mat, i - 1, j - 1, patch, src, dst);
        fprintf(patch,"= %i\n%s%s", j, ligne1, ligne2); // “= k\nL_new\nL_old”
      }
    }
  else if(a_ij == a_11)
  {
    write_patch_recur(mat, i - 1, j, patch, src, dst);
    char* ligne1 = malloc(dst.tab_size_line[i-1] * sizeof(char*));
    strncpy(ligne1, dst.tab_ligne[i-1], dst.tab_size_line[i-1]);
    *(ligne1 +dst.tab_size_line[i-1]) = '\0';
    fprintf(patch,"+ %i\n%s", j, ligne1); // “+ k\nL_new\n”
  }
  else if(a_ij == a_13)
  {
    write_patch_recur(mat, i, j-1, patch, src, dst);
    char* ligne = malloc(src.tab_size_line[j-1] * sizeof(char*));
    strncpy(ligne, src.tab_ligne[j-1], src.tab_size_line[j-1]);
    *(ligne +src.tab_size_line[j-1]) = '\0';
    fprintf(patch,"- %i\n%s", j, ligne); // “- k\nL_new\n”
  }
  }
}


/**
  *\brief Cette fonction récupère les fichiers, les traite selon des fonctions dans outils.c et remplit le patch
  *\param F1 Notre fichier source qu'on va passer en paramètre
  *\param F2 Notre fichier Target qu'on va passer en paramètre
  *\param P Notre fichier Patch qu'on va passer en paramètre
  *\return Ne retourne rien, mais écrit dans le patch écrit en paramètre
  */
void algo_iter(const char* F1, const char* F2, const char* P)
{
  FILE* patch = fopen(P, "w");
  if(getFilesize(F1) && getFilesize(F2))
  {
  char* ptr_src = (char*) convert_file_to_table(F1);
  char* ptr_dst = (char*) convert_file_to_table(F2);
  fichier src = lines(ptr_src),
          dst = lines(ptr_dst);
  int m = src.nbr_lines,
      n = dst.nbr_lines;
  int** mat = malloc((n+1)*sizeof(int*));
  if(n != 0 && m != 0)
  {
    /*initialisation de la matrice*/
    mat[0] = malloc((m+1)*sizeof(int));
    mat[0][0] = 0;
    int sum = 0;
    for(int j = 1; j < n + 1; j++)
    {
      sum += dst.tab_size_line[j-1];
      mat[j] = malloc((m+1)*sizeof(int));
      mat[j][0] = 10 * j + sum;
    }
    for(int i = 1; i < m + 1; i++)
    {
      mat[0][i] = 10 * i;
    }

    /* fill in the matrix*/
    int a_11, a_12, a_13;
    for(int i = 1; i < n + 1; i++)
    {
      for(int j = 1; j < m + 1; j++)
      {
        a_11 = mat[i-1][j] + 10 + dst.tab_size_line[i - 1];
        a_12 = mat[i-1][j - 1] + C(i - 1, j - 1, dst, src);
        a_13 = mat[i][j-1] + 10;
        mat[i][j] = min_3(a_11, a_12, a_13);
      }
    }
    /* construction of the patch  */
    write_patch_recur(mat, n, m, patch, src, dst);

    for (int i = 0; i < n+1; i++){
      free(mat[i]);
    }
    free(mat);
  }
}
  else if(getFilesize(F2) == 0)
  {
    /* empty target */
    char* ptr_src = (char*) convert_file_to_table(F1);
    fichier src = lines(ptr_src);
    int m = src.nbr_lines;
    for(int j = 0; j < m; j++)
    {
      char* ligne = malloc(src.tab_size_line[j] * sizeof(char));
      strncpy(ligne, src.tab_ligne[j], src.tab_size_line[j]);
      *(ligne + src.tab_size_line[j]) = '\0';
      fprintf(patch,"- %i\n%s", j + 1, ligne); // “- k\nL_new\n”
    }
  }
  else
  {
    /* empty source */
    char* ptr_dst = (char*) convert_file_to_table(F2);
    fichier dst = lines(ptr_dst);
    int n = dst.nbr_lines;
    for(int i = 0; i < n; i++)
    {
      char* ligne1 = malloc(dst.tab_size_line[i] * sizeof(char));
      strncpy(ligne1, dst.tab_ligne[i], dst.tab_size_line[i]);
      *(ligne1 + dst.tab_size_line[i]) = '\0';
      fprintf(patch,"+ %i\n%s", 0, ligne1); // “+ k\nL_new\n”
    }
  }
  fclose(patch);
}
