#ifndef MMRBC_TOKENIZER_H_
#define MMRBC_TOKENIZER_H_

#include <stdbool.h>

#include "token.h"

typedef enum mode
{
  MODE_NONE,
  MODE_COMMENT,
  MODE_QWORDS,
  MODE_WORDS,
  MODE_QSYMBOLS,
  MODE_SYMBOLS,
  MODE_TSTRING_DOUBLE,
  MODE_TSTRING_SINGLE,
} Mode;

typedef enum paren
{
  PAREN_NONE,
  PAREN_BRACE,
} Paren;

typedef struct tokenizer
{
  Mode mode;
  char *line;
  FILE *file;
  int line_num;
  int pos;
  int paren_stack_num;
  char modeTerminater;
  State state;
  Paren paren_stack[];
} Tokenizer;

void Tokenizer_new(Tokenizer* const self, FILE *file);

void Tokenizer_puts(Tokenizer* const self, char *line);

bool Tokenizer_hasMoreTokens(Tokenizer* const self);

void Tokenizer_advance(Tokenizer* const self, Token* const token,  bool recursive);

static struct {
  char *string;
} KEYWORDS[] = {
  {"BEGIN"},
  {"class"},
  {"ensure"},
  {"nil"},
  {"self"},
  {"when"},
  {"END"},
  {"def"},
  {"false"},
  {"not"},
  {"super"},
  {"while"},
  {"alias"},
  {"defined?"},
  {"for"},
  {"or"},
  {"then"},
  {"yield"},
  {"and"},
  {"do"},
  {"if"},
  {"redo"},
  {"true"},
  {"__LINE__"},
  {"begin"},
  {"else"},
  {"in"},
  {"rescue"},
  {"undef"},
  {"__FILE__"},
  {"break"},
  {"elsif"},
  {"module"},
  {"retry"},
  {"unless"},
  {"__ENCODING__"},
  {"case"},
  {"end"},
  {"next"},
  {"return"},
  {"until"},
  {NULL}
};

static struct {
  char letter;
} OPERATORS_1[] = {
  {'+'},
  {'-'},
  {'*'},
  {'/'},
  {'%'},
  {'&'},
  {'|'},
  {'^'},
  {'!'},
  {'~'},
  {'>'},
  {'<'},
  {'='},
  {'?'},
  {':'},
  {0}
};

static struct {
  char *string;
} OPERATORS_2[] = {
  {"**"},
  {"<<"},
  {">>"},
  {"&&"},
  {"||"},
  {"::"},
  {">="},
  {"<="},
  {"=="},
  {"!="},
  {"=~"},
  {"!~"},
  {".."},
  {"=>"},
  {"+="},
  {"-="},
  {"*="},
  {"/="},
  {"%="},
  {"&="},
  {"|="},
  {"^="},
  {NULL}
};

static struct {
  char *string;
} OPERATORS_3[] = {
  {"<=>"},
  {"==="},
  {"..."},
  {"**="},
  {"<<="},
  {">>="},
  {"&&="},
  {"||="},
  {NULL}
};

static struct {
  char letter;
} PARENS[] = {
  {'('},
  {')'},
  {'['},
  {']'},
  {'{'},
  {'}'},
  {0}
};

static struct {
  char letter;
} COMMA[] = {
  {','},
  {0}
};

static struct {
  char letter;
} SEMICOLON[] = {
  {';'},
  {0}
};

#endif