#include "regex.h"
#include "vec.h"

typedef enum REType {reLit, reAny, reSeq, reChoice} REType;
typedef enum REQuant {reOne, reOptional, reZeroPlus} REQuant;

struct RE {
  REType type;
  REQuant quantity;
  union {
    struct RE *children[2];
    char range[2];
  } value;
};

RE *MakeState(REType type)
{
  RE *state = malloc(sizeof(RE));
  state->type = type;
  state->quantity = reOne;
  state->value.children[0] = 0;
  state->value.children[0] = 0;
  return state;
}

RE *RECompileChoice(char **re);

RE *RECompileLiteral(char **re)
{
  RE *state = MakeState(reLit);
  char ch;

  if (**re == '\\') {
    (*re)++;
    if (!**re) return 0;
    switch (**re) {
    case 'n':
      ch = '\n';
      break;
    case 't':
      ch = '\t';
      break;
    default:
      ch = **re;
    }
  } else {
    ch = **re;
  }

  state->value.range[0] = ch;
  state->value.range[1] = ch;
  (*re)++;
  return state;
}

RE *RECompileRange(char **re)
{
  RE *state = RECompileLiteral(re);
  if (!state) return state;
  if (**re == '-') {
    (*re)++;
    if (!**re) return 0;
    state->value.range[1] = **re;
    (*re)++;
  }
  return state;
}

RE *RECompileClass(char **re)
{
  RE *state;
  (*re)++;
  if (**re == ']') return 0;
  state = RECompileRange(re);
  if (!state) return 0;
  while (**re != ']') {
    RE *next;
    if (!**re) return 0;
    next = state;
    state = MakeState(reChoice);
    state->value.children[0] = next;
    next = RECompileRange(re);
    if (!next) return next;
    state->value.children[1] = next;
  }
  return state;
}

RE *RECompilePrimary(char **re)
{
  RE *state;
  switch (**re) {
  case 0:
    return 0;
  case '.':
    (*re)++;
    return MakeState(reAny);
  case '[':
    return RECompileClass(re);
  case '(':
    (*re)++;
    state = RECompileChoice(re);
    if (!state || **re != ')') return 0;
    (*re)++;
    return state;
  default:
    return RECompileLiteral(re);
  }
}

RE *RECompileQuant(char **re)
{
  RE *state = RECompilePrimary(re);
  if (!state) return state;
  switch (**re) {
  case '?':
    (*re)++;
    state->quantity = reOptional;
    break;
  case '*':
    (*re)++;
    state->quantity = reZeroPlus;
    break;
  case '+': {
    RE *next = state;
    (*re)++;
    state = MakeState(reSeq);
    state->value.children[0] = next;
    next = MakeState(next->type);
    *next = *state->value.children[0];
    next->quantity = reZeroPlus;
    state->value.children[1] = next;
    break;
  }
  }
  return state;
}

RE *RECompileSeq(char **re)
{
  RE *state = RECompileQuant(re);
  if (!state) return 0;
  while (**re && **re != '|' && **re != ')') {
    RE *next = state;
    state = MakeState(reSeq);
    state->value.children[0] = next;
    next = RECompileQuant(re);
    if (!next) return 0;
    state->value.children[1] = next;
  }
  return state;
}

RE *RECompileChoice(char **re)
{
  RE *state = RECompileSeq(re);
  if (!state) return 0;
  while (**re == '|') {
    RE *next = state;
    (*re)++;
    state = MakeState(reChoice);
    state->value.children[0] = next;
    next = RECompileSeq(re);
    if (!next) return 0;
    state->value.children[1] = next;
  }
  return state;
}

RE *RECompile(char *pattern)
{
  return RECompileChoice(&pattern);
}

i32 RETestQuantity(RE *re, char *str);

i32 RETestState(RE *re, char *str)
{
  i32 matched;
  switch (re->type) {
  case reLit:
    if (*str >= re->value.range[0] && *str <= re->value.range[1]) {
      return 1;
    } else {
      return -1;
    }
  case reAny:
    if (!*str) return -1;
    return 1;
  case reSeq:
    matched = RETestQuantity(re->value.children[0], str);
    if (matched < 0) return -1;

  case reChoice:

  default:
    return -1;
  }
}

i32 RETestQuantity(RE *re, char *str)
{
  i32 matched;
  switch (re->quantity) {
  case reOne:
    return RETestState(re, str);
  case reOptional:
    matched = RETestState(re, str);
    if (matched > 0) return matched;
    return 0;
  case reZeroPlus:
    matched = RETestState(re, str);
    while (matched > 0) {
      i32 nextMatched = RETestState(re, str + matched);
      if (nextMatched < 0) {
        matched = 0;
      } else {
        matched += nextMatched;
      }
    }
    return matched;
  }
}

i32 RETest(char *pattern, char *str)
{
  RE *re = RECompile(pattern);
  if (!re) return -1;

  return RETestQuantity(re, str);
}
