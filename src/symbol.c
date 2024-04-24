#include "symbol.h"
#include "hash.h"
#include "hashmap.h"
#include "vec.h"
#include "str.h"

static char *names = 0;
static HashMap map = EmptyHashMap;

u32 AddSymbol(char *name)
{
  u32 len = strlen(name);
  return AddSymbolLen(name, len);
}

u32 AddSymbolLen(char *name, u32 len)
{
  u32 hash = Hash(name, len);

  if (!HashMapContains(&map, hash)) {
    u32 index = VecCount(names);
    HashMapSet(&map, hash, index);
    GrowVec(names, len);
    Copy(name, names + index, len);
    VecPush(names, 0);
  }

  return hash;
}

char *SymbolName(u32 sym)
{
  if (!HashMapContains(&map, sym)) return 0;
  return names + HashMapGet(&map, sym);
}
