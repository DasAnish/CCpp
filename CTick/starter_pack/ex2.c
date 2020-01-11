//
// Created by ad945 on 07/01/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFSIZE 1024

int main(int argc, char *argsv[]) {
  printf("\n+++++++++++++++++START+++++++++++++++++++\n");
  FILE *fp;
  unsigned char buffer[BUFSIZE] = {0};

  fp = fopen(argsv[1], "rb"); // read mode
  if (fp == NULL) {
    perror("Can't open file\n");
    return 1;
  }
  int ret = fread(&buffer, sizeof(char), BUFSIZE, fp);
  printf("%i\n", ret);

  unsigned char t[4];

  //Source
  printf("%d.%d.%d.%d ", buffer[12],buffer[13],buffer[14],buffer[15]);
  printf("%d.%d.%d.%d ", buffer[16], buffer[17], buffer[18], buffer[19]);


  t[0] = buffer[0];
  uint8_t IHL = (*(uint8_t *) t)&0xF;
  printf("%d ", IHL);

  t[0] = buffer[3];
  t[1] = buffer[2];
  uint16_t total_length = *(uint16_t *) t;
  printf("%d ", total_length);

  uint8_t data_offset = (uint8_t) buffer[IHL*4+12];
  data_offset = data_offset >> 4;
  printf("%d ", data_offset);

  int count = 0, offset = 0;
  for (int i = 0; i < BUFSIZE; i+= offset) {

    t[0] = buffer[i+3];
    t[1] = buffer[i+2];
    t[2] = 0;
    t[3] = 0;

    offset = *(int *) t;
    if (offset==0) break;

    count++;

  }

  printf("%d ", count);

  printf("\n\n");





  return 0;
}