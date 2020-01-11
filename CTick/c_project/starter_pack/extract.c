#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int getihl(char *p, int i){
  unsigned int ihl;
  unsigned char a[4] = {0};
  a[0] = p[i+0];
  ihl = *(int *)a;
  return ihl & 0xf;
}

unsigned int gettotallength(char *p, int i){
  unsigned int total_length;
  unsigned char a[4] = {0};
  a[0] = p[i+3];
  a[1] = p[i+2];
  total_length = *(int *)a;
  return total_length;
}

unsigned int getdataoffset(char *p, int i){
  unsigned int data_offset;
  unsigned char a[4] = {0};
  a[0] = p[i+getihl(p,i)*4+12];
  a[1] = 0;
  a[2] = 0;
  a[3] = 0;
  data_offset = *(int *)a;
  data_offset = data_offset >> 4;
  return data_offset;
}

char * readdata(char *p, int i, unsigned int ihl, unsigned int total_length, unsigned int data_offset){
  int len_actual_data = total_length - (ihl + data_offset)*4;
  if(len_actual_data == 0){
    return NULL;
  }
  char *q = (char *) malloc( (len_actual_data+1) * sizeof(char) ); // remember terminating character
  for(int j = 0;j<len_actual_data;j++){
    q[j] = p[i+ihl*4+data_offset*4+j];
  }
  q[len_actual_data] = '\0';
  return q;
}

int main(int argc, char *argsv[]){
  FILE *fp;
  FILE *fw;
  unsigned long filelen;

  fp = fopen(argsv[1] , "rb"); // read mode
  fw = fopen(argsv[2] , "wb+"); // write to new file
  if(fp == NULL){
    perror("Error while opening the file.\n");
    fclose(fp);
    fclose(fw);
    exit(EXIT_FAILURE);
  }
  fseek(fp,0,SEEK_END); // jump to end of file
  filelen = ftell(fp);
  rewind(fp); // jump back to start of file
  char *buf = (char *) malloc(sizeof(char) * filelen);
  fread(buf, sizeof(char), filelen, fp);

  int offset = 0;
  for(int i = 0;i<filelen;i+=offset){
    unsigned int ihl, total_length, data_offset;
    ihl = getihl(buf,i);
    total_length = gettotallength(buf,i);
    data_offset = getdataoffset(buf,i);
    char *p = readdata(buf,i, ihl, total_length, data_offset);
    for(int j = 0;j<total_length - (ihl + data_offset)*4;j++){
      printf("%c",p[j]);
    }
    fwrite(p,sizeof(char),total_length-(ihl+data_offset)*4,fw);
    offset = total_length;
  }
  fclose(fp);
  fclose(fw); // trick
  return 0;
}


