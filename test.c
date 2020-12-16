#include<stdio.h>
#include<stdlib.h>
#include"hashtable.h"

struct record_t {
  char key[256];
  int value;
};

int main() {
  char buf[256];
  struct hashtable_t *ht = hashtable_init(0.75);
  struct record_t *rec;
  while (1) {
    scanf("%s", buf);
    switch (buf[0]) {
    case 'S':
      rec = malloc(sizeof(struct record_t));
      scanf("%s%d", rec->key, &rec->value);
      hashtable_set(ht, rec->key, &rec->value);
      break;
    case 'G':
      scanf("%s", buf);
      int *val = hashtable_get(ht, buf);
      if (val) {
        printf("%s %d\n", buf, *val);
      } else {
        printf("%s NULL\n", buf);
      }
      break;
    case 'E':
      return 0;
    }
  }
}
