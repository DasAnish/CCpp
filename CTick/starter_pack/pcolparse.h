//
// Created by ad945 on 07/01/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifndef BUFSIZE
#define BUFSIZE 1024
#endif

#ifndef STARTER_PACK_PCOLPARSE_H
#define STARTER_PACK_PCOLPARSE_H
#endif //STARTER_PACK_PCOLPARSE_H

//Supply a buffer of bytes for these functions to run

#ifdef __cplusplus
  extern "C" {
#endif

uint8_t getIHL(unsigned char *buffer, int i);

uint16_t getTotalLength(unsigned char *buffer, int i);

uint8_t getDataOffset(unsigned char *buffer, int i);

unsigned int getIPCount(unsigned char *buffer, int len);

unsigned int getSourceIP(unsigned char *buffer, int i);

unsigned int getDestinationIP(unsigned char *buffer, int i);

void getAllData(unsigned char *buffer, FILE *fw, int len_file);

uint16_t getData(unsigned char *buffer, int i, FILE *fw);

unsigned int getFileLength(FILE *fp);

#ifdef __cplusplus
}
#endif
