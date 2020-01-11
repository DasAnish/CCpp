#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 1024
/* The machine this is supposed to run on is in little endian, whilst network
   byte order is in big endian.
*/

int main(int argc, char *argsv[]){
  FILE *fp;
  int retval;
  unsigned char buf[BUF_SIZE] = {0};

  fp = fopen(argsv[1] , "rb"); // read mode
  if(fp == NULL){
    perror("Error while opening the file.\n");
    exit(EXIT_FAILURE);
  }
  retval = fread(&buf,sizeof(char),BUF_SIZE,fp);
  printf("%i\n",retval);
  unsigned char a[4]={0};
  unsigned int ihl, total_length, data_offset;

  a[0] = buf[0];
  ihl = *(int *)a;
  ihl = ihl & 0xf;
  printf("ihl:%i\n",ihl); // IHL

  a[0] = buf[3];
  a[1] = buf[2];
  total_length = *(int *)a;
  printf("total_length:%i\n",total_length); // total_length

  printf("src:%i.%i.%i.%i\n",buf[12],buf[13],buf[14],buf[15]); // src

  printf("dst:%i.%i.%i.%i\n",buf[16],buf[17],buf[18],buf[19]); // dest

  a[0] = buf[ihl*4+12];
  a[1] = 0;
  a[2] = 0;
  a[3] = 0;
  data_offset = *(int *)a;
  data_offset = data_offset >> 4;
  printf("data_offset:%i\n",data_offset); // data_offset

  int count = 0, offset;
  for(int i = 0;i<BUF_SIZE;i+=offset){
    a[0] = buf[i+3];
    a[1] = buf[i+2];
    a[2] = 0;
    a[3] = 0;
    offset = *(int *)a;
    printf("offset:%i\n",offset);
    if(offset == 0){
      break;
    }
    count++;
   }
  printf("count:%i\n",count);

  printf("data_len: %i", total_length - ihl*4 - data_offset*4);
  /* Prints out the whole file in hex. Makes it easier to debug.
  for(int i = 0;i<1024;i++){
    printf("%x ",buf[i]);
  }
/* Checks if it's big endian or little endian on this machine.
    unsigned int num = 2130706432;
    unsigned int x;
    unsigned char a[4];
    a[3] = (num>>24) & 0xFF;
    a[2] = (num>>16) & 0xFF;
    a[1] = (num>>8) & 0xFF;
    a[0] = num & 0xFF;
    x = *(int *)a;
    printf("%d\n",x);
*/
  fclose(fp);
  return 0;
}

