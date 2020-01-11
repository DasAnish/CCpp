//
// Created by ad945 on 07/01/2020.
//

#include "pcolparse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#ifndef STARTER_PACK_PCOLPARSE_H
#define STARTER_PACK_PCOLPARSE_H
#endif

int main(int argc, char *argsv[]) {
  printf ("\n++++++++++++++++++++++EXTRACT+++++++++++++++++++++++++\n\n");
  FILE *fp, *fw;


  if (argc != 3) {
    perror("Usage: <log-file-name> <new-file-name>\n");
    return 1;
  }

  fp = fopen(argsv[1], "rb");
  fw = fopen(argsv[2], "wb+");

  if (fp == NULL) {
    perror("Can't open this file\n");
    fclose(fp);
    fclose(fw);
    return 2;
  }

  int len_file = getFileLength(fp);

  unsigned char *buffer = (unsigned char *) malloc(sizeof(char) * len_file);
  fread(buffer, sizeof(char), len_file, fp);

  getAllData(buffer, fw, len_file);

  printf("Done\n");
  fclose(fw);
  fclose(fp);
  free((void *) buffer);
  return 0;
}