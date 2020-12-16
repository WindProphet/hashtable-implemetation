#ifndef __HASHTABLE_H__

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

#define __HASHTABLE_STRUCTS__

struct hashtable_t *hashtable_init(float factor);
void hashtable_free(struct hashtable_t *ht);
void hashtable_rehash(struct hashtable_t *ht);
void *hashtable_get(struct hashtable_t *ht, char *key);
void hashtable_set(struct hashtable_t *ht, char *key, void *value);

#define __HASHTABLE_H__
#endif
