#include "debug.h"
#include "file.h"
#include "str.h"

int main(int argc, char *argv[])
{
  char *data;

  if (argc < 2) {
    fprintf(stderr, "Usage: hexdump <file>\n");
    return 1;
  }

  data = ReadFile(argv[1]);
  if (!data) {
    fprintf(stderr, "Could not read \"%s\"\n", argv[1]);
    return 1;
  }

  HexDump(data, FileSize(argv[1]), basename(argv[1]));
  return 0;
}
