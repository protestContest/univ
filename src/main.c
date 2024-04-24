#include "observe.h"

typedef struct {
  i32 count;
} Thing;

void Update(void *obj, void *ref)
{
  Thing *thing = (Thing*)obj;
  printf("Count: %d\n", thing->count);
}

int main(void)
{
  Thing thing = {0};
  i32 i;

  Observe(&thing, Update, 0);
  for (i = 0; i < 10; i++) {
    thing.count++;
    Notify(&thing);
  }

  Unobserve(&thing, Update, 0);
  for (i = 0; i < 10; i++) {
    thing.count++;
    Notify(&thing);
  }
}
