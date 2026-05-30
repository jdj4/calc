#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

#define VERSION "calc 1.0.0"
#define COPYRIGHT "Copyright (C) 2026 jdj4. All Rights Reserved."

static void print_help_msg(void);
static void print_welcome_msg(void);
static void args(int argc, char *arg);
int main(int argc, char *argv[]);
