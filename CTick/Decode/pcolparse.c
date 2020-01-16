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

uint8_t getIHL(unsigned char *buffer, int i){
  return ((uint8_t) buffer[i]) & 0xF;
}

uint16_t getTotalLength(unsigned char *buffer, int i){
  uint16_t left = (uint16_t) buffer[i+2];
  uint16_t right = (uint16_t) buffer[i+3];

  left = left << 8;
//  printf("DEBUG: %d | %d = %d\n", left, right, left | right);
  return left | right;
}

uint8_t getDataOffset(unsigned char *buffer, int i){
  return ((uint8_t) buffer[i+getIHL(buffer, i)*4+12])>>4;
}

unsigned int getIPCount(unsigned char *buffer, int len){
  unsigned int count = 0;
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

unsigned int getSourceIP(unsigned char *buffer, int i){
  unsigned int p1, p2, p3, p4;
  p1 = (unsigned int) buffer[i+12];
  p2 = (unsigned int) buffer[i+13];
  p3 = (unsigned int) buffer[i+14];
  p4 = (unsigned int) buffer[i+15];
  return (p1 << 24) | (p2 << 16) | (p3 << 8) | p4;
}

unsigned int getDestinationIP(unsigned char buffer[], int i){
  unsigned int p1, p2, p3, p4;
  p1 = (unsigned int) buffer[i+16];
  p2 = (unsigned int) buffer[i+17];
  p3 = (unsigned int) buffer[i+18];
  p4 = (unsigned int) buffer[i+19];
  return (p1 << 24) | (p2 << 16) | (p3 << 8) | p4;
}

uint16_t getData(unsigned char buffer[], int i, FILE *fw) {
  unsigned int ihl = (unsigned int) getIHL(buffer, i);
  unsigned int total_length = (unsigned int) getTotalLength(buffer, i);
  unsigned int data_offset = (unsigned int) getDataOffset(buffer, i);

  unsigned int data_len = total_length - (ihl + data_offset)*4;

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

void getAllData(unsigned char buffer[], FILE *fw, int len_file) {
  unsigned int offset = 0;
  for (int i = 0; i < len_file; i += offset) {
    offset = getData(buffer, i, fw);
    if (offset == 0) break;
  }
}

unsigned int getFileLength(FILE *fp) {
  int file_len;
  fseek(fp, 0, SEEK_END);
  file_len = ftell(fp);
  rewind(fp);

  return file_len;
}