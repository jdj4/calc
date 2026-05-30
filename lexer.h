#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define OPERATORS "+-*/%<>=^&|"
#define SCI_NOTATION "Ee+-"

typedef enum {
    IDENT,
    NUMBER,
    PLUS,
    MINUS,
    MULT,
    DIV,
    INTDIV,
    MOD,
    NOT,
    EQ,
    NE,
    LT,
    LE,
    GT,
    GE,
    XOR,
    BITAND,
    BITOR,
    AND,
    OR,
    LBRACK,
    RBRACK,
    EOF_
} Token;

typedef struct {
    Token token;
    char *value;
} TokenPair;

/*TokenPair **/void tokenize(char *line);
