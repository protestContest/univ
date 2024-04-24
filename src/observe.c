#include "observe.h"
#include "hashmap.h"
#include "hash.h"
#include "vec.h"

typedef struct {
  ObserveFn update;
  void *ref;
} Observer;

static HashMap subjects = EmptyHashMap;
static Observer **subject_observers = 0;

void Observe(void *subject, ObserveFn update, void *ref)
{
  Observer ob;
  u32 key = Hash(&subject, sizeof(subject));
  u32 index;

  ob.update = update;
  ob.ref = ref;

  if (HashMapContains(&subjects, key)) {
    index = HashMapGet(&subjects, key);
  } else {
    index = VecCount(subject_observers);
    HashMapSet(&subjects, key, index);
    VecPush(subject_observers, 0);
  }

  VecPush(subject_observers[index], ob);
}

void Unobserve(void *subject, ObserveFn update, void *ref)
{
  Observer *observers;
  u32 key = Hash(&subject, sizeof(subject));
  u32 i;
  if (!HashMapContains(&subjects, key)) return;

  observers = subject_observers[HashMapGet(&subjects, key)];
  for (i = 0; i < VecCount(observers); i++) {
    if (observers[i].update == update && observers[i].ref == ref) {
      VecDel(observers, i);
      return;
    }
  }
}

void Notify(void *subject)
{
  u32 key = Hash(&subject, sizeof(subject));
  if (HashMapContains(&subjects, key)) {
    Observer *observers = subject_observers[HashMapGet(&subjects, key)];
    u32 i;
    for (i = 0; i < VecCount(observers); i++) {
      observers[i].update(subject, observers[i].ref);
    }
  }
}
