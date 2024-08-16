#include "str.h"
#include "hash.h"
#include "math.h"
#include "vec.h"

char *NewString(char *str)
{
  if (!str) return 0;
  return StringFrom(str, StrLen(str));
}

char *StringFrom(char *str, u32 len)
{
  char *newstr;
  if (!str) return 0;
  newstr = malloc(len+1);
  Copy(str, newstr, len);
  newstr[len] = 0;
  return newstr;
}

char *SkipSpaces(char *str)
{
  while (*str == ' ' || *str == '\t') str++;
  return str;
}

char *LineStart(u32 index, char *str)
{
  while (index > 0 && !IsNewline(str[index-1])) index--;
  return str + index;
}

char *LineEnd(u32 index, char *str)
{
  while (str[index] != 0 && !IsNewline(str[index])) index++;
  return str + index + IsNewline(str[index]);
}

u32 LineNum(char *source, u32 pos)
{
  char *cur = source;
  u32 line = 0;

  while (cur < source + pos) {
    if (*cur == '\n') line++;
    cur++;
  }

  return line;
}

u32 ColNum(char *source, u32 pos)
{
  char *cur = source + pos;

  while (cur > source && *(cur-1) != '\n') cur--;

  return source + pos - cur;
}

char *JoinStr(char *str1, char *str2, char joiner)
{
  u32 len1 = strlen(str1), len2 = strlen(str2);
  u32 joinlen = joiner != 0;
  char *str = malloc(len1 + joinlen + len2 + 1);
  Copy(str1, str, len1);
  if (joiner) str[len1] = joiner;
  Copy(str2, str+len1+1, len2);
  str[len1+1+len2] = 0;
  return str;
}

char *StrCat(char *str1, char *str2)
{
  u32 len1 = str1 ? strlen(str1) : 0;
  u32 len2 = str2 ? strlen(str2) : 0;
  str1 = realloc(str1, len1+len2+1);
  Copy(str2, str1+len1, len2);
  str1[len1+len2] = 0;
  return str1;
}

u32 ParseInt(char *str)
{
  u32 num = 0;
  while (IsDigit(*str)) {
    u32 d = *str - '0';
    num = num * 10 + d;
    str++;
  }
  return num;
}

void Copy(void *src, void *dst, u32 size)
{
  u8 *src_bytes = src;
  u8 *dst_bytes = dst;
  u32 i;

  if (src == dst) return;

  if (src_bytes + size < dst_bytes || dst_bytes + size < src_bytes) {
    memcpy(dst, src, size);
    return;
  }

  if (src_bytes > dst_bytes) {
    Copy(dst, src, size);
    return;
  }

  for (i = 0; i < size; i++) dst_bytes[size-1-i] = src_bytes[size-1-i];
}

u32 WriteStr(char *str, u32 len, char *buf)
{
  u32 buflen = buf ? len+1 : 0;
  return snprintf(buf, buflen, "%*.*s", len, len, str);
}

u32 WriteNum(i32 num, char *buf)
{
  u32 len = buf ? NumDigits(num, 10) + 1 : 0;
  return snprintf(buf, len, "%d", num);
}

char *BufWrite(char *str, char *buf)
{
  i32 len = strlen(str);
  if (VecCount(buf) > 0 && buf[VecCount(buf)-1] == 0) VecPop(buf);
  GrowVec(buf, len);
  Copy(str, buf + VecCount(buf) - len, len);
  return buf;
}

char *BufWriteNum(i32 num, char *buf)
{
  i32 len = NumDigits(num, 10);
  if (VecCount(buf) > 0 && buf[VecCount(buf)-1] == 0) VecPop(buf);
  GrowVec(buf, len+1);
  VecPop(buf);
  snprintf(buf + VecCount(buf) - len, VecCount(buf)+1, "%d", num);
  return buf;
}
