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

void doStuff(unsigned char *buffer, int len_file) {
  unsigned int count = getIPCount(buffer, len_file);
  unsigned int c = 0;
  int offset = 0;
  for (int i = 0; i < len_file; i += offset) {
    unsigned int ipSource = getSourceIP(buffer, i);

    unsigned int ipDest = getDestinationIP(buffer, i);

    uint8_t ihl = getIHL(buffer, i);

    uint8_t data_offset = getDataOffset(buffer, i);

    uint16_t total_length = getTotalLength(buffer, i);
    if (total_length==0) break;
    if (count == c) break;
    printf("%d ", ++c);

    printf("%d.%d.%d.%d ", ipSource>>24, (ipSource>>16)&0xFF,
           (ipSource>>8)&0xFF, ipSource&0xFF);
    printf("%d.%d.%d.%d ", ipDest>>24, (ipDest>>16)&0xFF,
           (ipDest>>8)&0xFF, ipDest&0xFF);

    printf("%d ", ihl);
    printf("%d ", total_length);
    printf("%d\n", data_offset);

    offset = total_length;
  }
  printf("%d\n", count);
}

int main(int argc, char *argsv[]) {
  printf ("\n++++++++++++++++++++++SUMMARY+++++++++++++++++++++++++\n\n");
  FILE *fp;
  int ret;

  if (argc != 2) {
    perror("Usage: <log-file-name>\n");
    return 1;
  }

  fp = fopen(argsv[1], "rb");

  if (fp == NULL) {
    perror("Can't open this file\n");
    return 2;
  }

  int len_file = getFileLength(fp);
  unsigned char *buffer = (unsigned char *) malloc(sizeof(char) * len_file);

  ret = fread(buffer, sizeof(char), len_file, fp);
  printf("ret: %d\n", ret);

  doStuff(buffer, len_file);
  free((void *) buffer);
  fclose(fp);
  return 0;
}