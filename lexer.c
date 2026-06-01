/*
 * TODO:
 * - Wrong logic for scanning
 * - `scan_operator` is broken
 * - Cannot return an array from `tokenize`, need dynamic allocation
 */
#include "lexer.h"

static int contains(char *str, char c) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) return 1;
    }
    return 0;
}

TokenPair *scan_number(char **num) {
    TokenPair *pair = malloc(sizeof(TokenPair)); // TODO: memcheck
    char *start = *num;
    while (isdigit(**num) || contains(SCI_NOTATION, **num) || **num == '.') (*num)++;
    
    int len = *num - start;
    char *value = malloc(len + 1); // TODO: memcheck
    memcpy(value, start, len);
    value[len] = '\0';
    
    pair->token = NUMBER;
    pair->value = value;
    return pair;
}

TokenPair *scan_ident(char **ident) {
    TokenPair *pair = malloc(sizeof(TokenPair));
    char *start = *ident;
    while (isalpha(**ident) || **ident == '-') (*ident)++;
    
    int len = *ident - start;
    char *value = malloc(len + 1); // TODO: memcheck
    memcpy(value, start, len);
    value[len] = '\0';
    
    pair->token = IDENT;
    pair->value = value;
    return pair;
}

TokenPair *scan_operator(char *op) {
    TokenPair *pair = malloc(sizeof(TokenPair));
    char *next = op + 1;
    switch (*op) {
        case '+':
            pair->token = PLUS;
            pair->value = "+";
            break;
        case '-':
            pair->token = MINUS;
            pair->value = "-";
            break;
        case '*':
            pair->token = MULT;
            pair->value = "*";
            break;
        case '/':
            if (*next == '/') {
                pair->token = INTDIV;
                pair->value = "//";
            } else {
                pair->token = DIV;
                pair->value = "/";
            }
            break;
        case '%':
            pair->value = "%";
            break;
        case '<':
            if (*next == '=') {
                pair->token = LE;
                pair->value = "<=";
            } else {
                pair->token = LT;
                pair->value = "<";
            }
            break;
        case '>':
            if (*next == '=') {
                pair->token = GE;
                pair->value = ">=";
            } else {
                pair->token = GT;
                pair->value = ">";
            }
            break;
        case '=':
            pair->token = EQ;
            pair->value = "=";
            break;
        case '!':
            if (*next == '=') {
                pair->token = NE;
                pair->value = "!=";
            } else {
                pair->token = NOT;
                pair->value = "!";
            }
            break;
        case '^':
            pair->token = XOR;
            pair->value = "^";
            break;
        case '&':
            if (*next == '&') {
                pair->token = AND;
                pair->value = "&&";
            } else {
                pair->token = BITAND;
                pair->value = "&";
            }
            break;
        case '|':
            if (*next == '|') {
                pair->token = OR;
                pair->value = "||";
            } else {
                pair->token = BITOR;
                pair->value = "|";
            }
            break;
        default:
            break;
    }
    return pair;
}

/*TokenPair **/void tokenize(char *line) {
    TokenPair *tokens[100] = { NULL };
    int i = 0;
    for (char *ptr = line; *ptr != '\0'; ) {        
        if (isspace(*ptr)) {
            ptr++;
            continue;
        }
        
        if (isdigit(*ptr)) {
            //TokenPair *pair = scan_number(ptr);
            //printf("%s\n", pair->value);
            tokens[i] = scan_number(&ptr);
            printf("NUMBER: %s\n", tokens[i]->value);
        } else if (isalpha(*ptr) || *ptr == '_') {
            tokens[i] = scan_ident(&ptr);
            printf("IDENT: %s\n", tokens[i]->value);
        } else if (contains(OPERATORS, *ptr)) {
            tokens[i] = scan_operator(ptr);
            printf("OP: %s\n", tokens[i]->value);
        } else {
            ptr++;
            fprintf(stderr, "Error\n");
        }
        i++;
    }
}
