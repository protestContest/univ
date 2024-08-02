#include "symbol.h"
#include "hash.h"
#include "hashmap.h"
#include "math.h"
#include "vec.h"
#include "str.h"

static i32 symSize = 32;
static char *names = 0;
static HashMap map = EmptyHashMap;

void DestroySymbols(void)
{
  DestroyHashMap(&map);
  FreeVec(names);
  names = 0;
}

u32 Symbol(char *name)
{
  u32 len = strlen(name);
  return SymbolFrom(name, len);
}

u32 SymbolFrom(char *name, u32 len)
{
  u32 sym = FoldHash(Hash(name, len), symSize);
  if (!HashMapContains(&map, sym)) {
    u32 index = VecCount(names);
    HashMapSet(&map, sym, index);
    GrowVec(names, len);
    Copy(name, names + index, len);
    VecPush(names, 0);
  }
  return sym;
}

char *SymbolName(u32 sym)
{
  if (!HashMapContains(&map, sym)) return 0;
  return names + HashMapGet(&map, sym);
}

void SetSymbolSize(i32 size)
{
  symSize = size;
}

void ImportSymbols(char *names, i32 len)
{
  char *end = names + len;
  while (names < end) {
    len = strlen(names);
    SymbolFrom(names, len);
    names += len + 1;
  }
}

u32 ExportSymbols(char **result)
{
  if (result) {
    *result = realloc(*result, VecCount(names));
    Copy(names, *result, VecCount(names));
  }
  return VecCount(names);
}
