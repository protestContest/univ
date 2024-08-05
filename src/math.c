#include "math.h"

u32 NumDigits(i32 num, u32 base)
{
  u32 n = 0;
  if (num == 0) return 1;
  if (num < 0) {
    n = 1;
    num = -num;
  }
  while (num > 0) {
    num /= base;
    n++;
  }
  return n;
}

u32 PopCount(u32 n)
{
  n = n - ((n >> 1) & 0x55555555);
  n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
  n = (n + (n >> 4)) & 0x0F0F0F0F;
  n = n + (n >> 8);
  n = n + (n >> 16);
  return n & 0x0000003F;
}

static u32 rand_state = 1;

void SeedRandom(u32 seed)
{
  rand_state = seed;
}

u32 Random(void) {
  rand_state ^= rand_state << 13;
  rand_state ^= rand_state << 17;
  rand_state ^= rand_state << 5;
  return rand_state;
}

u32 RandomBetween(u32 min, u32 max)
{
  u32 r, range, buckets, limit;
  if (min == max) return min;
  if (min > max) {
    u32 tmp = min;
    min = max;
    max = tmp;
  }

  range = 1 + max - min;
  buckets = MaxUInt / range;
  limit = buckets * range;

  do {
    r = Random();
  } while (r >= limit);

  return min + (r / buckets);
}
