#include "debug.h"
#include "math.h"
#include "str.h"

void HexDump(void *data, u32 size)
{
  u8 *bytes = data;
  u32 colwidth = 4;
  u32 cols = 8;
  u32 rowwidth = colwidth*cols;
  u32 nrows = size / (rowwidth);
  u32 extra = size % (rowwidth);
  u32 sizewidth = NumDigits(size, 10);
  u32 i, j;

  for (i = 0; i < nrows; i++) {
    char *line = (char*)bytes;
    printf("%*ld│ ", sizewidth, bytes - (u8*)data);
    for (j = 0; j < rowwidth; j++) {
      printf("%02X", bytes[j]);
      if (j % colwidth == colwidth-1) printf(" ");
    }
    bytes += rowwidth;
    printf("│");
    for (j = 0; j < rowwidth; j++) {
      if (IsPrintable(line[j])) printf("%c", line[j]);
      else printf(" ");
    }
    printf("│\n");
  }

  printf("%*ld│ ", sizewidth, bytes - (u8*)data);
  for (i = 0; i < rowwidth; i++) {
    if (i < extra) printf("%02X", bytes[i]);
    else printf("  ");
    if (i % colwidth == colwidth-1) printf(" ");
  }

  printf("│");
  for (j = 0; j < rowwidth; j++) {
    if (j < extra && IsPrintable(bytes[j])) printf("%c", bytes[j]);
    else printf(" ");
  }
  printf("│\n");
}
