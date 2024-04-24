#include "file.h"
#include <fcntl.h>
#include <unistd.h>

char *ReadFile(char *path)
{
  int file;
  u32 size;
  char *data;

  file = open(path, O_RDWR, 0);
  if (file < 0) return 0;
  size = lseek(file, 0, 2);
  lseek(file, 0, 0);
  data = malloc(size + 1);
  read(file, data, size);
  data[size] = 0;
  close(file);
  return data;
}
