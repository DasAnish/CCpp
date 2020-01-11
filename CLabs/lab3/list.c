#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List *cons(int head, List *tail) { 
  /* malloc() will be explained in the next lecture! */
  List *cell = malloc(sizeof(List));
  cell->head = head;
  cell->tail = tail;
  return cell;
}

void free_list(List *list) {

  while(list){
    List *tail = list->tail;
    free(list);
    list = tail;
  }
  
}

/* Functions for you to implement */

int sum(List *list) {
  int s = 0;
  /* printf("%p",list); */
  List *current = list;
  while(current) {
    s += current->head;
    current = current->tail;
  }
  /* printf("%p",list); */
  return s;
}

void iterate(int (*f)(int), List *list) {
  List *current = list;
  while(current){
    current->head = (*f)(current->head);
    current = current->tail;
  }
}

void print_list(List *list) { 
  printf("[");
  List *current = list;
  while(current) {
    printf("%d", current->head);
    current = current->tail;
    if(current) printf(", ");
  }

  printf("]\n");
}

/**** CHALLENGE PROBLEMS ****/

List *merge(List *list1, List *list2) { 
  List *newList = NULL;

  while (list1 && list2) {
    if (list1->head <= list2->head){
      newList = cons(list1->head, newList);
      list1 = list1->tail;
    } else {
      newList = cons(list2->head, newList);
      list2 = list2->tail;
    }
  }

  while(list1) {
    newList = cons(list1->head, newList);
    list1 = list1->tail;
  }

  while(list2) {
    newList = cons(list2->head, newList);
    list2 = list2->tail;
  }

  return newList;
}



void split(List *list, List **list1, List **list2) {
  *list1 = NULL;
  *list2 = NULL;

  int i = 0;
  while (list) {

    i++;
    if (i%2 == 0) *list1 = cons(list->head, *list1);
    else *list2 = cons(list->head, *list2);

    list = list->tail;

  }
}

/* You get the mergesort implementation for free. But it won't
   work unless you implement merge() and split() first! */

List *mergesort(List *list) { 
  if (list == NULL || list->tail == NULL) { 
    return list;
  } else { 
    List *list1;
    List *list2;
    split(list, &list1, &list2);
    list1 = mergesort(list1);
    list2 = mergesort(list2);
    return merge(list1, list2);
  }
}
