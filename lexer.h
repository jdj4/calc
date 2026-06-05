#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define OPERATORS "+-*/%<>=^&|(),"
#define SCI_NOTATION "Ee+-"
#define BUFFER 100

typedef enum token {
    IDENT,
    NUMBER,
    PLUS,
    MINUS,
    MULT,
    EXP,
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
    LPAREN,
    RPAREN,
    COMMA,
    SYNTAX_ERROR,
    EOF_
} Token;

typedef struct token_pair {
    enum token token;
    char *value;
    struct token_pair *next;
} TokenPair;

typedef struct token_list {
    struct token_pair *head;
} TokenList;

TokenPair *tokenize(char *line);
