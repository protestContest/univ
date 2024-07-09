#pragma once

void DestroySymbols(void);
u32 Symbol(char *name);
u32 SymbolFrom(char *name, u32 len);
char *SymbolName(u32 sym);
void SetSymbolSize(i32 size);
void ImportSymbols(char *names, i32 len);
