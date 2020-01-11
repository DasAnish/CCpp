#include <ctype.h>
#include <string.h>
#include "revwords.h"

void reverse_substring(char str[], int start, int end) { 
  /* TODO */
  char temp;
  for (int i = start, j = end; i<j; i++, j--) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
}


int find_next_start(char str[], int len, int i) { 
  /* TODO */
  for (int j = i; j<len; j++) {
    if (str[j] == ' ') return j;
  }
  return len;
}

int find_next_end(char str[], int len, int i) {
  /* TODO */
  int found = 0;
  for (int j = i; j < len; j++) {
    if(j == i) continue;
    else if (str[j] == ' ') return j;
  }

  return len;
}

void reverse_words(char s[]) { 
  /* TODO */
  int len = strlen(s);
  int start = 0, end = 0;

  /* while(start<len && end<len) {
    end = find_next_end(s, len, start);
    printf("(%d, %d) ", start, end);
    reverse_substring(s, start, end-1);
    start = find_next_start(s, len, end);
   
    
    }*/

  for (int i = 0; i<len; i++) {
    if(s[i] == ' '){
      end = i-1;
      //printf("(%d, %d)", start, end);
      reverse_substring(s, start, end);
      start = end+2; 
      if (end>=len || start>=len) break;
    }
    //if (i == len-1) printf("Running this");
    if(i == len-1) reverse_substring(s, start, len-1);
  }
  
  //if(start == 0) reverse_substring(s, 0, len-1);
  
  return;
}
