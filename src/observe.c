#include "observe.h"
#include "hashmap.h"
#include "hash.h"
#include "vec.h"

typedef struct {
  ObserveFn update;
  void *ref;
  i32 next;
} Observer;

static HashMap subjects = EmptyHashMap;
static Observer *observers = 0;

void Observe(void *subject, ObserveFn update, void *ref)
{
  u32 key = Hash(&subject, sizeof(subject));
  Observer ob;
  ob.update = update;
  ob.ref = ref;
  ob.next = HashMapGet(&subjects, key);
  HashMapSet(&subjects, key, VecCount(observers));
  VecPush(observers, ob);
}

void Unobserve(void *subject, ObserveFn update, void *ref)
{
  u32 key = Hash(&subject, sizeof(subject));
  i32 index = HashMapGet(&subjects, key);
  Observer *ob = &observers[index];

  if (index >= 0 && ob->update == update && ob->ref == ref) {
    while (index >= 0 && ob->update == update && ob->ref == ref) {
      index = ob->next;
      if (index >= 0) ob = &observers[index];
    }
    HashMapSet(&subjects, key, index);
  }
  if (index < 0) return;
  while (ob->next >= 0) {
    Observer *next = &observers[ob->next];
    if (next->update == update && next->ref == ref) {
      ob->next = next->next;
      next = &observers[ob->next];
    } else {
      ob = &observers[ob->next];
    }
  }
}

void Notify(void *subject)
{
  u32 key = Hash(&subject, sizeof(subject));
  i32 index = HashMapGet(&subjects, key);

  while (index >= 0) {
    Observer *ob = &observers[index];
    ob->update(subject, ob->ref);
    index = ob->next;
  }
}
