#ifndef MMRBC_GENERATOR_H_
#define MMRBC_GENERATOR_H_

#include <stdint.h>

#include "scope.h"

#define HEADER_SIZE 22
#define FOOTER_SIZE 8

typedef struct node Node;

void Generator_generate(Scope *scope, Node *root);

#endif
