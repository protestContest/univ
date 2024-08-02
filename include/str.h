#pragma once

#define ANSINormal          "\033[0m"
#define ANSIBold            "\033[1m"
#define ANSIDim             "\033[2m"
#define ANSIItalic          "\033[3m"
#define ANSIUnderline       "\033[4m"
#define ANSIBlink           "\033[5m"
#define ANSIBlinkFast       "\033[6m"
#define ANSIInvert          "\033[7m"
#define ANSIHidden          "\033[8m"
#define ANSIStrikeThru      "\033[9m"
#define ANSINormalFont      "\033[10m"
#define ANSIFont(n)         "\033[1" ## (n) ## "m"
#define ANSIDblUnderline    "\033[21m"
#define ANSINormalWeight    "\033[22m"
#define ANSINotItalic       "\033[23m"
#define ANSINoUnderline     "\033[24m"
#define ANSINoBlink         "\033[25m"
#define ANSIProportional    "\033[26m"
#define ANSINotReversed     "\033[27m"
#define ANSIShown           "\033[28m"
#define ANSINoStrikeThru    "\033[29m"
#define ANSIBlack           "\033[30m"
#define ANSIRed             "\033[31m"
#define ANSIGreen           "\033[32m"
#define ANSIYellow          "\033[33m"
#define ANSIBlue            "\033[34m"
#define ANSIMagenta         "\033[35m"
#define ANSICyan            "\033[36m"
#define ANSIWhite           "\033[37m"
#define ANSIColor(n)        "\033[38:5:" ## (n) ## "m"
#define ANSIRGB(r,g,b)      "\033[38:2:" ## (r) ## ":" ## (g) ## ":" ## (b) ## "m"
#define ANSINormalColor     "\033[39m"
#define ANSIBGBlack         "\033[40m"
#define ANSIBGRed           "\033[41m"
#define ANSIBGGreen         "\033[42m"
#define ANSIBGYellow        "\033[43m"
#define ANSIBGBlue          "\033[44m"
#define ANSIBGMagenta       "\033[45m"
#define ANSIBGCyan          "\033[46m"
#define ANSIBGWhite         "\033[47m"
#define ANSIBGColor(n)      "\033[48:5:" ## (n) ## "m"
#define ANSIBGRGB(r,g,b)    "\033[48:2:" ## (r) ## ":" ## (g) ## ":" ## (b) ## "m"
#define ANSIBGNormalColor   "\033[49m"
#define ANSINotProportional "\033[50m"
#define ANSIFrame           "\033[51m"
#define ANSIEncircle        "\033[52m"
#define ANSIOverline        "\033[53m"
#define ANSINoFrame         "\033[54m"
#define ANSINoOverline      "\033[55m"

#define IsSpace(c)        ((c) == ' ' || (c) == '\t')
#define IsNewline(c)      ((c) == '\n' || (c) == '\r')
#define IsDigit(c)        ((c) >= '0' && (c) <= '9')
#define IsUppercase(c)    ((c) >= 'A' && (c) <= 'Z')
#define IsLowercase(c)    ((c) >= 'a' && (c) <= 'z')
#define IsAlpha(c)        (IsUppercase(c) || IsLowercase(c))
#define IsHexDigit(c)     (IsDigit(c) || ((c) >= 'A' && (c) <= 'F'))
#define HexDigit(n)       ((n) < 10 ? (n) + '0' : (n) - 10 + 'A')
#define IsPrintable(c)    ((c) >= 0x20 && (c) < 0x7F)
#define StrEq(s1, s2)     ((s1) && (s2) && strcmp(s1, s2) == 0)
#define MemEq(s1, s2, n)  (memcmp(s1, s2, n) == 0)
#define CopyStr(s, n)     strndup(s, n)
#define StrLen(s)         strlen(s)

char *NewStr(char *str);
char *SkipSpaces(char *str);
char *LineStart(u32 index, char *str);
char *LineEnd(u32 index, char *str);
u32 LineNum(char *str, u32 index);
u32 ColNum(char *str, u32 index);
char *JoinStr(char *str1, char *str2, char joiner);
char *StrCat(char *str1, char *str2);
u32 ParseInt(char *str);
void Copy(void *src, void *dst, u32 size);
u32 WriteStr(char *str, u32 len, char *buf);
u32 WriteNum(i32 num, char *buf);
char *BufWrite(char *str, char *buf);
char *BufWriteNum(i32 num, char *buf);
