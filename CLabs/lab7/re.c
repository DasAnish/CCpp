#include <stdlib.h>
#include <stdio.h>
#include "re.h"

arena_t create_arena(int size) { 
  arena_t area = malloc(sizeof(struct arena));
  area->size = size;
  area->current = 0;
  area->exps = malloc(sizeof(struct re)*size);

  return area;
}


void arena_free(arena_t a) { 
  free(a->exps);
  free(a);
}

Regexp *re_alloc(arena_t a) { 
  if (a->current == a->size) return NULL;

  Regexp *exp = a->exps + a->current;
  a->current += 1;

  return exp;
}

Regexp *re_chr(arena_t a, char c) { 
  Regexp *exp = re_alloc(a);

  if (exp == NULL) return NULL;

  exp->data.chr = c;
  exp->type = CHR;

  return exp;
}

Regexp *re_alt(arena_t a, Regexp *r1, Regexp *r2) { 
  Regexp *exp = re_alloc(a);

  if (exp == NULL) return NULL;

  exp->type = ALT;
  exp->data.pair.fst = r1;
  exp->data.pair.snd = r2;

  return exp;
}

Regexp *re_seq(arena_t a, Regexp *r1, Regexp *r2) { 
  Regexp *exp = re_alloc(a);

  if (exp == NULL) return NULL;

  exp->type = SEQ;
  exp->data.pair.fst = r1;
  exp->data.pair.snd = r2;

  return exp;
}

int re_match(Regexp *r, char *s, int i) { 
  if (r == NULL) return -1;

  int a1, a2;

  switch (r->type) {
  case CHR:
    if (r->data.chr == s[i]) {
      return i+1;
    } else return -1;
    break;

  case ALT:
    a1 = re_match(r->data.pair.fst, s, i);
    a2 = re_match(r->data.pair.snd, s, i);

    if (a1 == -1 && a2 == -1) return -1;
    else if (a1 == -1) return a2;
    else return a1;
    break;

  case SEQ:
    a1 = re_match(r->data.pair.fst, s, i);
    if (a1 == -1) return -1;

    a2 = re_match(r->data.pair.snd, s, a1);
    if (a2 == -1) return -1;

    return a2;
    break;
  }
}



void re_print(Regexp *r) { 
  if (r != NULL) { 
    switch (r->type) {
    case CHR: 
      printf("%c", r->data.chr);
      break;
    case SEQ:
      if (r->data.pair.fst->type == ALT) { 
	printf("(");
	re_print(r->data.pair.fst);
	printf(")");
      } else {
	re_print(r->data.pair.fst);
      }
      if (r->data.pair.snd->type == ALT) { 
	printf("(");
	re_print(r->data.pair.snd);
	printf(")");
      } else {
	re_print(r->data.pair.snd);
      }
      break;
    case ALT:
      re_print(r->data.pair.fst);
      printf("+");
      re_print(r->data.pair.snd);
      break;
    }
  } else { 
    printf("NULL");
  }
}    


      
  
