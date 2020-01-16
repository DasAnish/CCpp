//
// Created by ad945 on 12/01/2020.
//

#include "decode.h"
#include "pcolparse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argsv[]) {
  FILE *enc, *dec;

  printf("\n+++++++++++++++++++++DECODE+++++++++++++++++++++\n\n");
  enc = fopen(argsv[1], "rb");
  dec = fopen(argsv[2], "rb");

  if (enc== NULL || dec == NULL) return 1;

  int len_enc = getFileLength(enc);
  int len_dec = getFileLength(dec);

  printf("Lengths dec: %d | enc: %d\n", len_dec, len_enc);

  typedef unsigned char uchar;

  uchar *buffer_enc = (uchar *) malloc(sizeof(char) * len_enc);
  uchar *buffer_dec = (uchar *) malloc(sizeof(char) * len_dec);

  fread(buffer_dec, sizeof(char), len_dec, dec);
  fread(buffer_enc, sizeof(char), len_enc, enc);

  printf("%s\n", buffer_dec);
  printf("%s\n", buffer_enc);

  uchar *buffer = (uchar *) malloc(sizeof(char)* 23);

  for (int i = 0, c = 0; i < len_enc; i++){
    if (buffer_enc[i] >= 'A' && buffer_enc[i] <= 'Z') {
      buffer[c++] = buffer_enc[i];
      printf("%c", buffer_enc[i]);
    }
  }
  printf("\n");

  for (int i = 0, c = 0; i < len_dec; i++) {
    buffer_dec[i] += buffer[c];
    c = (c+1) % 23;
  }

  printf("%s\n", buffer_dec);



  free(buffer);
  free(buffer_dec);
  free(buffer_enc);
  fclose(enc);
  fclose(dec);

  return 0;
}
