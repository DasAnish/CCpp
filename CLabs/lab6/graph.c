#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "graph.h"

Node *empty = NULL;

Node *node(int value, Node *left, Node *right) { 
  Node *r = malloc(sizeof(Node));
  r->marked = false;
  r->value = value;
  r->left = left;
  r->right = right;
  return r;
}


/* Basic Problems */

int size(Node *node) {

  if (node == NULL || node->marked) return 0;
  node->marked = true;

  return 1 + size(node->left) + size(node->right);
  
}


void unmark(Node *node) { 

  if (node != NULL) {
    if (node->marked) {
      node->marked = false;
      unmark(node->left);
      unmark(node->right);
    }
    
  }
  
}

bool path_from(Node *node1, Node *node2) {

  if (node1 == NULL || node2 == NULL) return false;

  return (node1 == node2) || path_from(node1->left, node2) || path_from(node1->right, node2);
  
}

bool cyclic(Node *node) { 
  if (node == NULL) return false;

  Node *left = node->left;
  Node *right = node->right;

  return path_from(left, node) || path_from(right, node) || cyclic(left) || cyclic(right);
} 


/* Challenge problems */

void get_nodes(Node *node, Node **dest) { 
  if (node != NULL) {
    /* if (dest == NULL){ */
    /*   **dest = &node; */
    /* } */
    *dest = &node;
    dest = dest + 1;
    get_nodes(node->left, dest);
    get_nodes(node->right, dest);
  }
}

void graph_free(Node *node) { 
  Node **dest = NULL;

  get_nodes(node, dest);

  unmark(node);
  free(*dest);
  /* for (int i = 0; i<size(node); i++) { */
  /*   free(*(desti)); */
  /* } */
}


