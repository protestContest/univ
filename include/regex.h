#pragma once

/*
a     literal
\a    escaped
[a-z] range
.     any
a?    optional
a*    zero or more
a+    one or more
ab    sequence
a|b   choice
*/

typedef struct RE RE;
RE *RECompile(char *pattern);
i32 RETest(char *pattern, char *str);

