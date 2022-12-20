#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include "ast.h"

void codegen(FILE *fout, AstNode *n);

#endif
