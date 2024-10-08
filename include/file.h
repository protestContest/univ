#pragma once
#include <libgen.h>

#define DirName(path)   dirname(path)

typedef struct {
  u32 count;
  char **filenames;
} FileList;

FileList *NewFileList(u32 count);
void FreeFileList(FileList *list);

u32 FileSize(char *path);
char *ReadFile(char *path);
i32 WriteFile(u8 *data, u32 size, char *path);
FileList *ListFiles(char *path, char *ext, FileList *list);
char *FileExt(char *path);
