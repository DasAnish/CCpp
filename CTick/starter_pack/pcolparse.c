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

uint8_t getIHL(char *buffer, int i){
  return ((uint8_t) buffer[i]) & 0xF;
}

uint16_t getTotalLength(char *buffer, int i){
  uint16_t left = (uint16_t) buffer[i+2];
  uint16_t right = (uint16_t) buffer[i+3];

  left = left << 8;
//  printf("DEBUG: %d | %d = %d\n", left, right, left | right);
  return left | right;
}

uint8_t getDataOffset(char *buffer, int i){
  return ((uint8_t) buffer[i+getIHL(buffer, i)*4+12])>>4;
}

uint32_t getIPCount(char *buffer, int len){
  uint32_t count = 0;
  uint16_t offset = 0;
  for (int i = 0; i < len; i += offset) {
    offset = getTotalLength(buffer, i);
    if (offset == 0) {
      break;
    }
    count++;
  }
  return count;
}

uint32_t getSourceIP(char *buffer, int i){
  uint32_t p1, p2, p3, p4;
  p1 = (uint32_t ) buffer[i+12];
  p2 = (uint32_t ) buffer[i+13];
  p3 = (uint32_t ) buffer[i+14];
  p4 = (uint32_t ) buffer[i+15];
  return (p1 << 24) | (p2 << 16) | (p3 << 8) | p4;
}

uint32_t getDestinationIP(char buffer[], int i){
  uint32_t p1, p2, p3, p4;
  p1 = (uint32_t ) buffer[i+16];
  p2 = (uint32_t ) buffer[i+17];
  p3 = (uint32_t ) buffer[i+18];
  p4 = (uint32_t ) buffer[i+19];
  return (p1 << 24) | (p2 << 16) | (p3 << 8) | p4;
}

uint16_t getData(char buffer[], int i, FILE *fw) {
  uint32_t ihl = (uint32_t ) getIHL(buffer, i);
  uint32_t total_length = (uint32_t ) getTotalLength(buffer, i);
  uint32_t data_offset = (uint32_t ) getDataOffset(buffer, i);

  uint32_t data_len = total_length - (ihl + data_offset)*4;

  char *temp = (char *) malloc(sizeof(char)*(data_len+1));
  for (int k = 0; k<data_len; k++) {
    temp[k] = buffer[i+ihl*4+data_offset*4+k];
//    printf("%c", temp[k]);
  }
  temp[data_len] = '\0';

  fwrite(temp, sizeof(char), data_len, fw);
  free((void *)temp);

  return (uint16_t) total_length;
}

void getAllData(char buffer[], FILE *fw, int len_file) {
  uint32_t offset = 0;
  for (int i = 0; i < len_file; i += offset) {
    offset = getData(buffer, i, fw);
    if (offset == 0) break;
  }
}

uint32_t getFileLength(FILE *fp) {
  int file_len;
  fseek(fp, 0, SEEK_END);
  file_len = ftell(fp);
  rewind(fp);

  return file_len;
}