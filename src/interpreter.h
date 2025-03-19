#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser.h"

class Interpreter
{
public:
    int evaluate(ASTNode *root);
};

#endif
