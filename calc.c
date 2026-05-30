#include "calc.h"

static void print_help_msg(void) {
}

static void print_welcome_msg(void) {
    printf(VERSION); puts(" by jdj4");
    puts("Use CLI arg --help for usage information");
}

static void args(int argc, char *arg) {
    if (argc > 1) {
        if (strcmp(arg, "--version") == 0) {
            puts(VERSION);
            exit(0);
        } else if (strcmp(arg, "--credits") == 0) {
            puts(COPYRIGHT);
            exit(0);
        } else if (strcmp(arg, "--help") == 0) {
            print_help_msg();
            exit(0);
        } else if (strcmp(arg, "-q") == 0) {
        } else {
            printf("Invalid argument '%s', valid CLI args are --version, --credits, --help, and -q\n\n", arg);
            print_welcome_msg();
        }
    } else print_welcome_msg();
}

int main(int argc, char *argv[]) {
    args(argc, argv[1]);    
    size_t n = 0;
    char *line = NULL;
    while (!feof(stdin)) {
        printf(">>> ");
        while (getline(&line, &n, stdin) > 0) {
            printf("%s", line);
            break;
        }
    }
    return 0;
}
