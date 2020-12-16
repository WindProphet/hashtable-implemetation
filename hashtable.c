#include<stdlib.h>
#include<string.h>
#include"hashtable.h"

#ifndef __HASHTABLE_STRUCTS__
struct entry_t {
  char *key;
  unsigned long hash_val;
  void *value;
  struct entry_t *next;
};

struct hashtable_t {
  struct entry_t **table;
  int capacity;
  int entries_num;
  float load_factor;
};
#endif

unsigned long hash(const char *sstr) {
  unsigned char *str = (unsigned char*)sstr;
  unsigned long val = 5381;
  for (; *str; str++)
    val = ((val << 5) + val) + (*str);
  return val;
}

struct hashtable_t *hashtable_init(float factor) {
  struct hashtable_t *ht = malloc(sizeof(struct hashtable_t));
  ht->load_factor = factor == 0 ? 0.75f : factor;
  ht->capacity = 16;
  ht->entries_num = 0;
  ht->table = malloc(ht->capacity*sizeof(void *));
  memset(ht->table, 0, ht->capacity*sizeof(void *));
  return ht;
}

void hashtable_free(struct hashtable_t *ht) {
  for (int i = 0; i < ht->capacity; i++) {
    struct entry_t *p = ht->table[i];
    while (p) {
      void *f = p;
      p = p->next;
      free(f);
    }
  }
  free(ht->table);
  free(ht);
}

void hashtable_rehash(struct hashtable_t *ht) {
  if ((float)ht->entries_num/(float)ht->capacity < ht->load_factor)
    return;
  int cap = ht->capacity;
  ht->capacity <<= 1;
  struct entry_t **newtable = malloc(cap*2*sizeof(void *));
  for (int i = 0; i < cap; i++) {
    struct entry_t *p = ht->table[i],
      **a = newtable + i, **b = newtable + cap + i;
    *a = NULL; *b = NULL;
    while (p) {
      if (p->hash_val & cap) {
        *b = p;
        b = &(*b)->next;
        p = *b;
        *b = NULL;
      } else {
        *a = p;
        a = &(*a)->next;
        p = *a;
        *a = NULL;
      }
    }
  }
  free(ht->table);
  ht->table = newtable;
}

void *hashtable_get(struct hashtable_t *ht, char *key) {
  unsigned long h = hash(key);
  int index = h & (ht->capacity-1);
  struct entry_t *p = ht->table[index];
  while (p) {
    if (strcmp(p->key, key) == 0)
      return p->value;
    p = p->next;
  }
  // miss
  return NULL;
}

void hashtable_set(struct hashtable_t *ht, char *key, void *value) {
  unsigned long h = hash(key);
  int index = h & (ht->capacity-1);
  struct entry_t **p = ht->table + index;
  while (*p) {
    if (strcmp((*p)->key, key) == 0) {
      (*p)->value = value;
      return;
    }
    p = &((*p)->next);
  }
  // new
  ht->entries_num++;
  struct entry_t *node = malloc(sizeof(struct entry_t));
  *p = node;
  node->next = NULL;
  node->key = key;
  node->value = value;
  node->hash_val = h;
  hashtable_rehash(ht);
}


