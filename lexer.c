/*
 * TODO:
 * - Cannot return an array from `tokenize`, need dynamic allocation
 */
#include "lexer.h"

static int contains(char *str, char c) {
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == c) return 1;
    return 0;
}

TokenPair *scan_number(char **num) {
    TokenPair *pair = malloc(sizeof(TokenPair)); // TODO: memcheck
    int prev_digit = 0, dot_count = 0, prev_e = 0, e_count = 0;
    char *start = *num;
    while (1) {
        if (isdigit(**num)) {
            prev_digit = 1;
            prev_e = 0;
            (*num)++;
        } else if (prev_digit == 1 && dot_count == 0 && **num == '.') {
            prev_digit = 0;
            prev_e = 0;
            dot_count++;
            (*num)++;
        } else if (prev_digit == 1 && e_count == 0 && (**num == 'E' || **num == 'e')) {
            prev_digit = 0;
            prev_e = 1;
            e_count++;
            (*num)++;
        } else if (prev_e == 1 && (**num == '+' || **num == '-')) {
            prev_digit = 0;
            prev_e = 0;
            (*num)++;
        } else break;
    }
    
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
    int valid = 0;
    char *start = *ident;
    while (1) {
        if (isalpha(**ident) || **ident == '_') {
            valid = 1;
            (*ident)++;
        } else if (valid && isdigit(**ident)) {
            (*ident)++;
        } else break;
    }
    
    int len = *ident - start;
    char *value = malloc(len + 1); // TODO: memcheck
    memcpy(value, start, len);
    value[len] = '\0';
    
    pair->token = IDENT;
    pair->value = value;
    return pair;
}

TokenPair *scan_operator(char **op) {
    TokenPair *pair = malloc(sizeof(TokenPair));
    char *next = *op + 1;
    switch (**op) {
        case '+':
            pair->token = PLUS;
            pair->value = "+";
            (*op)++;
            break;
        case '-':
            pair->token = MINUS;
            pair->value = "-";
            (*op)++;
            break;
        case '*':
            if (*next == '*') {
                pair->token = EXP;
                pair->value = "**";
                (*op) += 2;
            } else {
                pair->token = MULT;
                pair->value = "*";
                (*op)++;
            }
            break;
        case '/':
            if (*next == '/') {
                pair->token = INTDIV;
                pair->value = "//";
                (*op) += 2;
            } else {
                pair->token = DIV;
                pair->value = "/";
                (*op)++;
            }
            break;
        case '%':
            pair->token = MOD;
            pair->value = "%";
            (*op)++;
            break;
        case '<':
            if (*next == '=') {
                pair->token = LE;
                pair->value = "<=";
                (*op) += 2;
            } else {
                pair->token = LT;
                pair->value = "<";
                (*op)++;
            }
            break;
        case '>':
            if (*next == '=') {
                pair->token = GE;
                pair->value = ">=";
                (*op) += 2;
            } else {
                pair->token = GT;
                pair->value = ">";
                (*op)++;
            }
            break;
        case '=':
            pair->token = EQ;
            pair->value = "=";
            (*op)++;
            break;
        case '!':
            if (*next == '=') {
                pair->token = NE;
                pair->value = "!=";
                (*op) += 2;
            } else {
                pair->token = NOT;
                pair->value = "!";
                (*op)++;
            }
            break;
        case '^':
            pair->token = XOR;
            pair->value = "^";
            (*op)++;
            break;
        case '&':
            if (*next == '&') {
                pair->token = AND;
                pair->value = "&&";
                (*op) += 2;
            } else {
                pair->token = BITAND;
                pair->value = "&";
                (*op)++;
            }
            break;
        case '|':
            if (*next == '|') {
                pair->token = OR;
                pair->value = "||";
                (*op) += 2;
            } else {
                pair->token = BITOR;
                pair->value = "|";
                (*op)++;
            }
            break;
        case '(':
            pair->token = LPAREN;
            pair->value = "(";
            (*op)++;
            break;
        case ')':
            pair->token = RPAREN;
            pair->value = ")";
            (*op)++;
            break;
        case ',':
            pair->token = COMMA;
            pair->value = ",";
            (*op)++;
            break;
        default:
            break;
    }
    return pair;
}

TokenPair *tokenize(char *line) {
    int first = 1;
    TokenPair *head = NULL, *tail = NULL, *token, *error;
    for (char *ptr = line; *ptr != '\0'; ) {
        token = NULL;
        if (isspace(*ptr)) {
            ptr++;
            continue;
        }
        
        if (isdigit(*ptr) || (first && (*ptr == '-' || *ptr == '+'))) {
            token = scan_number(&ptr);
            printf("NUMBER: %s\n", token->value);
        } else if (isalpha(*ptr) || *ptr == '_') {
            token = scan_ident(&ptr);
            printf("IDENT: %s\n", token->value);
        } else if (contains(OPERATORS, *ptr)) {
            token = scan_operator(&ptr);
            printf("OP: %s\n", token->value);
        } else {
            error = malloc(sizeof(TokenPair)); // TODO: memcheck
            error->token = SYNTAX_ERROR;
            error->value = "SyntaxError: invalid syntax";
            return error;
        }
        first = 0;
        
        token->next = NULL;
        if (head == NULL) {
            head = token;
            tail = token;
        } else {
            tail->next = token;
            tail = token;
        }
    }
    return head;
}
