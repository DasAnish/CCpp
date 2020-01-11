#include <stdlib.h>
#include "tree.h"

Tree *empty = NULL;

/* BASE EXERCISE */

int tree_member(int x, Tree *tree) { 
  //Implementing breadth first search

  if (tree == empty) {

    return 0;

  } else {

    if (x < tree->value) return tree_member(x, tree->left);
    else if (x > tree->value) return tree_member(x, tree->right);
    else return 1;

  }
  
}

Tree *node(Tree *left, int value, Tree *right) {

  Tree *t = malloc(sizeof(node));
  t->left = left;
  t->value = value;
  t->right = right;
  return t;
  
}

Tree *tree_insert(int x, Tree *tree) { 

  if (tree == empty) return node(empty, x, empty);
  else {

    if (x<tree->value) {
      tree->left = tree_insert(x, tree->left);
      return tree;
    } else if (x>tree->value) {
      tree->right = tree_insert(x, tree->right);
      return tree;
    } else {
      return tree;
    }
  }
  
}

void tree_free(Tree *tree) { 
  if (tree != empty) {

    tree_free(tree->left);
    tree_free(tree->right);
    free(tree);
    
  }
}

/* CHALLENGE EXERCISE */ 

void pop_minimum(Tree *tree, int *min, Tree **new_tree) { 
  if(tree->left == empty) {
    *min = tree->value;
    *new_tree = tree->right;
    free(tree);
  } else {
    pop_minimum(tree->left, min, &(tree->left));
    *new_tree = tree;
  }
}

Tree *tree_remove(int x, Tree *tree) { 
  if (tree==empty) {
    return empty;
  } else {
    if (x < tree->value) {
      tree->left = tree_remove(x, tree->left);
      return tree;
    } else if (x > tree->value) {
      tree->right = tree_remove(x, tree->right);
      return tree;
    } else {

      if (tree->right == empty) {
	Tree *result = tree->left;
	free(tree);
	return result;
      } else {
	pop_minimum(tree->right, &(tree->value), &(tree->right));
	return tree;
      }
      
    }
    
  }
}
